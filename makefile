.PHONY: compile run

run: compile
	./solitaire

compile: src/*.cpp
	g++ -std=c++20 -o solitaire src/*.cpp

clean:
	@-rm solitaire
