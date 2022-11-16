#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "gramatica.h"

class Automata {
 private:
  int nodos_;            // Numero de nodos
  char estado_inicial_;  // Estado inicial
  std::vector<char> estados_finales_;
  std::vector<char> simbolos_;  // guarda los simbolos del alfabeto
  std::vector<std::string>
      elementos_;  // Guerda las lineas del fichero de entrada
  std::vector<std::vector<std::pair<char, char>>>
      tabla_de_transiciones_;  // Guarda la tabla de transiciones
  std::vector<char> estados_no_terminales_;

 public:
  Automata();
  ~Automata();
  void Analizar(std::string);
  void Mostrar(std::ostream& os);
  std::vector<char> Split(std::string);
  void SetSimbolos(std::string);
  void SetNumerodeNodos(std::string);
  void SetEstadoArranque(std::string);
  void SetEstadoFinal(char);
  void SepararElementos(std::string);
  void SetTablaDeTransiciones();
  bool CheckString(std::string string);
  bool EsUnDfa();
  Gramatica ConvertirDfaEnGramatica();
};
