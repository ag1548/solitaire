.PHONY: compile run

run: compile
	./solitaire

compile: src/*.cpp
	g++ -o solitaire src/*.cpp

clean:
	@-rm solitaire
