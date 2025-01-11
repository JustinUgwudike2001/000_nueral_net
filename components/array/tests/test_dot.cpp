#include "../dot.h"

int test_dot(){
    
    Array<float> result;
    
    std::cout<<std::endl<<"ARRAY1::::::::::: "<<std::endl;
    Array<float> array1({5});
    array1.set_name("arr1");
    array1.lin();
    array1.get_shape().print();

    Array<float> array1t({5});
    array1t.set_name("arr1.t()");
    array1t = array1.t();
    array1t.get_shape().print();

    std::cout<<std::endl<<"ARRAY2::::::::::: "<<std::endl;
    Array<float> array2({4, 5});
    array2.set_name("arr2");
    array2.lin();
    array2.get_shape().print();

    Array<float> array2t({5, 4});
    array2t.set_name("arr2.t()");
    array2t = array2.t();
    array2t.get_shape().print();

    std::cout<<std::endl<<"ARRAY3::::::::::: "<<std::endl;
    Array<float> array3({3, 4, 5});
    array3.set_name("arr3");
    array3.lin();
    array3.get_shape().print();

    Array<float> array3t({3, 5, 4});
    array3t.set_name("arr3.t()");
    array3t = array3.t();
    array3t.get_shape().print();

    std::cout<<std::endl<<"ARRAY4::::::::::: "<<std::endl;
    Array<float> array4({2, 3, 4, 5});
    array4.set_name("arr4");
    array4.lin();
    array4.get_shape().print();

    Array<float> array4t({2, 3, 5, 4});
    array4t.set_name("arr4.t()");
    array4t = array4.t();
    array4t.get_shape().print();

    // std::cout<<"------------------------------------------"<<std::endl;
    // std::cout<<std::endl<<"arr1.arr1.t()"<<std::endl;
    // result = array1.dot(array1t);
    // result.print();

    // std::cout<<std::endl<<"arr1.t().arr1"<<std::endl;
    // result = array1t.dot(array1);
    // result.print();

    // std::cout<<"------------------------------------------"<<std::endl;
    // std::cout<<std::endl<<"arr2.arr1.t()"<<std::endl;
    // result = array2.dot(array1t);
    // result.print();

    // std::cout<<std::endl<<"arr1.arr2.t()"<<std::endl;
    // result = array1.dot(array2t);
    // result.print();

    // std::cout<<std::endl<<"arr2.arr2.t()"<<std::endl;
    // result = array2.dot(array2t);
    // result.print();

    // std::cout<<std::endl<<"arr2.t().arr2"<<std::endl;
    // result = array2t.dot(array2);
    // result.print();

    std::cout<<"------------------------------------------"<<std::endl;
    // std::cout<<std::endl<<"arr3.arr1.t()"<<std::endl;
    // result = array3.dot(array1t);
    // result.get_shape().print();

    // std::cout<<std::endl<<"arr1.arr3.t()"<<std::endl;
    // result = array1.dot(array3t);
    // result.get_shape().print();

    // std::cout<<std::endl<<"arr3.arr2.t()"<<std::endl;
    // result = array3.dot(array2t);
    // result.get_shape().print();

    // std::cout<<std::endl<<"arr2.t().arr3"<<std::endl;
    // result = array2t.dot(array3);
    // result.get_shape().print();

    std::cout<<std::endl<<"arr3.arr3.t()"<<std::endl;
    result = array3.dot(array3t);
    result.get_shape().print();

    std::cout<<std::endl<<"arr3.t().arr3"<<std::endl;
    result = array3t.dot(array3);
    result.get_shape().print();

    return 0;
}

int main()
{
    test_dot();
}