#include "../broadcast.h"

int main()
{
    Array<float> arr1({5});
    arr1.set_name("arr1");
    arr1.lin();
    //arr1.print_grad();

    Array<float> arr2({5});
    arr2.set_name("arr2");
    arr2.lin();

    Array<float> arr3;
    arr3.set_name("arr3");

    Array<float> arr4; 
    arr4.set_name("arr4");

    arr3 = arr1 + arr2;
    arr3 = arr3 / arr1;
    arr4 = arr1 * arr2; 
    arr3 = arr3 + arr4;
    arr4 = arr4 - 7;
    arr3 = arr3 + 4;
    arr3 = arr3 - arr4;
    arr3 = arr3 / 10;
    arr3 = arr3 * 4.2;
    arr3 = arr3 ^ 3;

    arr3.print();
    arr3.print_grad();
    //arr1.print_grad();
    //arr2.print_grad();

    printf("__________________________\n");
    arr3.backward();
    printf("__________________________\n");

    arr3.print_grad();
    arr1.print_grad();
    arr2.print_grad();
    arr4.print_grad();
}