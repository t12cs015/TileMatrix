/*
 * TMatrix.cpp
 *
 *  Created on: 2015/08/31
 *      Author: stomo
 */

#include <cassert>
#include <iostream>

#include "TMatrix.hpp"

/**
 * Constructor
 *
 * @param m number of lows of the matrix
 * @param n number of columns of the matrix
 */
TMatrix::TMatrix( const unsigned int M, const unsigned int N,
		const unsigned int mb, const unsigned int nb,
		const unsigned int ib )
{
	assert( M > 0 && N > 0 && mb > 0 && nb > 0 && ib > 0);
	assert( mb < M && nb < N && ib < nb );

	M_ = M;
	N_ = N;
	mb_ = mb;
	nb_ = nb;
	p_ = M_ % mb_ == 0 ? M_ / mb_ : M_ / mb_ + 1;
	q_ = N_ % nb_ == 0 ? N_ / nb_ : N_ / nb_ + 1;

	top_ = new BMatrix* [ p_ * q_ ];

	if (top_ == NULL)
	{
		std::cerr << "Can't allocate memory space for TMatrix class¥n";
		exit(EXIT_FAILURE);
	}
	else
		for (unsigned int i=0; i<p_; i++)
			for (unsigned int j=0; j<q_; j++)
			{
				unsigned int tm = ( i != p_-1 ) ? mb_ : M_ - i * mb_;
				unsigned int tn = ( j != q_-1 ) ? nb_ : N_ - j * nb_;
				top_[ i + j * p_ ] = new BMatrix( tm, tn, ib );
			}
}

/**
 * Destructor
 *
 */
TMatrix::~TMatrix()
{
	std::cout << "~TMatrix()\n";

	for (unsigned int i=0; i<p_; i++)
		for (unsigned int j=0; j<q_; j++)
		{
//			std::cout << "(" << i << "," << j << ")" << std::endl;
			operator delete [] (top_[ i + j * p_ ]);
		}
	operator delete [] (top_);
}

/**
 * Operator overload ()
 *
 * @param i low index
 * @param j column index
 */
BMatrix* TMatrix::operator()( const unsigned int i, const unsigned int j ) const
{
	assert( i > 0 && j > 0 );
	assert( i < p_ && j < q_ );

	return top_[ i + j * p_ ];
}
