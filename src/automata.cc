#include "automata.h"

Automata::Automata() {}

Automata::~Automata() {}

void Automata::Analizar(std::string nombre) {
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
  SetSimbolos(lines[0]);
  SetNumerodeNodos(lines[1]);
  SetEstadoArranque(lines[2]);
  for (auto i = 3; i < nodos_ + 3; i++)
  {
  SepararElementos(lines[i]);
  }

}

void Automata::SetSimbolos(std::string line) {
  std::vector<char> simbolos;
  for (auto i = 0; i < line.size(); i++) {
    if (line[i] != ' ') {
      simbolos.push_back(line[i]);
    }
  }
  simbolos_ = simbolos;
}

void Automata::SetNumerodeNodos(std::string line) {
  std::stringstream ss(line);
  ss >> nodos_;
}

void Automata::SetEstadoArranque(std::string line) {
  std::stringstream ss(line);
  ss >> estado_inicial_;
}

void Automata::SepararElementos(std::string line) {
  std::vector<std::string> elementos;
  std::string elemento;
  for (auto i = 0; i < line.size(); i++) {
    if (line[i] != ' ') {
      elemento += line[i];
    } else {
      elementos.push_back(elemento);
      elemento = "";
    }
  }
  elementos.push_back(elemento);
  SetTablaDeTransiciones(elementos);
}

void Automata::SetTablaDeTransiciones(std::vector<std::string> elementos) {
  std::vector<std::pair<int, char>> transiciones;
  for (auto i = 0; i < elementos.size(); i++) {
    std::pair<int, char> transicion;
    std::stringstream ss(elementos[i]);
    ss >> transicion.first;
    ss >> transicion.second;
    transiciones.push_back(transicion);
  }
  tabla_de_transiciones_.push_back(transiciones);
}

void Automata::Mostrar(std::ostream& os) { 
  os << "Automata" << std::endl;
  os << "Simbolos: ";
  for (auto i = 0; i < simbolos_.size(); i++) {
    os << simbolos_[i] << " ";
  }
  os << "numero de nodos: " << nodos_ << std::endl;
  os << "Estado inicial: " << estado_inicial_ << std::endl;
  os << "Tabla de transiciones: " << std::endl;
  for (auto i = 0; i < tabla_de_transiciones_.size(); i++) {
    for (auto j = 0; j < tabla_de_transiciones_[i].size(); j++) {
      os << tabla_de_transiciones_[i][j].first << " "
         << tabla_de_transiciones_[i][j].second << " ";
    }
    os << std::endl;
  }
  os << std::endl;
}

