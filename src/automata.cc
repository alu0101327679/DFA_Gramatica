#include "automata.h"

Automata::Automata() {}

Automata::~Automata() {}

/// @brief Analiza el fichero de entrada y guarda los datos en el automata
/// @param nombre
void Automata::Analizar(std::string nombre) {
  std::vector<std::string> lineas_transiciones;
  std::ifstream file(nombre);
  if (!file.is_open()) {
    std::cout << "Error al abrir el archivo" << std::endl;
    return;
  }
  std::string line;
  std::vector<std::string> lines;
  int line_number = 0;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  for (auto i = 0; i < lines.size(); i++) {
    SepararElementos(lines[i]);
  }

  for (auto i = 65; i <= 90; i++) {
    todos_estados_no_terminales_.push_back(i);
  }

  for (auto i = 0; i < lines.size(); i++) {
    SepararEstados(lines[i]);
  }
  file.close();
}

void Automata::SepararEstados(std::string line) {
  for (auto i = 0; i < line.size(); i++) {
    for (auto j = 0; j < todos_estados_no_terminales_.size(); j++) {
      if (line[i] == todos_estados_no_terminales_[j]) { //comprueba si el estado
                                                       //no terminal esta en la
                                                       //linea
        estados_no_terminales_.push_back(todos_estados_no_terminales_[j]);
        todos_estados_no_terminales_.erase(todos_estados_no_terminales_.begin() + j);
      }
    }
  }
}

/// @brief separa los elementos de la linea
/// @param line
void Automata::SepararElementos(std::string line) {
  std::string elemento;
  std::string elemento2;
  for (auto i = 0; i < line.size(); i++) {
    if ((line[i] != ' ') && (line[i] != '-') && (line[i] != '|') &&
        (line[i] != '>')) {
      elemento += line[i];
    } else {
      elemento2 += elemento;
      elemento = "";
    }
  }
  elemento2 += elemento;
  elementos_.push_back(elemento2);
}

/// @brief muestra por donde se especifique los datos del automata
/// @param os
void Automata::Mostrar(std::ostream& os) {

  os << "Nodos no terminales: ";
  for (auto i = 0; i < estados_no_terminales_.size(); i++) {
    os << estados_no_terminales_[i] << " ";
  }
  os << std::endl;

  os << "Elementos: " << std::endl;
  for (auto i = 0; i < elementos_.size(); i++) {
    os << elementos_[i] << std::endl;
  }
  os << std::endl;
}