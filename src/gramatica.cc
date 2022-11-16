
#include "gramatica.h"

Gramatica::Gramatica() {}

Gramatica::Gramatica(
    std::vector<std::vector<std::pair<char, char>>> tabla_de_transiciones,
    std::vector<char> estados_no_terminales, std::vector<char> simbolos,
    char estado_inicial, std::vector<char> estados_finales,
    std::vector<std::string> elementos, int nodos) {
  tabla_de_transiciones_ = tabla_de_transiciones;
  estados_no_terminales_ = estados_no_terminales;
  simbolos_ = simbolos;
  estado_inicial_ = estado_inicial;
  estados_finales_ = estados_finales;
  elementos_ = elementos;
  nodos_ = nodos;
}

Gramatica::~Gramatica() {}

void Gramatica::ImprimirFichero(std::ostream& os) {
  os << "Simbolos: " << simbolos_.size() << std::endl;
  for (auto i = 0; i < simbolos_.size(); i++) {
    os << simbolos_[i] << "\n";
  }
  os << "Nodos no terminales: " << estados_no_terminales_.size() << std::endl;
  for (auto i = 0; i < estados_no_terminales_.size(); i++) {
    os << estados_no_terminales_[i] << "\n";
  }
  os << "Estado inicial: " << estado_inicial_ << std::endl;

  int size = 0;
  int size2 = 0;
  for (auto i = 0; i < tabla_de_transiciones_.size(); i++) {
    size += tabla_de_transiciones_[i].size();
  }
  os << "Tabla de transiciones: " << size << std::endl;
  for (auto i = 0; i < tabla_de_transiciones_.size(); i++) {
    for (auto j = 0; j < tabla_de_transiciones_[i].size(); j++) {
      os << estados_no_terminales_[i] << " -> ";
      os << tabla_de_transiciones_[i][j].first << ""
         << tabla_de_transiciones_[i][j].second << std::endl;
    }
  }
  // ----------------------------------------------
  // os << "---------------------" << std::endl;

  // os << std::endl;
  // os << "numero de nodos: " << nodos_ << std::endl;

  // os << "Estados finales: ";
  // for (auto i = 0; i < estados_finales_.size(); i++) {
  //   os << estados_finales_[i] << " ";
  // }
  // os << std::endl;

  // os << std::endl;

  // os << std::endl;
  // os << "Elementos: " << std::endl;
  // for (auto i = 0; i < elementos_.size(); i++) {
  //   os << elementos_[i] << std::endl;
  // }
  // os << std::endl;
}
