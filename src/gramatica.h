#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


/// @brief Clase que representa una gramatica
class Gramatica {
 private:
  std::vector<std::vector<std::pair<char, char>>>
      tabla_de_transiciones_;  // Guarda la tabla de transiciones
  std::vector<char> estados_no_terminales_;

 public:
  Gramatica();
  Gramatica(std::vector<std::vector<std::pair<char, char>>>, std::vector<char>);
  ~Gramatica();
  void ImprimirFichero(std::ostream& os);
};
