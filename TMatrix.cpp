/*
 * TMatrix.cpp
 *
 *  Created on: 2015/08/31
 *      Author: stomo
 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "TMatrix.hpp"

using namespace std;

/**
 * Constructor
 *
 * @param M number of lows of the matrix
 * @param N number of columns of the matrix
 * @param mb number of lows of the tile
 * @param nb number of columns of the tile
 * @param ib inner blocking size
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

	try
	{
		top_ = new BMatrix* [ p_ * q_ ];
	}
	catch (bad_alloc &ex)
	{
		cerr << "Can't allocate memory space for TMatrix class: " << ex.what() << endl;
		exit(EXIT_FAILURE);
	}

	for (unsigned int i=0; i<p_; i++)
		for (unsigned int j=0; j<q_; j++)
		{
			unsigned int tm = ( i != p_-1 ) ? mb_ : M_ - i * mb_;
			unsigned int tn = ( j != q_-1 ) ? nb_ : N_ - j * nb_;
			top_[ i + j * p_ ] = new BMatrix( tm, tn, ib );
		}
}

/**
 * Copy constructor
 *
 * @param m number of low tiles of the TMtrix
 * @param n number of column tiles of the TMatrix
 */
TMatrix::TMatrix( const TMatrix& T )
{
  M_  = T.M_;
  N_  = T.N_;
  mb_ = T.mb_;
  nb_ = T.nb_;
  p_  = T.p_;
  q_  = T.q_;

  try
  {
	  top_ = new BMatrix* [ p_ * q_ ];
  }
  catch (bad_alloc &ex)
	{
		cerr << "Can't allocate memory space for TMatrix class: " << ex.what() << endl;
		exit(EXIT_FAILURE);
	}

  for ( unsigned int i = 0; i < p_; i++ )
    for ( unsigned int j = 0; j  < q_; j++ )
      top_[ i + j * p_ ] = T.top_[ i + j * p_ ];
}

/**
 * Destructor
 *
 */
TMatrix::~TMatrix()
{
	cout << "~TMatrix()\n";

	for (unsigned int i=0; i<p_; i++)
		for (unsigned int j=0; j<q_; j++)
		{
			cout << "(" << i << "," << j << "):  ";
			operator delete [] (top_[ i + j * p_ ]);
		}
	delete [] top_;
}

/**
 * Assign random numbers to the elements
 *
 * @param seed Seed of random number generator
 */
void TMatrix::Set_Rnd( const unsigned seed )
{
	Matrix Tmp(M_,N_);
	Tmp.Set_Rnd( seed );

	// (I,J) : Index of the elements of Matrix
	for (unsigned int I = 0; I < M_; I++)
	{
		for (unsigned int J = 0; J < N_; J++)
		{
			// (ti,tj) : Tile Index
			unsigned int ti = I / mb_;
			unsigned int tj = J / nb_;
			// (i,j) : Index of the elements of Tile
			unsigned int i = I % mb_;
			unsigned int j = J % nb_;

			top_[ ti + tj*p_ ]->Set_Val(i, j, Tmp(I,J));
		}
	}
}

/**
 * Set matrix to the identity matrix
 */
void TMatrix::Set_Iden()
{
	for (unsigned int i = 0; i < p_; i++)
		for (unsigned int j = 0; j < q_; j++)
			if (i == j)
				top_[ i + j * p_ ]->Set_Iden();
			else
				top_[ i + j * q_ ]->Set_Zero();
}

/**
 * Set matrix to the zero matrix
 */
void TMatrix::Set_Zero()
{
	for (unsigned int i = 0; i < p_; i++)
		for (unsigned int j = 0; j < q_; j++)
			top_[ i + j * p_ ]->Set_Zero();
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

/**
 * Save matrix elements to the file
 *
 * @param fname data file name
 */
void TMatrix::File_Out( const char* fname )
{
	Matrix Tmp(M_,N_);

	// (I,J) : Index of the elements of Matrix
	for (unsigned int I = 0; I < M_; I++)
	{
		for (unsigned int J = 0; J < N_; J++)
		{
			// (ti,tj) : Tile Index
			int ti = I / mb_;
			int tj = J / nb_;
			// (i,j) : Index of the elements of Tile
			int i = I % mb_;
			int j = J % nb_;

			double val = top_[ ti + tj*p_ ]->operator()(i, j);
			Tmp.Set_Val( I, J, val );
		}
	}
	Tmp.File_Out( fname );
}

/**
 * Save matrix elements to the file
 *
 * @param fname data file name
 * @param dig number of output digit
 */
void TMatrix::File_Out( const char* fname, const unsigned dig )
{
	Matrix Tmp(M_,N_);

	// (I,J) : Index of the elements of Matrix
	for (unsigned int I = 0; I < M_; I++)
	{
		for (unsigned int J = 0; J < N_; J++)
		{
			// (ti,tj) : Tile Index
			int ti = I / mb_;
			int tj = J / nb_;
			// (i,j) : Index of the elements of Tile
			int i = I % mb_;
			int j = J % nb_;

			double val = top_[ ti + tj*p_ ]->operator()(i, j);
			Tmp.Set_Val( I, J, val );
		}
	}
	Tmp.File_Out( fname, dig );
}
