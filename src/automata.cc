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
  SetSimbolos(lines[0]);
  SetNumerodeNodos(lines[1]);
  SetEstadoArranque(lines[2]);
  for (auto i = 3; i < nodos_ + 3; i++) {
    SepararElementos(lines[i]);
  }
  // std::cout << "Hola" << std::endl;
  SetTablaDeTransiciones();
}


/// @brief añaade los simbolos del alfabeto al automata
/// @param line 
void Automata::SetSimbolos(std::string line) {
  std::vector<char> simbolos;
  for (auto i = 0; i < line.size(); i++) {
    if (line[i] != ' ') {
      simbolos.push_back(line[i]);
    }
  }
  simbolos_ = simbolos;
}


/// @brief set el numero de nodos del automata
/// @param line 
void Automata::SetNumerodeNodos(std::string line) {
  std::stringstream ss(line);
  ss >> nodos_;
}

/// @brief set el estado inicial del automata
/// @param line 
void Automata::SetEstadoArranque(std::string line) {
  std::stringstream ss(line);
  ss >> estado_inicial_;
}

/// @brief set estados finales del automata
/// @param member 
void Automata::SetEstadoFinal(char member) {
  estados_finales_.push_back(member);
}

/// @brief separa los elementos de la linea
/// @param line 
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

/// @brief set la tabla de transiciones
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

/// @brief comprueba si el fichero de entrada representa un DFA
/// @return 
bool Automata::EsUnDfa() {
  int contador = 0;
  // std::cout << elementos_.size() << std::endl;
  // std::cout << nodos_ << std::endl;
  if (elementos_.size() != nodos_) {
    return false;
  }
  // std::cout << "Cantidad de simbolos: " << simbolos_.size() << std::endl;

  for (auto i = 0; i < elementos_.size(); i++) {
    if (elementos_[i][2] - 48 != simbolos_.size()) {
      // std::cout << "Cantidad de enlaces: " << elementos_[i][2] << std::endl;
      contador++;
      // std::cout <<  "Contador: " << contador << std::endl;
    }
  }

  if (contador > 1) {
    return false;
  }

  for (auto i = 0; i < tabla_de_transiciones_.size(); i++) {
    int variable = 3;
    int variable2 = 4;
    int counter = 0;
    for (auto j = 0; j < tabla_de_transiciones_[i].size(); j++) {
      for (auto z = 0; z < tabla_de_transiciones_[i].size(); z++) {
        if (tabla_de_transiciones_[i][j].first ==
            tabla_de_transiciones_[i][z].first) {
          // std::cout << "tabla_de_transiciones[" << i << "][" << j << "].fisrt
          // "
          //           << tabla_de_transiciones_[i][j].first << std::endl;
          // std::cout << "  tabla_de_transiciones[" << i << "][" << z
          //           << "].fisrt  " << tabla_de_transiciones_[i][z].first
          //           << std::endl;
          counter++;
        }
      }
    }
    // std::cout << "counter: " << counter << std::endl;
    // std::cout << "elementos[" << i << "][2] " << elementos_[i][2] <<
    // std::endl;
    if (counter != elementos_[i][2] - 48) {
      return false;
    }
  }

  return true;
}

/// @brief muestra por donde se especifique los datos del automata
/// @param os 
void Automata::Mostrar(std::ostream& os) {
  if (EsUnDfa()) {
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
    os << std::endl;
    os << "Elementos: " << std::endl;
    for (auto i = 0; i < elementos_.size(); i++) {
      os << elementos_[i] << std::endl;
    }
    os << std::endl;
  } else {
    os << "El automata no es un DFA" << std::endl;
  }
}

/// @brief imprime por fichero la gramatica del automata
/// @param os 
void Automata::ImprimirFichero(std::ostream& os) {
  for (auto i = 0; i < tabla_de_transiciones_.size(); i++) {
    for (auto j = 0; j < tabla_de_transiciones_[i].size(); j++) {
      os << estados_no_terminales_[i] << " -> ";
      os << tabla_de_transiciones_[i][j].first << ""
         << tabla_de_transiciones_[i][j].second << std::endl;
    }
    os << std::endl;
  }
}

/// @brief comprueba si el string dado es aceptado por el automata / gramatica
/// @param string 
/// @return 
bool Automata::CheckString(std::string string) {  // no está probada todavía
  char estado_actual = estado_inicial_;
  char estado_siguiente;

  // comprobar que el ultimo estado vistado al comprobar la cadena es un estado
  // final
  for (auto i = 0; i < string.size(); i++) {
    for (auto j = 0; j < tabla_de_transiciones_.size(); j++) {
      for (auto k = 0; k < tabla_de_transiciones_[j].size(); k++) {
        if (estado_actual == estados_no_terminales_[j]) {
          if (string[i] == tabla_de_transiciones_[j][k].first) {
            estado_siguiente = tabla_de_transiciones_[j][k].second;
            estado_actual = estado_siguiente;
          }
        }
      }
    }
  }

  for (auto i = 0; i < estados_finales_.size(); i++) {
    if (estado_actual == estados_finales_[i]) {
      return true;
    }
  }

  return false;
}
