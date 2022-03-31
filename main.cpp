#include <iostream>
#include "Matrix.hpp"

int main()
{
    Matrix mat {2, 3};

    mat(0, 0) = 0;  mat(1, 0) = 3; 
    mat(0, 1) = 6;  mat(1, 1) = 4; 
    mat(0, 2) = 5;  mat(1, 2) = 9;
    
    
    Matrix mat2 {3, 2};
    mat2(0, 0) = 8;  mat2(1, 0) = 9;   mat2(2, 0) = 15;
    mat2(0, 1) = 6;  mat2(1, 1) = 5;   mat2(2, 1) = 1;    

    // Githo


    /* Matrix mat {3, 5}; // Avant 5, 3 c'est faux
    mat(0, 0) = 100;    mat(1, 0) = 30; mat(2, 0) = 10; 
    mat(0, 1) = 1000;   mat(1, 1) = 45; mat(2, 1) = 25;
    mat(0, 2) = 25;     mat(1, 2) = 29; mat(2, 2) = 1;
    mat(0, 3) = 500;    mat(1, 3) = 40; mat(2, 3) = 17;
    mat(0, 4) = 75;     mat(1, 4) = 18; mat(2, 4) = 38;
    
    
    Matrix mat2 {3, 3};
    mat2(0, 0) = 852;   mat2(0, 1) = 9121;   mat2(0, 2) = 4578;
    mat2(1, 0) = 6455;  mat2(1, 1) = 542;    mat2(1, 2) = 4554;  
    mat2(2, 0) = 615;   mat2(2, 1) = 545;    mat2(2, 2) = 553;   */
    
    /* // Qhor
    Matrix mat {6, 2};
    mat(0, 0) = 5125;  mat(1, 0) = 156; mat(2, 0) = 2956;  mat(3, 0) = 17865; mat(4, 0) = 1616;  mat(5, 0) = 65526; 
    mat(0, 1) = 1485;  mat(1, 1) = 256; mat(2, 1) = 1561;  mat(3, 1) = 1451; mat(4, 1) = 15665;  mat(5, 1) = 1562486;
    
    
    Matrix mat2 {2, 2};
    mat2(0, 0) = 1429;  mat2(1, 0) = 124659;     
    mat2(0, 1) = 13919;  mat2(1, 1) = 1439; */
        
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