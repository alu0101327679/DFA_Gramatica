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
  for (auto i = 3; i < nodos_ + 3; i++) {
    SepararElementos(lines[i]);
  }
  // std::cout << "Hola" << std::endl;
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

void Automata::SetEstadoFinal(char member) {
  estados_finales_.push_back(member);
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
  elemento2 += elemento;
  // std::cout << "Elemento2: " << elemento2 << std::endl;
  elementos_.push_back(elemento2);
  // for (auto i = 0; i < elementos_.size(); i++) {
  //   std::cout << elementos_[i] << " | " << i <<  std::endl;
  // }
  // std::cout << elementos_.size() << std::endl;
  for (auto i = 0; i < line.size(); i++) {
    if (line[i] == '&') {
      SetEstadoFinal(line[0]);
    }
  }

  estados_no_terminales_.push_back(line[0]);
}

void Automata::SetTablaDeTransiciones() {
  std::vector<std::vector<std::pair<char, char>>> tabla_de_transiciones;
  std::vector<std::string> elementos;
  elementos.resize(elementos_.size());
  for (auto i = 0; i < elementos_.size(); i++) {
    elementos[i] = elementos_[i];
  }

  // std::cout << "nombre del nodo: " << elementos[0][0] << std::endl;
  // std::cout << "estado final o no: " << elementos[0][1] << std::endl;
  // std::cout << "numero de transiciones: " << elementos[0][2] << std::endl;
  // std::cout << "simbolo de la transicion: " << elementos[0][3] << std::endl;
  // std::cout << "nodo al que va: " << elementos[0][4] << std::endl;

  // std::cout << "simbolo de la transicion: " << elementos[0][3] << std::endl;
  // std::cout << "nodo al que va: " << elementos[0][4] << std::endl;
  // std::cout << "simbolo de la transicion: " << elementos[0][5] << std::endl;
  // std::cout << "nodo al que va: " << elementos[0][6] << std::endl;

  // std::cout << "simbolo de la transicion: " << elementos[1][3] << std::endl;
  // std::cout << "nodo al que va: " << elementos[1][4] << std::endl;
  // std::cout << "simbolo de la transicion: " << elementos[1][5] << std::endl;
  // std::cout << "nodo al que va: " << elementos[1][6] << std::endl;

  // std::cout << "simbolo de la transicion: " << elementos[2][3] << std::endl;
  // std::cout << "nodo al que va: " << elementos[2][4] << std::endl;
  // std::cout << "simbolo de la transicion: " << elementos[2][5] << std::endl;
  // std::cout << "nodo al que va: " << elementos[2][6] << std::endl;
  // std::cout << "simbolo de la transicion: " << elementos[2][7] << std::endl;
  // std::cout << "nodo al que va: " << elementos[2][8] << std::endl;

  tabla_de_transiciones.resize(nodos_);

  for (auto i = 0; i < nodos_; i++) {
    tabla_de_transiciones[i].resize(elementos_[i][2] - 48);
  }

  for (auto i = 0; i < tabla_de_transiciones.size(); i++) {
    int variable = 3;
    int variable2 = 4;
    for (auto j = 0; j < tabla_de_transiciones[i].size(); j++) {
      tabla_de_transiciones[i][j].first = elementos_[i][variable];
      tabla_de_transiciones[i][j].second = elementos_[i][variable2];
      // std::cout << "transiciones first: " <<
      // tabla_de_transiciones[i][j].first
      //           << std::endl;
      // std::cout << "transiciones second: " <<
      // tabla_de_transiciones[i][j].second
      //           << std::endl;
      // std::cout <<
      // "---------------------------------------------------------"
      //           << std::endl;
      variable += 2;
      variable2 += 2;
    }
  }

  tabla_de_transiciones_ = tabla_de_transiciones;
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
  os << "Estados finales: ";
  for (auto i = 0; i < estados_finales_.size(); i++) {
    os << estados_finales_[i] << " ";
  }
  os << std::endl;
  os << "Nodos no terminales: ";
  for (auto i = 0; i < estados_no_terminales_.size(); i++) {
    os << estados_no_terminales_[i] << " ";
  }
  os << std::endl;
  os << "Tabla de transiciones: " << std::endl;
  // os << "not yet" << std::endl;
  for (auto i = 0; i < tabla_de_transiciones_.size(); i++) {
    
    for (auto j = 0; j < tabla_de_transiciones_[i].size(); j++) {
      os << estados_no_terminales_[i] << " -> ";
      os << tabla_de_transiciones_[i][j].first << ""
         << tabla_de_transiciones_[i][j].second << std::endl;
    }
    os << std::endl;
  }
  // os << std::endl;
  // os << "Elementos: " << std::endl;
  // for (auto i = 0; i < elementos_.size(); i++) {
  //   os << elementos_[i] << std::endl;
  // }
  // os << std::endl;
}

// method to check if the class automata is a DFA
bool Automata::EsUnDfa() {
  if
}



// // method to check if the string is accepted by the automata
// bool Automata::CheckString(std::string string) {  // no está probada todavía
//   int nodo_actual = estado_inicial_ - 48;
//   int nodo_s = 0;
//   for (auto i = 0; i < string.size(); i++) {
//     for (auto j = 0; j < tabla_de_transiciones_[nodo_actual].size(); j++) {
//       if (string[i] == tabla_de_transiciones_[nodo_actual][j].first) {
//         nodo_actual = tabla_de_transiciones_[nodo_actual][j].second - 48;
//         break;
//       }
//     }
//   }
//   for (auto i = 0; i < elementos_[nodo_actual][1].size(); i++) {
//     if (elementos_[nodo_actual][1][i] == '1') {
//       return true;
//     }
//   }
//   return false;
// }

