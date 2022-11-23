#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/// @brief Clase que representa una gramatica
class Gramatica {
 private:
  int nodos_;            // Numero de nodos
  char estado_inicial_;  // Estado inicial
  std::vector<char> estados_finales_;
  std::vector<char> simbolos_;  // guarda los simbolos del alfabeto
  std::vector<std::string>
      elementos_;  // Guerda las lineas del fichero de entrada
  std::vector<std::vector<std::pair<char, char>>>
      tabla_de_transiciones_;  // Guarda la tabla de transiciones
  std::vector<char> todos_estados_no_terminales;

 public:
  Gramatica();
  Gramatica(
      std::vector<std::vector<std::pair<char, char>>> tabla_de_transiciones,
      std::vector<char> estados_no_terminales, std::vector<char> simbolos_,
      char estado_inicial, std::vector<char> estados_finales,
      std::vector<std::string> elementos, int nodos);
  ~Gramatica();
  void ImprimirFichero(std::ostream& os);
};
