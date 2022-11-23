#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>



/// @brief Clase que representa un automata
class Automata {
 private:
  char estado_inicial_;         // Estado inicial
  std::vector<char> simbolos_;  // guarda los simbolos del alfabeto
  std::vector<std::string>
      elementos_;  // Guerda las lineas del fichero de entrada
  std::vector<char>
      todos_estados_no_terminales_;  // guarda 25 posibles estados no terminales
  std::vector<char> estados_no_terminales_;  // guarda los estados no terminales
  std::vector<char> estados_terminales_;     // guarda los estados terminales
  std::vector<std::vector<std::pair<char, char>>>
    tabla_de_transiciones_;  // Guarda la tabla de transiciones

 public:
  Automata();
  ~Automata();
  void Analizar(std::string);
  void Mostrar(std::ostream& os);
  void SetTablaDeTransiciones();
  void SepararElementos(std::string);
  void SepararNoTerminales(std::string);
  void SepararSiTerminales();    
};
