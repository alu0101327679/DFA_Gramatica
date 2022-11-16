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
    if (!off_file.is_open())
    {
        std::cout << "Error al abrir el archivo" << std::endl;
        return 1;
    }
    automata.Analizar(argv[1]);
    automata.Mostrar(off_file);
    automata.Mostrar(std::cout);
   
}