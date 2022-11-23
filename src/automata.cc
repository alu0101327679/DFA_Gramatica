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
    SepararNoTerminales(lines[i]);
  }
  SepararSiTerminales();
  SetTablaDeTransiciones();
  file.close();
}

void Automata::SepararNoTerminales(std::string line) {
  for (auto i = 0; i < line.size(); i++) {
    for (auto j = 0; j < todos_estados_no_terminales_.size(); j++) {
      if (line[i] == todos_estados_no_terminales_[j]) {  // comprueba si el
                                                         // estado no terminal
                                                         // esta en la linea
        estados_no_terminales_.push_back(todos_estados_no_terminales_[j]);
        todos_estados_no_terminales_.erase(
            todos_estados_no_terminales_.begin() + j);
      }
    }
  }
}

void Automata::SepararSiTerminales() {
  bool ignorar = false;
  bool ignorar2 = false;
  for (auto i = 0; i < elementos_.size(); i++) {
    for (auto j = 0; j < elementos_[i].size(); j++) {
      for (auto k = 0; k < estados_no_terminales_.size(); k++) {
        if (elementos_[i][j] == estados_no_terminales_[k]) {
          ignorar = true;
          goto next;
        } else {
          ignorar = false;
        }
      }
    next:
      if (!ignorar) {
        for (auto l = 0; l < estados_terminales_.size(); l++) {
          if (elementos_[i][j] == estados_terminales_[l]) {
            ignorar2 = true;
            goto next2;
          } else {
            ignorar2 = false;
          }
        }
      next2:
        if ((!ignorar2) && (elementos_[i][j] != '|')) {
          estados_terminales_.push_back(elementos_[i][j]);
        }
      }
    }
  }
  std::cout << std::endl;
}

/// @brief separa los elementos de la linea
/// @param line
void Automata::SepararElementos(std::string line) {
  std::string elemento;
  std::string elemento2;
  for (auto i = 0; i < line.size(); i++) {
    if ((line[i] != ' ') && (line[i] != '-') && (line[i] != '>')) {
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

    os << "Tabla de transiciones: " << std::endl;
  for (auto i = 0; i < tabla_de_transiciones_.size(); i++) {
    for (auto j = 0; j < tabla_de_transiciones_[i].size(); j++) {
      os << estados_no_terminales_[i] << " -> ";
      os << tabla_de_transiciones_[i][j].first << ""
         << tabla_de_transiciones_[i][j].second << std::endl;
    }
    os << std::endl;
  }
  os << std::endl;

  os << "Esatdos terminales: ";
  for (auto i = 0; i < estados_terminales_.size(); i++) {
    os << estados_terminales_[i] << " ";
  }
  os << std::endl;

  os << "Estados no terminales: ";
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

/// @brief set la tabla de transiciones
void Automata::SetTablaDeTransiciones() {
  std::vector<std::vector<std::pair<char, char>>> tabla_de_transiciones;
  std::vector<std::string> elementos;
  elementos.resize(elementos_.size());
  for (auto i = 0; i < elementos_.size(); i++) {
    elementos[i] = elementos_[i];
  }

  tabla_de_transiciones.resize(elementos_.size());

  for (auto i = 0; i < elementos.size(); i++) {
    tabla_de_transiciones[i].resize(elementos[i][2] - 48);
  }

  for (auto i = 0; i < tabla_de_transiciones.size(); i++) {
    int variable = 3;
    int variable2 = 4;
    for (auto j = 0; j < tabla_de_transiciones[i].size(); j++) {
      tabla_de_transiciones[i][j].first = elementos[i][variable];
      tabla_de_transiciones[i][j].second = elementos[i][variable2];

      variable += 2;
      variable2 += 2;
    }
  }

  tabla_de_transiciones_ = tabla_de_transiciones;
}