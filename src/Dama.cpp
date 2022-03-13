/*
 * Dama.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */

#include "Dama.hpp"
#include <cmath>

using std::abs;

Dama::Dama(char t_Cor) : Peca(t_Cor, 'D') {}

Dama::~Dama() {}

bool Dama::verificaMovimento(int t_Xi, int t_Yi, int t_Xf, int t_Yf,
                             Peca *t_Tab[8][8], bool t_Come) const {
    if (abs(t_Xf - t_Xi) == abs(t_Yf - t_Yi)) {
        int condicaoParada = t_Xf;
        if (t_Come) {
            (t_Xf - t_Xi > 0 ? --condicaoParada : ++condicaoParada);
            if (abs(t_Xf - t_Xi) == 1) {
                return true;
            }
        }
        for (int i = (t_Yf - t_Yi > 0 ? t_Yi + 1 : t_Yi - 1),
                     j = (t_Xf - t_Xi > 0 ? t_Xi + 1 : t_Xi - 1);
             j != condicaoParada;
             (t_Yf - t_Yi > 0 ? ++i : --i), (t_Xf - t_Xi > 0 ? ++j : --j)) {
            if (t_Tab[i][j]) {
                return false;
            }
        }
        return true;
    } else if (t_Yf == t_Yi) {
        int condicaoParada = t_Xf;
        if (t_Come) {
            (t_Xf - t_Xi > 0 ? --condicaoParada : ++condicaoParada);
            if (abs(t_Xf - t_Xi) == 1) {
                return true;
            }
        }
        for (int j = (t_Xf - t_Xi > 0 ? t_Xi + 1 : t_Xi - 1); j != condicaoParada;
             (t_Xf - t_Xi > 0 ? ++j : --j)) {
            if (t_Tab[t_Yi][j]) {
                return false;
            }
        }
        return true;
    } else if (t_Xf == t_Xi) {
        int condicaoParada = t_Yf;
        if (t_Come) {
            (t_Yf - t_Yi > 0 ? --condicaoParada : ++condicaoParada);
            if (abs(t_Yf - t_Yi) == 1) {
                return true;
            }
        }
        for (int i = (t_Yf - t_Yi > 0 ? t_Yi + 1 : t_Yi - 1); i != condicaoParada;
             (t_Yf - t_Yi > 0 ? ++i : --i)) {
            if (t_Tab[i][t_Xi]) {
                return false;
            }
        }
        return true;
    }
    return false;
}
