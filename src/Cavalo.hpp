/*
 * Cavalo.hpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */

#ifndef CAVALO_HPP_
#define CAVALO_HPP_

#include "Peca.hpp"

class Cavalo : public Peca {
public:
    Cavalo(char);

    virtual ~Cavalo();

    bool verificaMovimento(int, int, int, int, Peca *[8][8], bool) const;
};

#endif /* CAVALO_HPP_ */
