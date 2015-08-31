/*
 * BMatrix.hpp
 *
 *  Created on: 2015/08/31
 *      Author: stomo
 */

#ifndef BMATRIX_HPP_
#define BMATRIX_HPP_

#include "Matrix.hpp"

class BMatrix : public Matrix {

protected:
	unsigned int ib_;	// block size

public:
	// Constructor
	BMatrix( const unsigned int m, const unsigned int n, const unsigned int ib );

	// Destructor
	virtual ~BMatrix();

	// Getters
	 unsigned int ib() { return ib_; }
};

#endif /* BMATRIX_HPP_ */
