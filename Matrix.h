#pragma once 
#include "Vector.h"
#include <random>

template<typename T>
class Matrix{
private:
    Vector<T>* _vectors;
    size_t _size;
    double _det;
    // }
    double poisk(const Matrix& A, size_t size, double ratio){
        double opred = 0;
        double ratio1 = 1;
        double count = 0;
        size_t cons = A._size;

        if (cons == 1){
            opred = A[0][0];
            return opred * ratio;
        }

        if (cons == 2){
            opred = A[0][0] * A[1][1] - A[0][1] * A[1][0];
            return opred * ratio;
            }
        
        if (cons > 2){
            for (int k = 0; k < cons; k++){
                Matrix<T> new_mat = Matrix<T>((cons - 1),(cons - 1));
                int w = 0;
                for (int i = 0; i < cons; i ++){
                    for (int j = 0; j < cons; j ++){
                        if ((j != k) && (i > 0)){
                            new_mat[w / (cons - 1)][w % (cons - 1)] = A[i][j];
                            w ++;
                            }
                    }      
                }
                if (k % 2 == 0)
                    ratio1 = A[0][k];
                else 
                    ratio1 = (-1) * A[0][k];
                ratio1 *= ratio;
                count += poisk(new_mat, cons - 1, ratio1);
            }
        }

        return count;
    }
    
    void Determinant(Matrix& A){
        if (A._size != A._vectors->GetSize()){
            std::cout << "error" << std::endl;
            exit;
        }
        double ratio = 1;
        _det = poisk(A, _size, ratio);
    }
public:
    Matrix() = delete;

    double GetDet(){
        return _det;
    }

    double Minor(int k, int l){
        Matrix<T> new_mat = Matrix<T>(_size - 1,_size - 1);
        int w = 0;
        for (int i = 0; i < _size; i ++){
            for (int j = 0; j < _vectors->GetSize(); j ++){
                if ((j != l) && (i != k)){
                    new_mat[w / (_size - 1)][w % (_size - 1)] = this->_vectors[i][j];
                    w ++;
                }
            }      
        }
        new_mat.Determinant(new_mat);
        double rez = new_mat.GetDet();
        return rez;
    }

    Matrix Inverse_matrix(Matrix& A){
        Matrix copy = Matrix(_size, _vectors->GetSize());
        for (size_t i = 0; i < _size; i++){
            for (size_t j = 0; j < _size; j++){
                copy[i][j] = pow(-1, i + j) * A.Minor(i, j);
            }
        }
        copy.Transposition();
        A.Determinant(A);
        for (size_t i = 0; i < _size; i++){
            for (size_t j = 0; j < _size; j++){
                copy[i][j] = (1 / A._det) * copy[i][j];
            }       
        }
    return copy;
    }

    // const Vector<T>& operator[](int index) const{
    //     return _vectors[index];
    // }
    Vector<T>& operator[](int index){
        return _vectors[index];
    }

    const Vector<T>& operator[](int index)const{
        return _vectors[index];
    }

    Matrix(const Matrix& A){
        _size = A._size;
        _det = 0;
        _vectors = new Vector<T>[_size];
        for (int i = 0; i < _size; i++){
            _vectors[i] = A._vectors[i];
        }
    }

    Matrix(size_t rows, size_t cols){
        _size = rows;
        _det = 0;
        _vectors = new Vector<T> [_size];
        for (size_t i = 0; i < _size; i++)
            _vectors[i] = Vector<T>(cols);
    }
    // Matrix(size_t size, T* vectors){
    //     _size = size;
    //     _det = 0;
    //     _vectors = new T[_size];
    //     for (int i = 0; i < size; i++){
    //         _array[i] = array[i];
    //     }

    

    void Transposition(){
        Matrix<T> copy = Matrix<T>(_vectors->GetSize(), _size);
        for (int i = 0; i < _size; i++){
            for (int j = 0; j < _vectors->GetSize(); j++)
                copy._vectors[j][i] =_vectors[i][j];
        }
        _size = copy._size;
        delete [] _vectors;
        _vectors = new Vector<T>[_size];
        for (int i = 0; i < _size; i++){
            _vectors[i] = copy._vectors[i];
            }
        }

    inline int rand(){
        std::mt19937 gen;
        gen.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist;
        return dist(gen) % 15;
    }

    void Completion_matr(){
        for (int i = 0; i < _size; i++){
            for (int j = 0; j < _vectors->GetSize(); j ++){
                _vectors[i][j] = rand();
            }
        }
    }

    Matrix operator+ (const Matrix& A) const{
        Matrix matr = Matrix(_size, _vectors->GetSize());
        if (_size != A._size || _vectors->GetSize() != A._vectors->GetSize()){
            std::cout << "error" << std::endl;
            exit;
            }
        for (size_t i = 0; i < _size; i++){
            for (size_t j = 0; j < _vectors->GetSize(); j++){
                matr[i][j] = _vectors[i][j] + A._vectors[i][j];
            }
        }
        return matr;
    }
    
    Matrix operator- (const Matrix& A) const{
        Matrix matr = Matrix(_size, _vectors->GetSize());
        if (_size != A._size || _vectors->GetSize() != A._vectors->GetSize()){
            std::cout << "error" << std::endl;
            exit;
            }
        for (size_t i = 0; i < _size; i++){
            for (size_t j = 0; j < _vectors->GetSize(); j++){
                matr[i][j] = _vectors[i][j] - A._vectors[i][j];
            }
        }
        return matr;
    }
    Matrix operator* (const Matrix& A) const{
        size_t rows, cols;
        rows = _size;
        cols = A._vectors->GetSize();
        Matrix matr = Matrix(rows, cols);
        Matrix<T> copy = Matrix<T>(A);
        if (_size != A._vectors->GetSize() || A._size != _vectors->GetSize()){
            std::cout << "error" << std::endl;
            exit;
            }
        copy.Transposition();
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                matr[i][j] = _vectors[i] * copy._vectors[j];
                
            }
        }
        return matr;
    }

    Matrix operator/ (Matrix& A) const{
        Matrix<double> ob_matrix = A.Inverse_matrix(A);
        Matrix<T> matr = Matrix<T>(*this *  ob_matrix);
        return matr;
    }

    friend std::ostream& operator<< (std::ostream& os, const Matrix& matr){
        for (size_t i = 0; i < matr._size; i++){
            os << matr._vectors[i] << std::endl;
        }
        return os;
    }

    ~Matrix(){
        delete [] _vectors;
    }

};