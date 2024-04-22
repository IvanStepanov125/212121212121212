#include <iostream>
#include "Matrix.h"

int main(){
    // double* array_for_vec2 = new double[3]{1, 2, 3};
    // Vector<int> vec1 = Vector<int>(3);
    Vector<int> vec1_1 = {1, 2, 3};
    Vector<int> vec2 = {3, 4, 5};
    std::cout << vec1_1 % vec2 << std::endl;

    // Vector<int> vec3 = vec1_1 + vec2;
    // Vector<int> vec4 = vec1_1 - vec2;
    
    // std::cout << vec2 << std::endl;

    Matrix<double> matrix = Matrix<double>(3, 3);
    Matrix<double> matrix1 = Matrix<double>(3, 3);
    matrix.Completion_matr();
    matrix1.Completion_matr();
    // std::cout << matrix << std::endl;
    // std::cout << matrix1 << std::endl;
    //matrix1.Transposition();
    //std::cout << matrix1 << std::endl;
    Matrix<double> matrix2 = matrix + matrix1;
    // Matrix<int> matrix3 = matrix - matrix1;
    //Matrix<double> matrix4 = matrix * matrix1; //Matrix(*****);
    std::cout << matrix2 << std::endl;
    // std::cout << matrix3 << std::endl;
    //std::cout << matrix4 << std::endl;
    //Matrix<double> ob_matrix = matrix.Inverse_matrix(matrix);
    //Matrix<double> matrix5 = matrix / matrix1;
    //std::cout << matrix5 << std::endl;
    //std::cout << ob_matrix << std::endl;
    //Matrix<double> matrix7 = ob_matrix * matrix;
    //std::cout << matrix7 << std::endl;
    //matrix7.Transposition();
    //std::cout << matrix7 << std::endl;
    //delete [] array_for_vec2;
    return 0;
}
//перегрузка оператора +, -, *, /.
//Метод нахождения обратной матрицы, нахождения опередлителя матрицы любого парядка, транспонирование матрицы, рандомное заполнение.
//*Векторное произведение векторов.