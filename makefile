.PHONY: compile run

run: compile
	./solitaire

compile: *.cpp
	g++ -o solitaire *.cpp

clean:
	@-rm *.o
	@-rm solitaire
