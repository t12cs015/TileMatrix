/*
 * TileMatrixTest.cpp
 *
 *  Created on: 2015/08/31
 *      Author: stomo
 */

#include <iostream>
#include <cstdlib>
#include "Matrix.hpp"
#include "BMatrix.hpp"
#include "TMatrix.hpp"

using namespace std;

int main( int argc, char* argv[] )
{
	{
		Matrix A(10,10);
		cout << A(0,0) << endl;
		cout << "Matrix block end" << endl;
	}

	{
		Matrix A(100,50);
		cout << "m = " << A.m() << ", n = " << A.n() << endl;
		cout << "Matrix block end" << endl;
	}

//	for (unsigned int i=0; i<3; i++)
//	{
//		BMatrix A(200000000,200000000,5);
//		cout << A(0,0) << endl;
//		cout << "m = " << A.m() << ", n = " << A.n() << ", ib = " << A.ib() << endl;
//		cout << "BMatrix block end" << endl;
//	}

//	for (unsigned int i=0; i<3; i++)
	{
//		cout << endl << "The " << i+1 << "th TEST" << endl;
		TMatrix A(50000,50000,1000,1000,5);
		cout << "M = " << A.M() << ", n = " << A.N() << ", mb = " << A.mb() << ", nb = " << A.nb();
		cout << ", p = " << A.p() << ", q = " << A.q() << endl;
		cout << "TMatrix block end" << endl;
	}

	cout << endl << "TileMatrixTest end" << endl;
	return EXIT_SUCCESS;
}
