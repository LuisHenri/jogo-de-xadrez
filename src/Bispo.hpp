/*
 * Bispo.hpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */

#ifndef BISPO_HPP_
#define BISPO_HPP_

#include "Peca.hpp"

class Bispo : public Peca {
public:
    Bispo(char);

    virtual ~Bispo();

    bool verificaMovimento(int, int, int, int, Peca *[8][8], bool) const;
};

#endif /* BISPO_HPP_ */
