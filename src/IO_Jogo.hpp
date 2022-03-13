#ifndef IO_JOGO_HPP_
#define IO_JOGO_HPP_

#include <string>
#include "Tabuleiro.hpp"

class IO_Jogo {
private:
    Tabuleiro m_Tabuleiro;

public:
    IO_Jogo();

    ~IO_Jogo();

    void Interface();   // O que o usuário quer
    void jogaJogo();

    void jogaJogo(std::string);
};

#endif
