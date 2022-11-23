#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/// @brief Clase que representa un gramatica
class Gramatica {
 private:
  char estado_inicial_;         // Estado inicial
  std::vector<char> simbolos_;  // guarda los simbolos del alfabeto
  std::vector<std::string>
      elementos_;  // Guerda las lineas del fichero de entrada
  std::vector<char>
      todos_estados_no_terminales_;  // guarda 25 posibles estados no terminales
  std::vector<char> estados_no_terminales_;  // guarda los estados no terminales
  std::vector<char> estados_terminales_;     // guarda los estados terminales
  std::vector<std::vector<std::string>>
      tabla_de_transiciones_;  // Guarda la tabla de transiciones

 public:
  Gramatica();
  ~Gramatica();
  void Analizar(std::string);
  void Mostrar(std::ostream& os);
  void SetTablaDeTransiciones();
  void LimpiarLinea(std::string);
  void SepararNoTerminales(std::string);
  void SepararSiTerminales();
  void FormaNormalDeChomsky();
  bool Inutiles();
  bool Vacias();
  bool Unitarias();
};
