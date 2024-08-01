#include "../squeeze.h"

int main()
{
    std::cout<<std::endl<<"ARRAY2::::::::::: "<<std::endl;
    Array array2(4,3);
    array2.lin();
    array2.print();

    Array result = array2.unsqueeze(0);
    result.print();

    result = array2.unsqueeze(1);
    result.print();

    result = array2.unsqueeze(2);
    result.print();


    std::cout<<std::endl<<"ARRAY2_1::::::::: "<<std::endl;
    Array array3(4,3,2,1);
    array3.lin();
    array3.print();

    result = array3.squeeze(3);
    result.print();

    std::cout<<std::endl<<"ARRAY2_2::::::::: "<<std::endl;
    Array array4(4,3,1,2);
    array4.lin();
    array4.print();

    result = array4.squeeze(2);
    result.print();

    std::cout<<std::endl<<"ARRAY2_3::::::::: "<<std::endl;
    Array array5(1,4,3,2);
    array5.lin();
    array5.print();

    result = array5.squeeze(0);
    result.print();
}