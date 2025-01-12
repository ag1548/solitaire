SUIT_S = "S"
SUIT_C = "C"
SUIT_H = "H"
SUIT_D = "D"

FACE_A = "A"
FACE_2 = "2"
FACE_3 = "3"
FACE_4 = "4"
FACE_5 = "5"
FACE_6 = "6"
FACE_7 = "7"
FACE_8 = "8"
FACE_9 = "9"
FACE_0 = "0"
FACE_J = "J"
FACE_Q = "Q"
FACE_K = "K"

SUITS = [SUIT_S, SUIT_C, SUIT_H, SUIT_D]
FACES = [
    FACE_A,
    FACE_2,
    FACE_3,
    FACE_4,
    FACE_5,
    FACE_6,
    FACE_7,
    FACE_8,
    FACE_9,
    FACE_0,
    FACE_J,
    FACE_Q,
    FACE_K,
]


class Card:
    def __init__(self, suit, face):
        self.suit = suit
        self.face = face

    def __eq__(self, other):
        return other.suit == self.suit and other.face == self.face

    def __repr__(self):
        if self.IsDarkCard():
            return f"{self.face} of {self.suit}"
        else:
            return f"\033[7m{self.face} of {self.suit}\033[0m"

    def __str__(self):
        if self.IsDarkCard():
            return f"{self.face} of {self.suit}"
        else:
            return f"\033[7m{self.face} of {self.suit}\033[0m"

    def IsDarkCard(self):
        return self.suit == SUIT_C or self.suit == SUIT_S


class SolitaireCard(Card):
    def __init__(self, suit, face):
        super().__init__(suit, face)
        self.revealed = False

    def Reveal(self):
        self.revealed = True


class Deck:
    def __init__(self):
        self.cards = [SolitaireCard(s, f) for s in SUITS for f in FACES]

    def __repr__(self):
        result = ""
        for i, c in enumerate(self.cards):
            result += f"[{i:2}]: {c}"
            if i % 13 == 12:
                result += "\n"
            elif i is not len(self.cards):
                result += ", "
        return result

    def __str__(self):
        result = ""
        for i, c in enumerate(self.cards):
            result += f"[{i:2}]: {c}"
            if i % 13 == 12:
                result += "\n"
            elif i is not len(self.cards) - 1:
                result += ", "
        return result

    def Shuffle(self):
        from random import seed, shuffle

        seed(None)
        shuffle(self.cards)

    def DrawCard(self):
        return self.cards.pop()

    def IsEmpty(self):
        return len(self.cards) == 0


