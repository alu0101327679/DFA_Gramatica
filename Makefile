

make: src/main.cc  src/automata.cc src/gramatica.cc
	g++ src/main.cc  src/automata.cc src/gramatica.cc -o  programa

clean: 
	rm programa