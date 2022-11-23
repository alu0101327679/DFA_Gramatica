#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "gramatica.h"

// Shift + Alt + F

using namespace std;

int main(int argc, char *argv[]) {
  Gramatica gramatica;
  std::ofstream off_file(argv[2]);
  if (!off_file.is_open()) {
    std::cout << "Error al abrir el archivo" << std::endl;
    return 1;
  }
  gramatica.Analizar(argv[1]);
  gramatica.Mostrar(std::cout);
  //gramatica.Mostrar(off_file);
  off_file.close();

}