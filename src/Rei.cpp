/*
 * Rei.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */

#include "Rei.hpp"

Rei::Rei(char t_Cor) : Peca(t_Cor, 'R') {}

Rei::~Rei() {}

bool Rei::verificaMovimento(int t_Xi, int t_Yi, int t_Xf, int t_Yf,
                            Peca *t_Tab[8][8], bool t_Come) const {
    if (t_Xf == t_Xi + 1 || t_Xf == t_Xi - 1 || t_Yf == t_Yi + 1 ||
        t_Yf == t_Yi - 1) {
        return true;
    }
    return false;
}
