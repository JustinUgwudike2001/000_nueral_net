#include "../broadcast.h"

int main()
{

    Array array2(3,1);
    array2.lin();
    array2.print();
    std::cout<<std::endl;

    Array result;

    result = array2.expand(-1, -1);
    result.print();
    std::cout<<std::endl;

    result = array2.expand(6, -1);
    result.print();
    std::cout<<std::endl;

    result = array2.expand(-1, 9);
    result.print();
    std::cout<<std::endl;
    
    result = array2.expand(9, 5);
    result.print();
    std::cout<<std::endl;

    Array array3(3,2,1);
    array3.lin();
    array3.print();
    std::cout<<std::endl;

    result = array3.expand(-1,-1, 8);
    result.print();
    std::cout<<std::endl;

    result = array3.expand(6, 4, 8);
    result.print();
    std::cout<<std::endl;

    Array array4(4, 3,2,1);
    array4.lin();
    array4.print();
    std::cout<<std::endl;

    result = array4.expand(-1,-1,-1, 5);
    result.print();
    std::cout<<std::endl;

    result = array4.expand(8, -1, -1, -1);
    result.print();
    std::cout<<std::endl;
    
}