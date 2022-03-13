/*
 * Tabuleiro.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */
#include <cstdlib>
#include <iostream>

using namespace std;

#include "Bispo.hpp"
#include "Cavalo.hpp"
#include "Dama.hpp"
#include "Peao.hpp"
#include "Rei.hpp"
#include "Tabuleiro.hpp"
#include "Torre.hpp"

/* Inicia as casa vazias com NULL.
Inicia as 16 peças brancas.
Inicia as 16 peças preta.*/
Tabuleiro::Tabuleiro()
        : m_Vez('B'), pecasComidasBranco(0), pecasComidasPreto(0) {
    // Seta as casas Vazias com NULL
    for (int i = 2; i < 6; ++i) {
        for (int j = 0; j < 8; ++j) {
            m_Tab[i][j] = NULL;
        }
    }

    // Seta as Brancas
    m_Tab[0][0] = new Torre('B');
    m_Tab[0][1] = new Cavalo('B');
    m_Tab[0][2] = new Bispo('B');
    m_Tab[0][3] = new Dama('B');
    m_Tab[0][4] = new Rei('B');
    m_Tab[0][5] = new Bispo('B');
    m_Tab[0][6] = new Cavalo('B');
    m_Tab[0][7] = new Torre('B');
    for (int i = 0; i < 8; ++i) {
        m_Tab[1][i] = new Peao('B');
    }

    // Seta as Pretas
    m_Tab[7][0] = new Torre('P');
    m_Tab[7][1] = new Cavalo('P');
    m_Tab[7][2] = new Bispo('P');
    m_Tab[7][3] = new Dama('P');
    m_Tab[7][4] = new Rei('P');
    m_Tab[7][5] = new Bispo('P');
    m_Tab[7][6] = new Cavalo('P');
    m_Tab[7][7] = new Torre('P');
    for (int i = 0; i < 8; ++i) {
        m_Tab[6][i] = new Peao('P');
    }
}

/* Deleta todas as casas */
Tabuleiro::~Tabuleiro() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete m_Tab[i][j];
        }
    }
}

void Tabuleiro::somaPecasComidas() {
    (getVez() == 'B' ? ++pecasComidasBranco : ++pecasComidasPreto);
}

int Tabuleiro::getPecasComidas(char t_Cor) {
    return (t_Cor == 'B' ? pecasComidasBranco : pecasComidasPreto);
}

char Tabuleiro::getVez() const {
    return m_Vez;
}

void Tabuleiro::trocaVez() {
    m_Vez = (m_Vez == 'B' ? 'P' : 'B');
}

/* Tenta mover a peça
Se consegue mover, move e retorna true
Caso contrário, retorna false

O parâmetro 'come' é false por padrã. Caso seja true, significa que a jogada vai
capturar uma peça adversária */
// QUANDO PEDE PRO PEÃO COMER, ELE PEGA O PRIMEIRO DISPONIVEL PARA COMER
// SOLUÇÃO? TEMPLATE ESPECIALIZADO PARA PEÃO PASSANDO A COLUNA
bool Tabuleiro::movePeca(char t_Peca, int t_Xf, int t_Yf, bool t_come) {
    // Caso haja uma peça na casa-destino e ela seja da mesma cor do jogador,
    // retorna false
    if (m_Tab[t_Yf][t_Xf] && m_Tab[t_Yf][t_Xf]->getCor() == m_Vez) {
        return false;
    }
    int Xi = -1, Yi = 0;

    while (achaPeca(t_Peca, Xi, Yi, m_Vez)) {
        if (m_Tab[Yi][Xi]->verificaMovimento(Xi, Yi, t_Xf, t_Yf, m_Tab, t_come)) {
            if (t_come) {
                delete m_Tab[t_Yf][t_Xf];
            }
            m_Tab[t_Yf][t_Xf] = m_Tab[Yi][Xi];
            m_Tab[Yi][Xi] = NULL;
            m_Tab[t_Yf][t_Xf]->somaMovimento();
            return true;
        }
    }
    return false;
}

