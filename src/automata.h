#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class Automata
{
  private:
    int nodos_;
    int estado_inicial_;
    // std::vector<int> estados_finales_;
    std::vector<char> simbolos_;
    std::vector<std::string> elementos_;
    std::vector<std::vector<std::pair<int,char>>> tabla_de_transiciones_;

  public:
    Automata();
    ~Automata();
    void Analizar(std::string);
    void Mostrar(std::ostream& os);
    std::vector<char> Split(std::string);
    void SetSimbolos(std::string);
    void SetNumerodeNodos(std::string);
    void SetEstadoArranque(std::string);
    void SepararElementos(std::string);
    void SetTablaDeTransiciones();

};
