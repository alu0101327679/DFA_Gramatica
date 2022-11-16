#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

struct data {
    int linea;
    std::string contenido;
    std::string tipo;
};

class Automata
{
  private:
    bool main_bool_ = false;
    data descripcion_;
    std::vector<data> comentarios_;
    std::vector<data> bucles_;
    std::vector<data> variables_;
    std::vector<data> expresiones_;
    std::string nombre_;

  public:
    Automata();
    ~Automata();
    void analizar(std::string);
    void mostrar(std::ostream& os);
};
