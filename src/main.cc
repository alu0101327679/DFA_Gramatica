#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "automata.h"
// #include "gramatica.h"

using namespace std;

int main(int argc, char *argv[]) {
  Automata automata;
  Gramatica gramatica;
  std::ofstream off_file(argv[2]);
  if (!off_file.is_open()) {
    std::cout << "Error al abrir el archivo" << std::endl;
    return 1;
  }
  automata.Analizar(argv[1]);
  // automata.ImprimirFichero(off_file);
  automata.ConvertirDfaEnGramatica(gramatica);
//   gramatica.ImprimirFichero(off_file);
  off_file.close();
  automata.Mostrar(std::cout);

  // esta debe ser aceptada
//   automata.CheckString("abb")
//       ? std::cout << "Cadena aceptada ----------" << std::endl
//       : std::cout << "Cadena no aceptada ----------" << std::endl;

//   // esta no debe ser aceptada
//   automata.CheckString("a")
//       ? std::cout << "Cadena aceptada ----------" << std::endl
//       : std::cout << "Cadena no aceptada ----------" << std::endl;

//   // esta debe ser aceptada
//   automata.CheckString("bb")
//       ? std::cout << "Cadena aceptada ----------" << std::endl
//       : std::cout << "Cadena no aceptada ----------" << std::endl;

//   // esta debe ser aceptada
//   automata.CheckString("abbaaaaaab")
//       ? std::cout << "Cadena aceptada ----------" << std::endl
//       : std::cout << "Cadena no aceptada ----------" << std::endl;

}