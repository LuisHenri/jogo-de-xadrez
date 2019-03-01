//============================================================================
// Name        : Xadrez.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "Bispo.hpp"
#include "Cavalo.hpp"
#include "Dama.hpp"
#include "IO_Jogo.hpp"
#include "Peao.hpp"
#include "Rei.hpp"
#include "Tabuleiro.hpp"
#include "Torre.hpp"

// X = colunas [j]
// Y = linhas [i]
int main() {
  IO_Jogo JogoDeXadrez;
  JogoDeXadrez.Interface();
}
