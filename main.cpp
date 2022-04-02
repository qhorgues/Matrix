#include <iostream>
#include "Matrix.hpp"

int main()
{
        Matrix<int, 3, 2> mat1 {};

        mat1(0, 0) = 0;    mat1(0, 1) = 3; 
        mat1(1, 0) = 6;    mat1(1, 1) = 4; 
        mat1(2, 0) = 5;    mat1(2, 1) = 9;

        
        Matrix<int, 2, 3> mat2 {};
        mat2(0, 0) = 8;    mat2(0, 1) = 9;     mat2(0, 2) = 15;
        mat2(1, 0) = 6;    mat2(1, 1) = 5;     mat2(1, 2) = 1;        
                
        Matrix mat = mat2 * mat1;

        std::cout << mat1 << " *\n" << mat2 << "=\n" << mat << std::endl;

        std::cout << mat1.column(0) << " *\n" << mat2.line(0) << "=\n" << mat2.line(0) * mat1.column(0)    << std::endl;

}