/* Varre o tabuleiro procurando pela peça passada como argumento.
Caso encontre uma peça, é retornado true.
Caso contrário, é retornado false. */
bool Tabuleiro::achaPeca(char t_Peca, int &t_Xi, int &t_Yi, char t_Cor) const {
    while (t_Yi < 8) {
        // cout << t_Xi;
        for (t_Xi = (t_Xi < 8 ? t_Xi + 1 : 0); t_Xi < 8; ++t_Xi) {
            // Verifica se a casa está vazia. Em seguida verifica se a peça é igual à
            // desejada
            if (m_Tab[t_Yi][t_Xi] && m_Tab[t_Yi][t_Xi]->getPeca() == t_Peca) {
                if (m_Tab[t_Yi][t_Xi]->getCor() == t_Cor) {
                    return true;
                }
            }
        }
        ++t_Yi;
    }
    return false;
}

bool Tabuleiro::xeque(int t_Xf, int t_Yf, char t_Vez) {
    int Xi = 0, Yi = 0;
    // Acha a peça 'Rei' adversária e verifica se é possível o movimento até o rei
    if (achaPeca('R', Xi, Yi, (t_Vez == 'B' ? 'P' : 'B'))) {
        if (m_Tab[t_Yf][t_Xf]->verificaMovimento(t_Xf, t_Yf, Xi, Yi, m_Tab, true)) {
            return true;
        }
    }
    return false;
}

template<>
bool Tabuleiro::roque<true>() {
    int i = (getVez() == 'B' ? 0 : 7);
    if (m_Tab[i][0] && m_Tab[i][4]) {
        if (!m_Tab[i][0]->getMovimentos() && !m_Tab[i][4]->getMovimentos()) {
            if (m_Tab[i][0]->verificaMovimento(0, i, 3, i, m_Tab)) {
                m_Tab[i][2] = m_Tab[i][4];
                m_Tab[i][4] = NULL;
                m_Tab[i][2]->somaMovimento();
                m_Tab[i][3] = m_Tab[i][0];
                m_Tab[i][0] = NULL;
                m_Tab[i][3]->somaMovimento();
                return true;
            }
        }
    }
    return false;
}

template<>
bool Tabuleiro::roque<false>() {
    int i = (getVez() == 'B' ? 0 : 7);
    if (m_Tab[i][7] && m_Tab[i][4]) {
        if (!m_Tab[i][7]->getMovimentos() && !m_Tab[i][4]->getMovimentos()) {
            if (m_Tab[i][7]->verificaMovimento(7, i, 5, i, m_Tab)) {
                m_Tab[i][6] = m_Tab[i][4];
                m_Tab[i][4] = NULL;
                m_Tab[i][6]->somaMovimento();
                m_Tab[i][5] = m_Tab[i][7];
                m_Tab[i][7] = NULL;
                m_Tab[i][5]->somaMovimento();
                return true;
            }
        }
    }
    return false;
}

bool Tabuleiro::promocao(char t_Promo, int t_Xf, int t_Yf) {
    int auxMovimentos = m_Tab[t_Yf][t_Xf]->getMovimentos();
    delete m_Tab[t_Yf][t_Xf];

    switch (t_Promo) {
        case 'B':
            m_Tab[t_Yf][t_Xf] = new Bispo(getVez());
            break;
        case 'C':
            m_Tab[t_Yf][t_Xf] = new Cavalo(getVez());
            break;
        case 'D':
            m_Tab[t_Yf][t_Xf] = new Dama(getVez());
            break;
        case 'T':
            m_Tab[t_Yf][t_Xf] = new Torre(getVez());
            break;
        default:
            return false;
    }
    for (int i = 0; i < auxMovimentos; ++i) {
        m_Tab[t_Yf][t_Xf]->somaMovimento();
    }
    return true;
}

