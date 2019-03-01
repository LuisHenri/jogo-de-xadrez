/*
 * Peca.hpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */

#ifndef PECA_HPP_
#define PECA_HPP_

class Peca {
private:
  char m_Cor;    //(B)anca, (P)reta
  char m_Peca;   //(B)ispo, (C)avalo, (D)ama, (P)eão, (R)ei, (T)orre
  int  movimentos;

public:
  Peca(char, char);
  virtual ~Peca();
  char         getCor() const;
  char         getPeca() const;
  void         somaMovimento();
  int          getMovimentos() const;
  virtual bool verificaMovimento(int, int, int, int, Peca * [8][8],
                                 bool = 0) const = 0;
};

#endif /* PECA_HPP_ */
