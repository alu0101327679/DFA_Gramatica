#include "automata.h"

Automata::Automata()
{
}

Automata::~Automata()
{
}

void Automata::analizar(std::string nombre)
{
    std::ifstream file(nombre);
    std::string line;
    int line_number = 0;
    while (std::getline(file, line))
    {
        line_number++;
        std::cout << line_number << " " << line << std::endl;
    }
}

void Automata::mostrar(std::ostream& os)
{
  os << "Nombre del programa: " << nombre_ << std::endl;
  os << "Descripcion: " << descripcion_.contenido << std::endl;
  os << "Comentarios: " << std::endl;
  for (auto& comentario : comentarios_)
  {
    os << "Linea " << comentario.linea << ": " << comentario.contenido << std::endl;
  }
  os << "Bucles: " << std::endl;
  for (auto& bucle : bucles_)
  {
    os << "Linea " << bucle.linea << ": " << bucle.contenido << std::endl;
  }
  os << "Variables: " << std::endl;
  for (auto& variable : variables_)
  {
    os << "Linea " << variable.linea << ": " << variable.contenido << std::endl;
  }
  os << "Expresiones: " << std::endl;
  for (auto& expresion : expresiones_)
  {
    os << "Linea " << expresion.linea << ": " << expresion.contenido << std::endl;
  }
}