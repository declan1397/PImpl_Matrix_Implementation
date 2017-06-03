#include "Matrix.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

/*
 * Matrix test harness.
 *
 *  Created by Caroline Kierstead on 2017-05-02.
 *  Last updated: 2017-05-23
 *  Copyright 2017 UW. All rights reserved.
 *
 */
const static unsigned int MAX_MATRICES = 10;

// Helper methods that retrieve the necessary matrix ids and integer values,
// then verify that the associated Matrices are initialized (or not), as
// appropriate.
void createMatrix( vector<Matrix*> & matrices );
void deleteMatrix( vector<Matrix*> & matrices );
void copyCtorMatrix( vector<Matrix*> & matrices );
void moveCtorMatrix( vector<Matrix*> & matrices );
void copyMatrix( vector<Matrix*> & matrices );
void moveMatrix( vector<Matrix*> & matrices );
void readInMatrix( vector<Matrix*> & matrices );
void writeOutMatrix( vector<Matrix*> & matrices );
void addMatrices( vector<Matrix*> & matrices );
void subtractMatrices( vector<Matrix*> & matrices );
void multiplyMatrices( vector<Matrix*> & matrices );
void compareMatrices( vector<Matrix*> & matrices );

// Performs value*Matrix if flag == true, Matrix*value if flag == false.
void scaleMatrix( vector<Matrix*> & matrices, bool flag = true );

int main() {
	char command;

	// Create MAX_MATRICES (Matrix*) set initially to nullptr.
	vector<Matrix*> matrices( MAX_MATRICES, nullptr );

	for (;;) {
		try {
			cerr << "Enter command: ";
			cin >> command;
			if ( cin.fail() ) break;
			switch( command ) {
				case 'c':
					createMatrix( matrices );
					break;
				case 'd':
					deleteMatrix( matrices );
					break;
				case 'C':
					copyCtorMatrix( matrices );
					break;
				case 'M':
					moveCtorMatrix( matrices );
					break;
				case '<':
					writeOutMatrix( matrices );
					break;
				case '>':
					readInMatrix( matrices );
					break;
				case '=':
					copyMatrix( matrices );
					break;
				case 'm':
					moveMatrix( matrices );
					break;
				case '+':
					addMatrices( matrices );
					break;
				case '-':
					subtractMatrices( matrices );
					break;
				case '*':
					multiplyMatrices( matrices );
					break;
				case 'e':
					compareMatrices( matrices );
					break;
				case 's':
					scaleMatrix( matrices );
					break;
				case 'S':
					scaleMatrix( matrices, false );
					break;
			} // switch
		} catch( string & s ) {
			cout << s << endl;
		} // catch
	} // for

	for ( auto it : matrices ) delete it;
	return 0;
} // main

// Clears the cin error flags if invalid input is read. Discards any input to the end of the line.
void fixcin() {
    cin.clear();
    string discard;
    getline(cin, discard);
} // fixcin

bool get1Id( unsigned int & id ) {
	cin >> id;
	if ( ! cin.fail() ) {
		if ( id < MAX_MATRICES ) return true;
		fixcin();
		cerr << "Id must be in the range 0 to " << MAX_MATRICES-1 << endl;
		return false;
	} // if
	fixcin();
	cerr << "Unable to obtain an id." << endl;
	return false;
} // get1Id

bool get2Ids( unsigned int & id1, unsigned int & id2 ) { 
	return get1Id( id1 ) && get1Id( id2 ); 
} // get2Ids

bool get3Ids( unsigned int & id1, unsigned int & id2, unsigned int & id3 ) {
	 return get1Id( id1 ) && get1Id( id2 ) && get1Id( id3 ); 
} // get3Ids

bool getIdAndValue( unsigned int & id, int & value ) {
	if ( get1Id( id ) ) {
		cin >> value;
		if ( ! cin.fail() ) return true;
		fixcin();
		cerr << "Unable to obtain an integer value." << endl;
	} // if
	return false;
} // getIdAndValue

