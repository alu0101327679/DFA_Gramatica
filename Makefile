

make: src/main.cc  src/gramatica.cc 
	g++ src/main.cc  src/gramatica.cc  -o  programa

clean: 
	rm programa