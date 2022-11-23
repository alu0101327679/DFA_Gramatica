#include "gramatica.h"

Gramatica::Gramatica() {}

Gramatica::Gramatica(
    std::vector<std::vector<std::pair<char, char>>> tabla_de_transiciones,
    std::vector<char> estados_no_terminales, std::vector<char> simbolos,
    char estado_inicial, std::vector<char> estados_finales,
    std::vector<std::string> elementos, int nodos) {
  tabla_de_transiciones_ = tabla_de_transiciones;
  todos_estados_no_terminales = estados_no_terminales;
  simbolos_ = simbolos;
  estado_inicial_ = estado_inicial;
  estados_finales_ = estados_finales;
  elementos_ = elementos;
  nodos_ = nodos;
}

Gramatica::~Gramatica() {}

void Gramatica::ImprimirFichero(std::ostream& os) {
  os << simbolos_.size() << std::endl;  //<< "Simbolos: "
  for (auto i = 0; i < simbolos_.size(); i++) {
    os << simbolos_[i] << "\n";
  }
  os << todos_estados_no_terminales.size()
     << std::endl;  //<< "Nodos no terminales: "
  for (auto i = 0; i < todos_estados_no_terminales.size(); i++) {
    os << todos_estados_no_terminales[i] << "\n";
  }
  os << estado_inicial_ << std::endl;  //<< "Estado inicial: "

  int size = 0;
  int size2 = 0;
  for (auto i = 0; i < tabla_de_transiciones_.size(); i++) {
    size += tabla_de_transiciones_[i].size();
  }
  os << size << std::endl;  // "Tabla de transiciones: " <<
  for (auto i = 0; i < tabla_de_transiciones_.size(); i++) {
    for (auto j = 0; j < tabla_de_transiciones_[i].size(); j++) {
      os << todos_estados_no_terminales[i] << " -> ";
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
