#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "automata.h"

using namespace std;


int main(int argc, char *argv[])
{
    Automata automata;
    std::ofstream off_file(argv[2]);
    automata.analizar(argv[1]);
    // programa.mostrar(off_file);
    // programa.mostrar(std::cout);
   
}