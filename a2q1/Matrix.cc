#include "Matrix.h"
#include <iomanip>

//*******************************************
// Matrix Declaration
//*******************************************

struct Matrix::Impl {
    int numCols;
    int numRows;
    std::vector<int> v;
};

//*******************************************
// Constructors, Destructors, Assignment
//*******************************************

Matrix::Matrix( int numRows, int numCols, const std::vector<int> & v ) : matrix_(new Matrix::Impl){
    
    if ( numRows <= 0 || numRows > 10 || numCols <= 0 || numCols > 10 ){
        throw "Invalid dimensions";
    };

    if ( v.size() != (unsigned)numRows*numCols ){
        throw "Invalid number of elements";
    };
    
    matrix_->numCols = numCols;
    matrix_->numRows = numRows;
    matrix_->v = v;
};

Matrix::Matrix( const Matrix &m ) : matrix_(new Matrix::Impl (*m.matrix_)){

};

Matrix::~Matrix(){
    delete matrix_;
    matrix_ = NULL;
};

//*******************************************
// Main Methods
//*******************************************

// Returns: # of rows in the matrix.
int Matrix::rows() const {
    return matrix_->numRows;
};

// Returns: # of columns in the matrix.
int Matrix::cols() const{
    return matrix_->numCols;
}; 

// Throws: string "Invalid index" if ( i < 0 || i >= rows() || j < 0 || j >= cols() )
// Returns: this[i][j]
int Matrix::get( int i, int j ) const{
    if ( i < 0 || i >= rows() || j < 0 || j >= cols() ){
        throw "Invalid index";
    }
    return matrix_->v.at(i*cols() + j);
};

//*******************************************
// Operators
//*******************************************

// Assignment Operation
Matrix& Matrix::operator= (const Matrix &m){
    Matrix copy(m);
    Matrix::Impl* var;
    var  = copy.matrix_;
    copy.matrix_ = matrix_;
    matrix_ = var;

    return *this;

};

// Arithmetic Operations

// Addition
Matrix operator+ (const Matrix &m1, const Matrix &m2){
    std::vector<int> v;

    // Must be same size
    for (int i=0; i < m1.rows(); i++){
           for (int j=0; j < m1.cols(); j++){
               int sum = m1.get(i,j) + m2.get(i,j);
               v.push_back(sum);
           }
    }

    return Matrix(m1.rows(), m1.cols(), v);
};

// Subtraction
Matrix operator- (const Matrix &m1, const Matrix &m2){
    std::vector<int> v;

    // Must be same size
    for (int i=0; i < m1.rows(); i++){
           for (int j=0; j < m1.cols(); j++){
               int sum = m1.get(i,j) - m2.get(i,j);
               v.push_back(sum);
           }
    }

    return Matrix(m1.rows(), m1.cols(), v);  
};

// Matrix Multiplication
Matrix operator* (const Matrix &m1, const Matrix &m2){
    std::vector<int> v;

    for (int i=0; i < m1.rows(); i++){
        for (int j=0; j < m2.cols(); j++){
                int value = 0;
            for (int k=0; k < m1.cols(); k++){
                value = value + (m1.get(i,k)*m2.get(k,j));
            }
            v.push_back(value);
        }
    }

    return Matrix(m1.rows(), m2.cols(), v); 
};

// Integer-Matrix Multiplication
Matrix operator* (int scale, const Matrix &m){
    std::vector<int> v;

    for (int i=0; i < m.rows(); i++){
           for (int j=0; j < m.cols(); j++){
               v.push_back(m.get(i,j)*scale);
           }
    }

    return Matrix(m.rows(), m.cols(), v); 
};

// Matrix-Integer Multiplication
Matrix operator* (const Matrix &m, int scale){
    std::vector<int> v;

    for (int i=0; i < m.rows(); i++){
           for (int j=0; j < m.cols(); j++){
               v.push_back(m.get(i,j)*scale);
           }
    }

    return Matrix(m.rows(), m.cols(), v); 
};

// Comparison Operation
bool operator== (const Matrix &m1, const Matrix &m2){

    // Check dimension equality
    if ((m1.rows() != m2.rows()) || (m1.cols() != m2.cols())){
        return false;
    }

    // Check element equality
    for (int i=0; i < m1.rows(); i++){
        for (int j=0; j < m1.cols(); j++){
            if (m1.get(i,j) != m2.get(i,j)){
                return false;
            }
        }
    }

    // Passed all tests
    return true;
};

// Streaming Operations
std::ostream& operator<< (std::ostream &sout, const Matrix &m){
    for (int i=0; i < m.rows(); i++){
        for (int j=0; j < m.cols(); j++){
            sout << std::setw(4);
            sout << m.get(i, j) << " ";
        }
        sout << "\n";
    }
    return sout;
};

std::istream& operator>> (std::istream &sin,  Matrix &m){
    int numCol;
    int numRow;
    int value;
    std::vector<int> v;

    sin >> numRow >> numCol;

    for (int i=0; i < numCol*numRow; i++){
        sin >> value;
        v.push_back(value);
    }

    m = Matrix(numRow, numCol, v);
    return sin;
};