class Board:
    def __init__(self):
        self.drawPile = []
        self.discardPile = []

        self.foundation_S = []
        self.foundation_C = []
        self.foundation_D = []
        self.foundation_H = []

        self.boardStack_0 = []
        self.boardStack_1 = []
        self.boardStack_2 = []
        self.boardStack_3 = []
        self.boardStack_4 = []
        self.boardStack_5 = []
        self.boardStack_6 = []

        self.deck = Deck()
        self.deck.Shuffle()

        for idx, stack in enumerate(
            [
                self.boardStack_0,
                self.boardStack_1,
                self.boardStack_2,
                self.boardStack_3,
                self.boardStack_4,
                self.boardStack_5,
                self.boardStack_6,
            ]
        ):
            for _ in range(idx + 1):
                stack.append(self.deck.DrawCard())
            stack[-1].Reveal()

        while not self.deck.IsEmpty():
            c = self.deck.DrawCard()
            c.Reveal()
            self.drawPile.append(c)

    def DrawCardOrResetDrawPile(self):
        if not len(self.drawPile):
            self.ResetDrawPile()
        else:
            self.discardPile.append(self.drawPile.pop())

    def ResetDrawPile(self):
        [self.drawPile.append(c) for c in reversed(self.discardPile)]
        self.discardPile.clear()

    def MoveColumn(self):
        def acquire_value(msg):
            value = None
            while value is None:
                value = input(msg)
                try:
                    value_validated = int(value)
                except:
                    pass
                else:
                    if value_validated >= 0 and value_validated <= 7:
                        return value_validated
                value = None

        from_ = acquire_value("Move from which column? ")
        to_ = acquire_value("Move to which column? ")

        if from_ == 0:
            self.AttemptMoveFromDiscardPile(to_)
        else:
            self.AttemptColumnMove(from_, to_)

    def PromoteToFoundation(self, option):
        source_stack = {
            0: self.discardPile,
            1: self.boardStack_0,
            2: self.boardStack_1,
            3: self.boardStack_2,
            4: self.boardStack_3,
            5: self.boardStack_4,
            6: self.boardStack_5,
            7: self.boardStack_6,
        }[option]

        if not len(source_stack):
            return

        foundation = {
            SUIT_S: self.foundation_S,
            SUIT_C: self.foundation_C,
            SUIT_H: self.foundation_H,
            SUIT_D: self.foundation_D,
        }[source_stack[-1].suit]

        if not len(foundation) and not source_stack[-1].face == FACE_A:
            return

        if (not len(foundation) and source_stack[-1].face == FACE_A) or (
            FACES.index(foundation[-1].face) == FACES.index(source_stack[-1].face) - 1
        ):
            foundation.append(source_stack.pop())
            self.RevealTopMostCard(source_stack)

    def CheckWinCondition(self):
        return all(
            len(f) > 0 and f[-1].face == FACE_K
            for f in [
                self.foundation_S,
                self.foundation_C,
                self.foundation_D,
                self.foundation_H,
            ]
        )

    def RevealTopMostCard(self, stack):
        if len(stack):
            stack[-1].Reveal()

    def AttemptMoveFromDiscardPile(self, to_):
        if not len(self.discardPile) or not to_:
            return

        fromCard = self.discardPile[-1]
        if fromCard.face == FACE_K:
            target_stack = {
                1: self.boardStack_0,
                2: self.boardStack_1,
                3: self.boardStack_2,
                4: self.boardStack_3,
                5: self.boardStack_4,
                6: self.boardStack_5,
                7: self.boardStack_6,
            }[to_]

            if len(target_stack):
                return

            target_stack.append(self.discardPile.pop())
            return

        # Card is not a K

        target_stack = {
            1: self.boardStack_0,
            2: self.boardStack_1,
            3: self.boardStack_2,
            4: self.boardStack_3,
            5: self.boardStack_4,
            6: self.boardStack_5,
            7: self.boardStack_6,
        }[to_]
        if not len(target_stack):
            return

        toCard = target_stack[-1]

        if fromCard.IsDarkCard() == toCard.IsDarkCard():
            return

        if FACES.index(fromCard.face) + 1 != FACES.index(toCard.face):
            return

        target_stack.append(self.discardPile.pop())

    def AttemptColumnMove(self, from_, to_):
        if from_ == to_ or not to_:
            return

        source_stack = {
            1: self.boardStack_0,
            2: self.boardStack_1,
            3: self.boardStack_2,
            4: self.boardStack_3,
            5: self.boardStack_4,
            6: self.boardStack_5,
            7: self.boardStack_6,
        }[from_]
        if not len(source_stack):
            return
        sourceIndex = 0
        while not source_stack[sourceIndex].revealed:
            sourceIndex += 1
        fromCard = source_stack[sourceIndex]

        target_stack = {
            1: self.boardStack_0,
            2: self.boardStack_1,
            3: self.boardStack_2,
            4: self.boardStack_3,
            5: self.boardStack_4,
            6: self.boardStack_5,
            7: self.boardStack_6,
        }[to_]
        if not len(target_stack):
            if fromCard.face != FACE_K:
                return

            number_moved = 0
            for c in source_stack[sourceIndex:]:
                number_moved += 1
                target_stack.append(c)
            while number_moved:
                number_moved -= 1
                source_stack.pop()
            self.RevealTopMostCard(source_stack)
            return

        toCard = target_stack[-1]

        if fromCard.IsDarkCard() == toCard.IsDarkCard():
            return

        if FACES.index(fromCard.face) + 1 != FACES.index(toCard.face):
            return

        number_moved = 0
        for c in source_stack[sourceIndex:]:
            number_moved += 1
            target_stack.append(c)
        while number_moved:
            number_moved -= 1
            source_stack.pop()
        self.RevealTopMostCard(source_stack)

    def PrintBoard(self):

        # Column 0 label
        print(" " * 8, end="")
        print(f"{'[c0]':>8}")

        # Draw pile
        print(f"[{'*' if len(self.drawPile) else '-':>6}]", end="")
        # Discard pile
        print(
            f"[{self.discardPile[-1] if len(self.discardPile) else f"{'-':>6}"}]",
            end="",
        )
        # Foundations
        print(" " * 8, end="")
        for f in [
            self.foundation_S,
            self.foundation_C,
            self.foundation_D,
            self.foundation_H,
        ]:
            print(f"[{f[-1] if len(f) else f"{'-':>6}"}]", end="")
        print()
        print()

        # Column numbers
        [print(f"{f"[c{x}]":>8}", end="") for x in range(1, 8)]
        print()

        number_of_printed_lines = 0
        while True:
            for stack in [
                self.boardStack_0,
                self.boardStack_1,
                self.boardStack_2,
                self.boardStack_3,
                self.boardStack_4,
                self.boardStack_5,
                self.boardStack_6,
            ]:
                if not len(stack) and not number_of_printed_lines:
                    print(f"[{'-':>6}]", end="")
                elif number_of_printed_lines >= len(stack):
                    print(" " * 8, end="")
                elif stack[number_of_printed_lines].revealed:
                    print(f"[{stack[number_of_printed_lines]}]", end="")
                elif not stack[number_of_printed_lines].revealed:
                    print(f"[{'*':>6}]", end="")

            if all(
                number_of_printed_lines >= len(stack)
                for stack in [
                    self.boardStack_0,
                    self.boardStack_1,
                    self.boardStack_2,
                    self.boardStack_3,
                    self.boardStack_4,
                    self.boardStack_5,
                    self.boardStack_6,
                ]
            ):
                break

            print()

            number_of_printed_lines += 1

        while number_of_printed_lines <= 13:
            number_of_printed_lines += 1
            print()

        print()


class Game:
    def __init__(self):
        self.board = Board()

        while True:
            self.board.PrintBoard()
            self.PrintMenu()

            option = input(">>> ")

            while True:
                if option == "q":
                    exit(0)
                elif option == "d":
                    self.board.DrawCardOrResetDrawPile()
                    break
                elif option == "m":
                    self.board.MoveColumn()
                    break
                elif option >= "0" and option <= "7":
                    self.board.PromoteToFoundation(int(option))
                    break
                else:
                    print(f"Invalid input: {option}")
                    option = input(">>> ")

            print("***************************************************************")
            if self.board.CheckWinCondition():
                self.board.PrintBoard()
                break

        print("************ YOU WIN! ************")

    def PrintMenu(self):
        print("***************************************************************")
        print("Menu:")
        print("   q - exit")
        print("   d - [reset] draw pile")
        print("   0-7 - Promote to foundation ('0' is the discard pile)")
        print("   m - Move a card (or stack of cards)")


Game()
