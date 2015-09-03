/*
 * TMatrix.cpp
 *
 *  Created on: 2015/08/31
 *      Author: stomo
 */

#include <iostream>
#include <cstdlib>
#include <cassert>
#include "TMatrix.hpp"

using namespace std;

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
#ifdef DEBUG
	cout << "TMatrix(M,N,mb,nb,ib)\n";
#endif

	assert( M > 0 && N > 0 && mb > 0 && nb > 0 && ib > 0);
	assert( mb < M && nb < N && ib < nb );

	M_ = M;
	N_ = N;
	mb_ = mb;
	nb_ = nb;
	p_ = M_ % mb_ == 0 ? M_ / mb_ : M_ / mb_ + 1;
	q_ = N_ % nb_ == 0 ? N_ / nb_ : N_ / nb_ + 1;

	try
	{
		top_ = new BMatrix* [ p_ * q_ ];
	}
	catch (char* eb)
	{
		cerr << "Can't allocate memory space for TMatrix class: " << eb << endl;
		exit(EXIT_FAILURE);
	}

	for (unsigned int j=0; j<q_; j++)
		for (unsigned int i=0; i<p_; i++)
		{
			unsigned int tm = ( i != p_-1 ) ? mb_ : M_ - i * mb_;
			unsigned int tn = ( j != q_-1 ) ? nb_ : N_ - j * nb_;
			try
			{
				top_[ i + j * p_ ] = new BMatrix( tm, tn, ib );
			}
			catch (char* eb)
			{
				cerr << "Can't allocate memory space for TMatrix class: " << eb << endl;
				exit(EXIT_FAILURE);
			}
#ifdef DEBUG
			cout << "BMatrix(" << (top_[ i + j * p_ ])->m() << ",";
			cout << (top_[ i + j * p_ ])->n() << ",";
			cout << (top_[ i + j * p_ ])->ib() << ")\n";
//			cout << "top_[" << i + j * p_ << "] = " << &top_[ i + j * p_ ] << endl;
#endif
		}
}

/**
 * Destructor
 *
 */
TMatrix::~TMatrix()
{
#ifdef DEBUG
	cout << "\n~TMatrix()\n";
#endif

	for (unsigned int j=0; j<q_; j++)
		for (unsigned int i=0; i<p_; i++)
		{
#ifdef DEBUG
			cout << "BMatrix(" << (top_[ i + j * p_ ])->m() << ",";
			cout << (top_[ i + j * p_ ])->n() << ",";
			cout << (top_[ i + j * p_ ])->ib() << ")\n";
//			cout << "top_[" << i + j * p_ << "] = " << &top_[ i + j * p_ ] << endl;
#endif
			delete top_[ i + j * p_ ];
		}
	delete [] top_;
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
