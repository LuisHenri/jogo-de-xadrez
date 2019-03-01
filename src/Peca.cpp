/*
 * Peca.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */

#include "Peca.hpp"

Peca::Peca(char t_Cor, char t_Peca)
  : m_Cor(t_Cor), m_Peca(t_Peca), movimentos(0) {}

Peca::~Peca() {}

char Peca::getCor() const {
  return m_Cor;
}

char Peca::getPeca() const {
  return m_Peca;
}

void Peca::somaMovimento() {
  ++movimentos;
}

int Peca::getMovimentos() const {
  return movimentos;
}
