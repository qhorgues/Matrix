#include <iostream>
#include "../include/Matrix.hpp"

int main()
{
        constexpr Matrix<int, 1> mat1 {
                {8}
        };

        
        constexpr Matrix<int, 3, 1> mat2 {
                {4},
                {3},
                {2}
        };

        constexpr Matrix<int , 4> A {
                Matrix<int, 2>{}          , Matrix<int, 2>{{1, 1}, {2, 3}},
                Matrix<int, 2>::identity(), Matrix<int, 2>{}
        };
     
                
        constexpr Matrix mat { mat2 * mat1 };

        std::cout << mat1 << " *\n" << mat2 << " =\n" << mat << std::endl;
        std::cout << A << std::endl;

}