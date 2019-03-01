/*
 * Peao.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */

#include "Peao.hpp"
#include <cmath>
using std::abs;
Peao::Peao(char t_Cor) : Peca(t_Cor, 'P') {}

Peao::~Peao() {}

bool Peao::verificaMovimento(int t_Xi, int t_Yi, int t_Xf, int t_Yf,
                             Peca* t_Tab[8][8], bool t_Come) const {
  if (t_Come && abs(t_Xf - t_Xi) == 1) {
    if (getCor() == 'B' && (t_Yf - t_Yi == 1)) {
      return true;
    } else if (getCor() == 'P' && (t_Yf - t_Yi == -1)) {
      return true;
    }
  }

  if (t_Xf == t_Xi) {
    if (getCor() == 'B' && t_Yf > t_Yi) {
      if ((t_Yf - t_Yi == 2 && getMovimentos() == 0) || t_Yf - t_Yi == 1) {
        return true;
      }
    } else if (getCor() == 'P' && t_Yf < t_Yi) {
      if ((t_Yf - t_Yi == -2 && getMovimentos() == 0) || t_Yf - t_Yi == -1) {
        return true;
      }
    }
  }
  return false;
}
