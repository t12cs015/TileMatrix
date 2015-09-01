/*
 * Matrix.cpp
 *
 *  Created on: 2015/08/31
 *      Author: stomo
 */

#include <iostream>
#include <cassert>
#include <cstdlib>
#include "Matrix.hpp"

using namespace std;

/**
 * Constructor
 *
 * @param m number of lows of the matrix
 * @param n number of columns of the matrix
 */
Matrix::Matrix( const unsigned int m, const unsigned int n )
{
//	cout << "Matrix()\n";

	assert( m > 0 );
	assert( n > 0 );

	m_ = m;
	n_ = n;

	try
	{
		top_ = new double[ m*n ];
	}
	catch (bad_alloc &ex)
	{
		cerr << "Can't allocate memory space for Matrix class: " << ex.what() << endl;
		exit(EXIT_FAILURE);
	}

	for (unsigned int i=0; i<m_*n_; i++)
		top_[i] = 0.0;
}

/**
 * Destructor
 *
 */
Matrix::~Matrix()
{
//	cout << "~Matrix()\n";
	if (top_ != NULL)
		operator delete[] (top_);
}

/**
 * Operator overload =
 */
Matrix &Matrix::operator=( const Matrix &T )
{
	assert( m_ == T.m_ );
	assert( n_ == T.n_ );

	for (unsigned int i = 0; i < m_ * n_; i++)
		top_[i] = T.top_[i];

	return *this;
}

/**
 * Operator overload []
 *
 * @param i index
 */
double &Matrix::operator[]( const unsigned int i ) const
{
	assert( i >= 0 );
	assert( i < m_ * n_ );

	return top_[ i ];
}

/**
 * Operator overload ()
 *
 * @param i low index
 * @param j column index
 */
double &Matrix::operator()( const unsigned int i, const unsigned int j ) const
{
	assert( i >= 0 );  assert( i < m_ );
	assert( j >= 0 );  assert( j < n_ );

	return top_[ i + j * m_ ];
}