bool Tabuleiro::desambiguacao(char t_Peca, char t_Col, int t_Xf, int t_Yf,
                              bool t_come) {   // Recebe se come ou não
    int col = t_Col - 'a';
    if (m_Tab[t_Yf][t_Xf] && m_Tab[t_Yf][t_Xf]->getCor() == m_Vez) {
        return false;
    }
    int Yi = 0;
    while (Yi < 8) {
        if (m_Tab[Yi][col] && m_Tab[Yi][col]->getPeca() == t_Peca &&
            m_Tab[Yi][col]->getCor() == getVez()) {
            if (m_Tab[Yi][col]->verificaMovimento(col, Yi, t_Xf, t_Yf, m_Tab,
                                                  t_come)) {
                if (t_come) {
                    delete m_Tab[t_Yf][t_Xf];
                }
                m_Tab[t_Yf][t_Xf] = m_Tab[Yi][col];
                m_Tab[Yi][col] = NULL;
                m_Tab[t_Yf][t_Xf]->somaMovimento();
                return true;
            }
        }
        ++Yi;
    }
    return false;
}

bool Tabuleiro::desambiguacao(char t_Peca, int t_Lin, int t_Xf, int t_Yf,
                              bool t_come) {   // Recebe se come ou não
    if (m_Tab[t_Yf][t_Xf] && m_Tab[t_Yf][t_Xf]->getCor() == m_Vez) {
        return false;
    }
    int Xi = 0;
    while (Xi < 8) {
        if (m_Tab[t_Lin][Xi] && m_Tab[t_Lin][Xi]->getPeca() == t_Peca &&
            m_Tab[t_Lin][Xi]->getCor() == getVez()) {
            if (m_Tab[t_Lin][Xi]->verificaMovimento(Xi, t_Lin, t_Xf, t_Yf, m_Tab,
                                                    t_come)) {
                if (t_come) {
                    delete m_Tab[t_Yf][t_Xf];
                }
                m_Tab[t_Yf][t_Xf] = m_Tab[t_Lin][Xi];
                m_Tab[t_Lin][Xi] = NULL;
                m_Tab[t_Yf][t_Xf]->somaMovimento();
                return true;
            }
        }
        ++Xi;
    }
    return false;
}

bool Tabuleiro::enPassant(int t_col, int t_Xf, int t_Yf) {
    if (!m_Tab[t_Yf][t_Xf]) {
        int Yi = 0;
        while (Yi < 8) {
            if (m_Tab[Yi][t_col] && m_Tab[Yi][t_col]->getPeca() == 'P' &&
                m_Tab[Yi][t_col]->getCor() == getVez()) {
                if (m_Tab[Yi][t_col]->verificaMovimento(t_col, Yi, t_Xf, t_Yf, m_Tab,
                                                        true)) {
                    if (m_Tab[Yi][t_Xf] && m_Tab[Yi][t_Xf]->getPeca() == 'P' &&
                        m_Tab[Yi][t_Xf]->getMovimentos() == 1) {
                        delete m_Tab[Yi][t_Xf];
                        m_Tab[Yi][t_Xf] = NULL;
                        m_Tab[t_Yf][t_Xf] = m_Tab[Yi][t_col];
                        m_Tab[Yi][t_col] = NULL;
                        m_Tab[t_Yf][t_Xf]->somaMovimento();
                        return true;
                    }
                }
            }
            ++Yi;
        }
    }
    return false;
}

void Tabuleiro::printTab() {
    system("clear");
    cout << "Vez: \033[1;" << (getVez() == 'B' ? "36mBranco" : "35mPreto")
         << "\033[0m" << endl;
    cout << "  ABCDEFGH" << endl;
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 12; ++j) {
            if (j == 0 || j == 11) {
                cout << i + 1;
            } else if (j == 1 || j == 10) {
                cout << ' ';
            } else if (m_Tab[i][j - 2]) {
                if ((i + j) % 2 != 0) {
                    cout << "\033[47;";
                } else {
                    cout << "\033[40;";
                }
                if (m_Tab[i][j - 2]->getCor() == 'B') {
                    cout << "36m" << m_Tab[i][j - 2]->getPeca() << "\033[0m";
                } else {
                    cout << "35m" << m_Tab[i][j - 2]->getPeca() << "\033[0m";
                }
            } else {
                if ((i + j) % 2 != 0) {
                    cout << "\033[47;";
                } else {
                    cout << "\033[40;";
                }
                cout << "35m" << ' ' << "\033[0m";
            }
        }
        cout << endl;
    }
    cout << "  ABCDEFGH\n" << endl;
}