void createMatrix( vector<Matrix*> & matrices ) {
	unsigned int id;
	int value;
	if ( ! get1Id( id ) ) return;
	if ( matrices.at( id ) != nullptr ) {
		cerr << "Matrix " << id << " on which to use the constructor is not a nullptr." << endl;
		return;
	} // if
	int r, c;
	cin >> r >> c;
	if ( cin.fail() ) return;
	vector<int> v;
	for ( int i = 0; i < r*c; ++i ) {
		cin >> value;
		if ( cin.fail() ) {
			fixcin();
			return;
		} // if
		v.emplace_back( value );
	} // for
	matrices.at( id ) = new Matrix( r, c, v );
} // createMatrix

void deleteMatrix( vector<Matrix*> & matrices ) {
	unsigned int id;
	if ( ! get1Id( id ) ) return;
	if ( matrices.at( id ) == nullptr ) {
		cerr << "Matrix " << id << " to delete is a nullptr." << endl;
		return;
	} // if
	delete matrices.at( id );
	matrices.at( id ) = nullptr;
} // deleteMatrix

void copyCtorMatrix( vector<Matrix*> & matrices ) {
	unsigned int id1, id2;
	if ( ! get2Ids( id1, id2 ) ) return;
	if ( matrices.at( id1 ) != nullptr ) {
		cerr << "Matrix " << id1 << " on which to use the copy constructor is not a nullptr." << endl;
		return;
	} // if
	if ( matrices.at( id2 ) == nullptr ) {
		cerr << "Matrix " << id2 << " to copy is a nullptr." << endl;
		return;
	} // if
	matrices.at( id1 ) = new Matrix( *matrices.at( id2 ) );
} // copyCtorMatrix

void moveCtorMatrix( vector<Matrix*> & matrices ) {
	unsigned int id1, id2;
	if ( ! get2Ids( id1, id2 ) ) return;
	if ( matrices.at( id1 ) != nullptr ) {
		cerr << "Matrix " << id1 << " on which to use the move constructor is not a nullptr." << endl;
		return;
	} // if
	if ( matrices.at( id2 ) == nullptr ) {
		cerr << "Matrix " << id2 << " to move is a nullptr." << endl;
		return;
	} // if
	matrices.at( id1 ) = new Matrix( std::move( *matrices.at( id2 ) ) );
	delete matrices.at( id2 );
	matrices.at( id2 ) = nullptr;
} // moveCtorMatrix

void copyMatrix( vector<Matrix*> & matrices ) {
	unsigned int id1, id2;
	if ( ! get2Ids( id1, id2 ) ) return;
	if ( matrices.at( id1 ) == nullptr ) {
		cerr << "Matrix " << id1 << " on which to use the assignment operator is a nullptr." << endl;
		return;
	} // if
	if ( matrices.at( id2 ) == nullptr ) {
		cerr << "Matrix " << id2 << " to copy is a nullptr." << endl;
		return;
	} // if
	*matrices.at( id1 ) = *matrices.at( id2 );
} // copyMatrix

void moveMatrix( vector<Matrix*> & matrices ) {
	unsigned int id1, id2;
	if ( ! get2Ids( id1, id2 ) ) return;
	if ( matrices.at( id1 ) == nullptr ) {
		cerr << "Matrix " << id1 << " on which to use the assignment operator is a nullptr." << endl;
		return;
	} // if
	if ( matrices.at( id2 ) == nullptr ) {
		cerr << "Matrix " << id2 << " to copy is a nullptr." << endl;
		return;
	} // if
	*matrices.at( id1 ) = std::move( *matrices.at( id2 ) );
	delete matrices.at( id2 );
	matrices.at( id2 ) = nullptr;
} // moveMatrix

void readInMatrix( vector<Matrix*> & matrices ) {
	unsigned int id;
	if ( ! get1Id( id ) ) return;
	if ( matrices.at( id ) == nullptr ) {
		cerr << "Matrix " << id << " to read into is a nullptr." << endl;
		return;
	} // if
	cin >> (*matrices.at( id ));
} // readInMatrix

void writeOutMatrix( vector<Matrix*> & matrices ) {
	unsigned int id;
	if ( ! get1Id( id ) ) return;
	if ( matrices.at( id ) == nullptr ) {
		cerr << "Matrix " << id << " to output is a nullptr." << endl;
		return;
	} // if
	cout << "Matrix " << id << " =\n" << (*matrices.at( id ));
} // writeOutMatrix

