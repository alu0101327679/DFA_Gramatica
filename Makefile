

make: src/main.cc  src/automata.cc 
	g++ src/main.cc  src/automata.cc -o  programa

clean: 
	rm programa