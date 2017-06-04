#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>

/*
 * Represents an immutable 2-D Matrix of integers. Use the Pimpl idiom to hide the
 * implementation. Must support the following operations in addition to the provided 
 * signatures:
 *
 *  1) m1 = m2
 *  2) m1 + m2
 *  3) m1 - m2
 *  4) m1 * m2
 *  5) <int> * m1
 *  6) m1 * <int>
 *  7) test if m1 == m2 via operator==
 *  8) output m via operator<<
 *  9) read in m via operator>>
 *
 * IMPLEMENTATION NOTES:
 * - Add the signatures for the operations described above. You must decide whether
 *   they are members of the class or free routines, but remember that style matters.
 * - You may not add any other public data/methods, and may not declare any friends.
 *
 *  Created by Caroline Kierstead on 2017-04-29.
 *  Last updated: 2017-05-25
 *  Copyright 2017 UW. All rights reserved.
 *
 */
#include <iostream>

class Matrix {
    // *** add Pimpl declarations

	struct Impl;
	Impl* matrix_;

public:
	// Throws: 
	//  - string "Invalid dimensions if ( numRows <= 0 || numRows > 10 || numCols <= 0 || numCols > 10 ).
	//  - string "Invalid number of elements" if ( v.size() != numRows*numCols ).
	// Ensures: this[i][j] = v[j+(i*numCols)] for all i, j such that 0 <= i < numRows and 0 <= j < numCols.
	Matrix( int numRows, int numCols, const std::vector<int> & v );

	// Ensures: this matrix is a deep copy of the other
	Matrix( const Matrix &);

	// Ensures: this is empty
	virtual ~Matrix();

	// Returns: # of rows in the matrix.
	int rows() const; 

	// Returns: # of columns in the matrix.
	int cols() const; 

	// Throws: string "Invalid index" if ( i < 0 || i >= rows() || j < 0 || j >= cols() )
	// Returns: this[i][j]
	int get( int i, int j ) const;

    // *** add operations as needed

	Matrix& operator= (const Matrix &);

};

// *** add free routines as needed

// Arithmetic Operations
Matrix operator+ (const Matrix&, const Matrix&);
Matrix operator- (const Matrix&, const Matrix&);
Matrix operator* (const Matrix&, const Matrix&);
Matrix operator* (int scale, const Matrix&);
Matrix operator* (const Matrix&, int scale);

// Comparison Operation
bool operator== (const Matrix&, const Matrix&);

// Streaming Operations
std::ostream& operator<< (std::ostream &sout, const Matrix &r);
std::istream& operator>> (std::istream &sin, Matrix &s);

#endif
