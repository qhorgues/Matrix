#include <iostream>
#include "Matrix.hpp"

int main()
{
    Matrix<int> mat {2, 3};

    mat(0, 0) = 0;  mat(1, 0) = 3; 
    mat(0, 1) = 6;  mat(1, 1) = 4; 
    mat(0, 2) = 5;  mat(1, 2) = 9;
    
    
    Matrix<int> mat2 {3, 2};
    mat2(0, 0) = 8;  mat2(1, 0) = 9;   mat2(2, 0) = 15;
    mat2(0, 1) = 6;  mat2(1, 1) = 5;   mat2(2, 1) = 1;    
    
        
    std::cout << mat << " *\n" << mat2 << "=\n" << mat * mat2 << std::endl;

}

/* #include <forward_list>
#include <string>
#include <iostream>

#include <SecureEntry>

int main()
{
    std::forward_list<std::string> liste {};
    liste.push_front("Un chaine");
    liste.push_front("Un chaine");
    liste.push_front("Un chaine");

    auto afficheListe { [&liste]() -> void 
    {
        for (std::string const & e : liste)
        {
            std::cout << e << std::endl;
        }
    }};

    afficheListe();

    liste.pop_front();
    liste.pop_front();
    liste.pop_front();

    afficheListe();

    std::string str {};
    secureEntry(str);

    liste.push_front(std::move(str));

    afficheListe();

    liste.clear();
} */