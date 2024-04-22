#pragma once 
#include <iostream>
#include <math.h>


template<typename T>
class Matrix;

template<typename T>
class Vector{
private:
    T* _array;
    size_t _size;
    double _lenght;
    double* _norm;
    void Length(){
        double lenght = 0;
        for (size_t i = 0; i < _size; i++)
            lenght += _array[i] * _array[i];
        _lenght = sqrt(lenght);
    }
public:
    Vector(){
        _size = 10;
        _array = new T[_size];
        _lenght = 0;
        _norm  = new double[_size];
    }
    const T& operator[](int i) const{
        return _array[i];
    }
    T& operator[](int i){
        return _array[i];
    }

    size_t GetSize(){
        return _size;
    }

    void Print_norm(){
        for (size_t i = 0; i < _size; i++){
            if (i == 0){
                std::cout << "(";
            }
            std::cout << _norm[i];
            if (i + 1 != _size)
                std::cout << ", ";
            if (i == _size - 1){
                std::cout << ")" << std::endl;
            }
        }
    }

    Vector(const Vector& tmp){
        _size = tmp._size;
        _array = new T[_size];
        _norm = new double[_size];
        for (size_t i = 0; i < _size; i++){
            _array[i] = tmp._array[i];
        }
    }

    Vector& operator=(const Vector& tmp){
        if(tmp._size > _size){
            delete [] _array;
            _array = new T[tmp._size];
        }
        _size = tmp._size;
        for(size_t i = 0; i < _size; i ++){
            _array[i] = tmp._array[i];
        }

        return *this;
    }

    Vector(std::initializer_list<T> list){
        _size = list.size();
        _array = new T[_size];
        _norm = new double[_size];
        int i = 0;
        for (auto elem = list.begin(); elem != list.end(); elem++, i++){
            _array[i] = *elem;
        }
    }

    Vector(size_t size, T* array){
        _size = size;
        _array = new T[_size];
        _norm = new double[_size];
        for (int i = 0; i < size; i++){
            _array[i] = array[i];
        }
    }

    Vector(size_t size): _size(size), _array(new T[size]), _norm(new double[size]){
        
        for (int i =0; i < size; i++){
            _array[i] = 0;
        }
    }
    ~Vector(){
        delete [] _array;
        delete [] _norm;
    }

    Vector(size_t i, T arry){
        _array[i] = arry;
    }

    Vector operator+(const Vector& A) const{
        if (_size != A._size){
            throw;
        }
        T* array = new T[_size];
        for (size_t i = 0; i < _size; i ++){
            array[i] = _array[i] + A._array[i];
        }
        return Vector(_size, array);
    }

    double operator*(const Vector& A) const{
        if (_size != A._size){
            throw;
        }
        double res = 0;
        for (size_t i = 0; i < _size; i ++){
            res += _array[i] * A._array[i];
        }
        return res;
    }
    Vector operator%(const Vector& A) const{
        if (_size != A._size){
            throw "asd";
        }
        Matrix<T> matr = Matrix<T>(3, 3);
        for (int i = 0; i < _size; i ++){
            matr[0][i] = 1;
            matr[1][i] = _array[i];
            matr[2][i] = A._array[i];
        }
        T* array = new T[_size];
        for (int j = 0; j < _size; j++){
            array[j] = pow(-1, j) * matr.Minor(0, j);
        }
        return Vector(_size, array);
    }

    Vector operator~(){
        this->Length();
        if (_lenght != 0)
            for (size_t i = 0; i < _size; i ++){
                _norm[i] = _array[i] / _lenght;
            }
        return *this;
    }


    Vector operator-(const Vector& A) const{
        if (_size != A._size){
            throw;
        }
        T* array = new T[_size];
        for (size_t i = 0; i < _size; i ++){
            array[i] = _array[i] - A._array[i]; 
        }
        return Vector(_size, array);
    }

    friend std::ostream& operator<< (std::ostream& os, const Vector& vec){
        os << "(";
        for (int i =0; i < vec._size; i++){
            os << vec._array[i];
            if (i + 1 != vec._size)
                os << ", ";
        }
        os << ")";
        
    return os;
    }
};