void addMatrices( vector<Matrix*> & matrices ) {
	unsigned int id1, id2, id3;
	if ( ! get3Ids( id1, id2, id3) ) return;
	if ( matrices.at( id1 ) == nullptr ) {
		cerr << "Matrix " << id1 << " to be assigned result of matrix addition is a nullptr." << endl;
		return;
	} // if
	if ( matrices.at( id2 ) == nullptr ) {
		cerr << "Matrix " << id2 << ", LHS of matrix addition, is a nullptr." << endl;
		return;
	} // if
	if ( matrices.at( id3 ) == nullptr ) {
		cerr << "Matrix " << id3 << ", RHS of matrix addition, is a nullptr." << endl;
		return;
	} // if
	(*matrices.at( id1 )) = (*matrices.at( id2 )) + (*matrices.at( id3 ));
} // addMatrices

void subtractMatrices( vector<Matrix*> & matrices ) {
	unsigned int id1, id2, id3;
	if ( ! get3Ids( id1, id2, id3 ) ) return;
	if ( matrices.at( id1 ) == nullptr ) {
		cerr << "Matrix " << id1 << " be assigned result of matrix subtraction is a nullptr." << endl;
		return;
	} // if
	if ( matrices.at( id2 ) == nullptr ) {
		cerr << "Matrix " << id2 << ", LHS of matrix subtraction, is a nullptr." << endl;
		return;
	} // if
	if ( matrices.at( id3 ) == nullptr ) {
		cerr << "Matrix " << id3 << ", RHS of matrix subtraction, is a nullptr." << endl;
		return;
	} // if
	(*matrices.at( id1 )) = (*matrices.at( id2 )) - (*matrices.at( id3 ));
} // subtractMatrices

void multiplyMatrices( vector<Matrix*> & matrices ) {
	unsigned int id1, id2, id3;
	if ( ! get3Ids( id1, id2, id3 ) ) return;
	if ( matrices.at( id1 ) == nullptr ) {
		cerr << "Matrix " << id1 << " to be assigned result of matrix multiplication is a nullptr." << endl;
		return;
	} // if
	if ( matrices.at( id2 ) == nullptr ) {
		cerr << "Matrix " << id2 << ", LHS of matrix multiplication, is a nullptr." << endl;
		return;
	} // if
	if ( matrices.at( id3 ) == nullptr ) {
		cerr << "Matrix " << id3 << ", RHS of matrix multiplication, is a nullptr." << endl;
		return;
	} // if
	(*matrices.at( id1 )) = (*matrices.at( id2 )) * (*matrices.at( id3 ));
} // multiplyMatrices

void compareMatrices( vector<Matrix*> & matrices ) {
	unsigned int id1, id2;
	if ( ! get2Ids( id1, id2 ) ) return;
	if ( matrices.at( id1 ) == nullptr ) {
		cerr << "Matrix " << id1 << ", LHS of matrix comparison, is a nullptr." << endl;
		return;
	} // if
	if ( matrices.at( id2 ) == nullptr ) {
		cerr << "Matrix " << id2 << ", RHS of matrix comparison, is a nullptr." << endl;
		return;
	} // if
	cout << "Matrix " << id1 << " == " << id2 << "? " 
		<< boolalpha << ( (*matrices.at( id1 )) == (*matrices.at( id2 )) ) << endl;
} // compareMatrices

void scaleMatrix( vector<Matrix*> & matrices, bool flag ) {
	unsigned int id1, id2;
	int value;

	if ( ! get1Id( id1 ) || ! getIdAndValue( id2, value ) ) return;
	if ( matrices.at( id1 ) == nullptr ) {
		cerr << "Matrix " << id1 << " to be assigned result of scaled matrix is a nullptr." << endl;
		return;
	} // if
	if ( matrices.at( id2 ) == nullptr ) {
		cerr << "Matrix " << id2 << ", matrix to scale, is a nullptr." << endl;
		return;
	} // if
	if ( flag ) *(matrices.at( id1 )) = value * (*matrices.at( id2 ));
	else *(matrices.at( id1 )) = (*matrices.at( id2 )) * value;
} // scaleMatrix
