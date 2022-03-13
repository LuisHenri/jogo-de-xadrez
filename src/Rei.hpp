/*
 * Rei.hpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */

#ifndef REI_HPP_
#define REI_HPP_

#include "Peca.hpp"

class Rei : public Peca {
public:
    Rei(char);

    virtual ~Rei();

    bool verificaMovimento(int, int, int, int, Peca *[8][8], bool) const;
};

#endif /* REI_HPP_ */
