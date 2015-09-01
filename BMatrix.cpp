/*
 * BMatrix.cpp
 *
 *  Created on: 2015/08/31
 *      Author: stomo
 */

#include <iostream>
#include <cassert>
#include "BMatrix.hpp"

using namespace std;

/**
 * Constructor
 *
 * @param m number of lows of the matrix
 * @param n number of columns of the matrix
 */
BMatrix::BMatrix( const unsigned int m, const unsigned int n, const unsigned int ib ) : Matrix(m,n)
{
//	cout << "BMatrix()\n";

	assert( ib > 0 );
	assert( ib < m );

	ib_ = ib;
}

/**
 * Destructor
 *
 */
BMatrix::~BMatrix()
{
//	cout << "~BMatrix()\n";
}
