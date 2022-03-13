/*
 * Dama.hpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */

#ifndef DAMA_HPP_
#define DAMA_HPP_

#include "Peca.hpp"

class Dama : public Peca {
public:
    Dama(char);

    virtual ~Dama();

    bool verificaMovimento(int, int, int, int, Peca *[8][8], bool) const;
};

#endif /* DAMA_HPP_ */
