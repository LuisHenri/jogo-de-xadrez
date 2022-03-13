/*
 * Tabuleiro.hpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */

#ifndef TABULEIRO_HPP_
#define TABULEIRO_HPP_

#include "Peca.hpp"
// class Peca;   // Como ele sabe dos métodos sem o include?

class Tabuleiro {
private:
    Peca *m_Tab[8][8];   // Como ele sabe da existência dessa classe sem o include
    char m_Vez;
    int pecasComidasBranco;
    int pecasComidasPreto;

public:
    // PODEMOS CRIAR UM CONSTRUTOR QUE RECEBE UMA STRING COM O NOME DO ARQUIVO A
    // SER LIDO
    Tabuleiro();

    ~Tabuleiro();

    void somaPecasComidas();

    int getPecasComidas(char);

    char getVez() const;

    void trocaVez();

    bool movePeca(char, int, int, bool = false);

    bool achaPeca(char, int &, int &, char) const;

    bool xeque(int, int, char);

    template<bool>
    bool roque();

    bool promocao(char, int, int);

    bool desambiguacao(char, char, int, int,
                       bool = false);   // Peão, Bispo, Cavalo, Torre
    bool desambiguacao(char, int, int, int,
                       bool = false);   // Peão, Bispo, Cavalo, Torre
    bool enPassant(int, int, int);

    void printTab();
};

#endif /* TABULEIRO_HPP_ */
