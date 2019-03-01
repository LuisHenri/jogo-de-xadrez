#ifndef IO_JOGO_HPP_
#define IO_JOGO_HPP_

#include <string>
using std::string;
#include "Tabuleiro.hpp"
// class Tabuleiro;

class IO_Jogo {
private:
  Tabuleiro m_Tabuleiro;

public:
  IO_Jogo();
  ~IO_Jogo();
  void Interface();   // O que o usuário quer
  void jogaJogo();
  void jogaJogo(string);
};

#endif
