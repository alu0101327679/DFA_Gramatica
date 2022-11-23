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
    LimpiarLinea(lines[i]);
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
void Gramatica::LimpiarLinea(std::string line) {
  std::string elemento = "";
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
  os << "Tabla de transiciones: " << tabla_de_producciones_.size() << std::endl;
  for (auto i = 0; i < tabla_de_producciones_.size(); i++) {
    for (auto j = 0; j < tabla_de_producciones_[i].size(); j++) {
      os << estados_no_terminales_[i] << " -> ";
      os << tabla_de_producciones_[i][j] << std::endl;
    }
    os << std::endl;
  }
  os << std::endl;

  os << "Estados terminales: ";
  for (auto i = 0; i < estados_terminales_.size(); i++) {
    os << estados_terminales_[i] << " ";
  }
  os << std::endl;

  os << "Estados no terminales: ";
  for (auto i = 0; i < estados_no_terminales_.size(); i++) {
    os << estados_no_terminales_[i] << " ";
  }
  os << std::endl;

  os << "Todos los estados no terminales: ";
  for (auto i = 0; i < todos_estados_no_terminales_.size(); i++) {
    os << todos_estados_no_terminales_[i] << " ";
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
    for (auto j = 1; j < elementos_[i].size(); j++) {
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
  tabla_de_producciones_ = tabla;
}

void Gramatica::FormaNormalDeChomsky() {
  Inutiles();
  Vacias();
  Unitarias();
  Inutiles();
  char vacio = ' ';
  bool insertar = true;
  int interacciones = 0;
  std::string valor_original = "";
  std::vector<std::string> anadir_en_tabla;

  for (auto i = 0; i < tabla_de_producciones_.size(); i++) {
    for (auto j = 0; j < tabla_de_producciones_[i].size(); j++) {
      if (tabla_de_producciones_[i][j].size() > 2) {
        // std::cout << tabla_de_producciones_[i][j] << std::endl;
        char random = rand() % 26 + 65;
        for (auto z = 0; z < estados_no_terminales_.size(); z++) {
          if (random == estados_no_terminales_[z]) {
            insertar = false;
          }
          interacciones++;
        }
        if (insertar) {
          estados_no_terminales_.push_back(random);
        }

        for (auto z = 0; z < todos_estados_no_terminales_.size(); z++) {
          if (random == todos_estados_no_terminales_[z]) {
            todos_estados_no_terminales_.erase(
                todos_estados_no_terminales_.begin() + z);
          }
        }  // borra los elementos de todos los estados no terminales

        valor_original = tabla_de_producciones_[i][j];
        // guardar los 2 ultimos valor de un string en otro string
        std::string value_holder2 = "";
        // for (auto k = 0; k < tabla_de_producciones_[i][j].size(); k++) {
        //   if (tabla_de_producciones_[i][j][k] == estados_terminales_[i]) {
        //     value_holder2 += tabla_de_producciones_[i][j][k];
        //     goto next;
        //   }
        // }
        // next:
        anadir_en_tabla.push_back(value_holder2);
        tabla_de_producciones_.push_back(anadir_en_tabla);
        anadir_en_tabla.clear();
        value_holder2 = "";
        valor_original = "";

      } else if (tabla_de_producciones_[i][j].size() == 2) {  // =2 carat
        // se comprueba si los 2 caracteres son no terminales no se hace nada
        // si uno de los 2 caracteres es terminal se crea un estado no terminal
        // que se le asigna a los 2 caracteres se sustituye en todas las
        // ocurrencias de la tabla de transiciones se anade a la tabla de
        // transiciones el nuevo estado no terminal

      }  // si tiene un caracter se supone que solo puede estar en la raiz
    }
  }
  // Inutiles();
  // Vacias();
  // Unitarias();
  // Inutiles();
  // char terminal = ' ';
  // bool insertar = true;
  // int interacciones = 0;
  // std::string valor_original = "";
  // std::vector<std::string> anadir_en_tabla;

  // // para cada valor terminal crea un nuevo estado no terminal y lo sustituye
  // en
  // // la tabla de transiciones

  // for (auto j = 0; j < tabla_de_producciones_.size(); j++) {
  //   for (auto k = 0; k < tabla_de_producciones_[j].size(); k++) {
  //     for (auto l = 0; l < tabla_de_producciones_[j][k].size(); l++) {
  //       if (tabla_de_producciones_[j][k].size() >= 2) {
  //         for (auto i = 0; i < tabla_de_producciones_[j][k].size(); i++) {
  //           if (tabla_de_producciones_[j][k][l] == estados_terminales_[i]) {
  //             char random = rand() % 26 + 65;
  //             AddProcuccion(estados_terminales_[i], random);
  //             RemplazarTerminal(tabla_de_producciones_[j], random);
  //           }
  //         }
  //       }
  //     }
  //   }
  // }

  // for (auto j = 0; j < tabla_de_producciones_.size(); j++) {
  //   for (auto k = 0; k < tabla_de_producciones_[j].size(); k++) {
  //     for (auto l = 0; l < tabla_de_producciones_[j][k].size(); l++) {
  //       if (tabla_de_producciones_[j][k].size() >= 3) {
  //         AddNoTerminales(tabla_de_producciones_[j].size());
  //         RemplazarNoTerminales(tabla_de_producciones_[j]);
  //       }
  //     }
  //   }
  // }
}

// void Gramatica::AddProcuccion(char estado_terminal, char random) {
// //añadir random a los estados no terminales, evitando que se repitan y
// borrando los de todos los estados no terminales
//   bool insertar = true;
//   for (auto i = 0; i < estados_no_terminales_.size(); i++) {
//     if (estados_no_terminales_[i] == random) {
//       insertar = false;
//     }
//   }
//   if (insertar) {
//     estados_no_terminales_.push_back(random);
//   }

//   // añadir el estado terminal a la tabla de transiciones
//   std::string estado_terminal_string = "";
//   estado_terminal_string += estado_terminal;
//   std::vector<std::string> tabla;
//   tabla.push_back(estado_terminal_string);
//   tabla_de_producciones_.push_back(tabla);

// }

// void Gramatica::RemplazarTerminal(std::vector<std::string>&
// estados_terminales,
//                                   char random) {}

// void Gramatica::AddNoTerminales(int size) {}

// void Gramatica::RemplazarNoTerminales(std::vector<std::string>& estados) {}

bool Gramatica::Inutiles() { return true; }

bool Gramatica::Vacias() { return true; }

bool Gramatica::Unitarias() { return true; }

// funcion Transformaci´on de una CFG a su Forma Normal de Chomsky
// 1. Eliminar las producciones in´utiles
// 2. Eliminar las producciones vac´ıas
// 3. Eliminar las producciones unitarias
// 4. Eliminar las producciones in´utiles
// 5. Transformar las producciones de m´as de dos s´ımbolos en producciones
// de dos s´ımbolos
// 6. Transformar las producciones de dos s´ımbolos en las que uno de ellos
// es terminal en producciones de dos s´ımbolos en las que ninguno de ellos
// es terminal
// 7. Transformar las producciones de dos s´ımbolos en las que ninguno de
// ellos es terminal en producciones de dos s´ımbolos en las que ambos son
// no terminales
// 8. Transformar las producciones de dos s´ımbolos en las que ambos son
// no terminales en producciones de un s´ımbolo en la ra´ız y dos s´ımbolos
// en las ramas
