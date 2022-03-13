/*
 * Torre.hpp
 *
 *  Created on: Oct 26, 2018
 *      Author: luishenri
 */

#ifndef TORRE_HPP_
#define TORRE_HPP_

#include "Peca.hpp"

class Torre : public Peca {
public:
    Torre(char);

    virtual ~Torre();

    bool verificaMovimento(int, int, int, int, Peca *[8][8], bool) const;
};

#endif /* TORRE_HPP_ */
