/*
 * Cavalo.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */
// Eu sou um cavalo
#include "Cavalo.hpp"

Cavalo::Cavalo(char t_Cor) : Peca(t_Cor, 'C') {}

Cavalo::~Cavalo() {}

bool Cavalo::verificaMovimento(int t_Xi, int t_Yi, int t_Xf, int t_Yf,
                               Peca *t_Tab[8][8], bool t_Come) const {
    if (t_Xf == t_Xi - 1 || t_Xf == t_Xi + 1) {
        if (t_Yf == t_Yi - 2 || t_Yf == t_Yi + 2) {
            return true;
        }
    } else if (t_Xf == t_Xi - 2 || t_Xf == t_Xi + 2) {
        if (t_Yf == t_Yi - 1 || t_Yf == t_Yi + 1) {
            return true;
        }
    }
    return false;
}
