#include "automata.h"

Automata::Automata() {}

Automata::~Automata() {}

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
  SetSimbolos(lines[0]);
  SetNumerodeNodos(lines[1]);
  SetEstadoArranque(lines[2]);
  for (auto i = 3; i < nodos_ + 3; i++)
  {
  SepararElementos(lines[i]);
  }
  SetTablaDeTransiciones();

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

  std::string elemento;
  std::string elemento2;
  for (auto i = 0; i < line.size(); i++) {
    if (line[i] != ' ') {
      elemento += line[i];
    } else {
      // std::cout << "Elemento: "<< elemento << std::endl;
      elemento2 += elemento;
      elemento = "";
    }
    // std::cout << elemento ;
  }
  // std::cout << std::endl;
  elementos_.push_back(elemento2);
  // for (auto i = 0; i < elementos_.size(); i++) {
  //   std::cout << elementos_[i] << " | " << i <<  std::endl;
  // }
  // std::cout << elementos_.size() << std::endl;
}

void Automata::SetTablaDeTransiciones() {
  std::vector<std::vector<std::pair<int, char>>> tabla_de_transiciones;
  

  // std::vector<std::vector<std::pair<int, char>>> tabla_de_transiciones;
  // std::vector<std::pair<int, char>> transiciones;
  // std::pair<int, char> transicion;
  // for (auto i = 0; i < elementos_.size(); i++) {
  //   for (auto j = 0; j < elementos_[i].size(); j++) {
  //     if (elementos_[i][j + 1] != ' ') {
  //       transicion.first = elementos_[i][j] - '0';
  //       transicion.second = elementos_[ i][j + 1]; // - '0';
  //     } else {
  //       transicion.first = elementos_[i][j] - '0';
  //       transicion.second = elementos_[i][j + 2]; // - '0';
  //     }
  //   }
  // }
}

void Automata::Mostrar(std::ostream& os) { 
  os << "Automata" << std::endl;
  os << "Simbolos: ";
  for (auto i = 0; i < simbolos_.size(); i++) {
    os << simbolos_[i] << " ";
  }
  os << std::endl;
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
  os << "Elementos: " << std::endl;
  for (auto i = 0; i < elementos_.size(); i++) {
    os << elementos_[i] << std::endl;
  }
  os << std::endl;
}

