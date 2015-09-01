/*
 * Matrix.cpp
 *
 *  Created on: 2015/08/31
 *      Author: stomo
 */

#include <iostream>
#include <fstream>
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
 * Copy Constructor
 *
 * @param T original object
 */
Matrix::Matrix( const Matrix& T )
{
	this->m_ = T.m();
	this->n_ = T.n();

	try
	{
		this->top_ = new double[ T.m() * T.n() ];
	}
	catch (bad_alloc &ex)
	{
		cerr << "Can't allocate memory space for Matrix class: " << ex.what() << endl;
		exit(EXIT_FAILURE);
	}

	for (unsigned int i = 0; i < this->m_ * this->n_; i++)
		this->top_[i] = T.top_[i];
}

/**
 * Destructor
 *
 */
Matrix::~Matrix()
{
	if (top_ != NULL)
		operator delete[] (top_);
}

/**
 * Assign random numbers to the elements
 *
 * @param seed Seed of random number generator
 */
void Matrix::Set_Rnd( const unsigned seed )
{
	assert( seed >= 0 );

	srand(seed);
	for (unsigned int i = 0; i < m_ * n_; i++)
		top_[i] = (double)rand() / RAND_MAX;
}

/**
 * Set matrix to the identity matrix
 */
void Matrix::Set_Iden()
{
	for (unsigned int i = 0; i < m_; i++)
		for (unsigned int j = 0; j < n_; j++)
			top_[ i + j * m_ ] = ( i == j ) ? 1.0 : 0.0;
}

/**
 * Set matrix to the identity matrix
 */
void Matrix::Set_Zero()
{
	for (unsigned int i = 0; i < m_ * n_; i++)
		top_[ i ] = 0.0;
}

/**
 * Assign the value to (i,j) element
 *
 * @param i vertical index of the element
 * @param j horizontal index of the element
 * @param val element value
 */
void Matrix::Set_Val( const unsigned int i, const unsigned int j, const double val )
{
	assert( i >= 0 );	assert( i < m_ );
	assert( j >= 0 );	assert( j < n_ );

	top_[ i + j * m_ ] = val;
}

/**
 * Show elements to the standard output
 */
void Matrix::Show_all() const
{
	for (unsigned int i = 0; i < m_; i++) {
		for (unsigned int j = 0; j < n_; j++) {
			cout << top_[ i + j * m_ ] << " ";
		}
		cout << endl;
	}
	cout << endl;
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

/**
 * Save matrix elements to the file
 *
 * @param fname data file name
 */
void Matrix::File_Out( const char* fname )
{
	ofstream matf(fname);
	if (!matf) {
		cerr << "Unable to open " << fname << endl;
		exit(EXIT_FAILURE);
	}

	matf << m_ << std::endl;
	matf << n_ << std::endl;
	for (unsigned int i = 0; i < m_; i++)
	{
		for (unsigned int j = 0; j < n_; j++)
		{
			matf << top_[ i + j * m_ ] << " ";
		}
		matf << endl;
	}
	matf.close();
}

/**
 * Save matrix elements to the file
 *
 * @param fname data file name
 * @param dig number of output digit
 */
void Matrix::File_Out( const char* fname, const unsigned dig )
{
	ofstream matf(fname);
	if (!matf) {
		std::cerr << "Unable to open " << fname << std::endl;
		exit(EXIT_FAILURE);
	}

	matf << m_ << endl;
	matf << n_ << endl;
	matf.precision(dig);
	for (unsigned int i = 0; i < m_; i++)
	{
		for (unsigned int j = 0; j < n_; j++)
		{
			matf << top_[ i + j * m_ ] << " ";
		}
		matf << endl;
	}
	matf.close();
}
