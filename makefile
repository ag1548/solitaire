.PHONY: compile run

run: compile
	./solitaire

compile: src/*.cpp
	g++ -std=c++23 -o solitaire src/*.cpp

clean:
	@-rm solitaire
