/*
 * Peao.hpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */

#ifndef PEAO_HPP_
#define PEAO_HPP_

#include "Peca.hpp"

class Peao : public Peca {
public:
  Peao(char);
  virtual ~Peao();
  bool verificaMovimento(int, int, int, int, Peca * [8][8], bool) const;
};

#endif /* PEAO_HPP_ */
