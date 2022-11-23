#include "gramatica.h"

Gramatica::Gramatica() {}

Gramatica::~Gramatica() {}

/// @brief Analiza el fichero de entrada y guarda los datos en el gramatica
/// @param nombre
void Gramatica::Analizar(std::string nombre) {
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
  FormaNormalDeChomsky();
  file.close();
}

void Gramatica::SepararNoTerminales(std::string line) {
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

void Gramatica::SepararSiTerminales() {
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
}

/// @brief separa los elementos de la linea
/// @param line
void Gramatica::SepararElementos(std::string line) {
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

/// @brief muestra por donde se especifique los datos del gramatica
/// @param os
void Gramatica::Mostrar(std::ostream& os) {
  os << "Tabla de transiciones: " << std::endl;
  for (auto i = 0; i < tabla_de_transiciones_.size(); i++) {
    for (auto j = 0; j < tabla_de_transiciones_[i].size(); j++) {
      os << estados_no_terminales_[i] << " -> ";
      os << tabla_de_transiciones_[i][j] << std::endl;
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

/// @brief set la tabla de transiciones separando los elementos con una |
void Gramatica::SetTablaDeTransiciones() {
  std::string elemento = "";
  std::vector<std::string> falsa_tabla;
  std::vector<std::vector<std::string>> tabla;
  for (auto i = 0; i < elementos_.size(); i++) {
    for (auto j = 1; j <= elementos_[i].size(); j++) {
      if (elementos_[i][j] != '|') {
        elemento += elementos_[i][j];
      } else {
        falsa_tabla.push_back(elemento);
        elemento = "";
      }
    }
    falsa_tabla.push_back(elemento);
    elemento = "";
    tabla.push_back(falsa_tabla);
    falsa_tabla.clear();
  }
  tabla_de_transiciones_ = tabla;
}

void Gramatica::FormaNormalDeChomsky() {
  Inutiles();
  Vacias();
  Unitarias();
  Inutiles();
  // funcion que pasa a la forma normal de chomsky una gramatica

  for (auto i = 0; i < tabla_de_transiciones_.size(); i++) {
    for (auto j = 0; j < tabla_de_transiciones_[i].size(); j++) {
      if (tabla_de_transiciones_[i][j].size() > 2) { //si el elemento tiene mas de 2 caracteres
        //se crea un estado no terminal que se le asigna a los 2 ultimos elemementos
        //se sustituye en todas las ocurrencias de la tabla de transiciones
        //se añade a la tabla de transiciones el nuevo estado no terminal
      }else if (tabla_de_transiciones_[i][j].size() == 2) {//si el elemento tiene 2 caracteres
        //se comprueba si los 2 caracteres son no terminales no se hace nada
        //si uno de los 2 caracteres es terminal se crea un estado no terminal que se le asigna a los 2 caracteres
        //se sustituye en todas las ocurrencias de la tabla de transiciones
        //se añade a la tabla de transiciones el nuevo estado no terminal

      }//si tiene un caracter se supone que solo puede estar en la raiz
    }
  }
}

bool Gramatica::Inutiles() { return true; }

bool Gramatica::Vacias() { return true; }

bool Gramatica::Unitarias() { return true; }
