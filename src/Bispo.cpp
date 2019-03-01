/*
 * Bispo.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */

#include "Bispo.hpp"
#include <cmath>
using std::abs;
Bispo::Bispo(char t_Cor) : Peca(t_Cor, 'B') {}

Bispo::~Bispo() {}

bool Bispo::verificaMovimento(int t_Xi, int t_Yi, int t_Xf, int t_Yf,
                              Peca* t_Tab[8][8], bool t_Come) const {
  if (abs(t_Xf - t_Xi) == abs(t_Yf - t_Yi)) {
    // Verifica se há peças no caminho até o destino final.
    // Caso haja, retorna false.
    // Caso t_Come seja true, não verifica a última casa; pois esta tem uma peça
    // e resultaria em um falso negativo
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
  }
  return false;
}
