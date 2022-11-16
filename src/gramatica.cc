
#include "gramatica.h"

Gramatica::Gramatica() {}

Gramatica::Gramatica(std::vector<std::vector<std::pair<char, char>>> tabla,
                     std::vector<char> estados) {
  tabla_de_transiciones_ = tabla;
  estados_no_terminales_ = estados;
}

Gramatica::~Gramatica() {}

void Gramatica::ImprimirFichero(std::ostream& os) {
  os << "Gramatica: " << std::endl;
  for (int i = 0; i < estados_no_terminales_.size(); i++) {
    os << estados_no_terminales_[i] << " -> ";
    for (int j = 0; j < tabla_de_transiciones_[i].size(); j++) {
      os << tabla_de_transiciones_[i][j].first << ""
         << tabla_de_transiciones_[i][j].second << " ";
    }
    os << std::endl;
  }
}
