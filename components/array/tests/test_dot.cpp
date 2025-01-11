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
    Array<float> array3({6, 4, 5});
    array3.set_name("arr3");
    array3.lin();
    array3.get_shape().print();

    Array<float> array3t({6, 5, 4});
    array3t.set_name("arr3.t()");
    array3t = array3.t();
    array3t.get_shape().print();

    Array<float> array31({1, 5, 4});
    array31.set_name("arr31");
    array31.lin();
    array31.get_shape().print();

    Array<float> array32({2, 5, 4});
    array32.set_name("arr32");
    array32.lin();
    array32.get_shape().print();

    Array<float> array33({3, 5, 4});
    array33.set_name("arr33");
    array33.lin();
    array33.get_shape().print();

    Array<float> array34({4, 5, 4});
    array34.set_name("arr34");
    array34.lin();
    array34.get_shape().print();

    std::cout<<std::endl<<"ARRAY4::::::::::: "<<std::endl;
    Array<float> array4({2, 3, 4, 5});
    array4.set_name("arr4");
    array4.lin();
    array4.get_shape().print();

    Array<float> array4t({2, 3, 5, 4});
    array4t.set_name("arr4.t()");
    array4t = array4.t();
    array4t.get_shape().print();

    Array<float> array41({1, 3, 5, 4});
    array41.set_name("arr41");
    array41.lin();
    array41.get_shape().print();

    Array<float> array46({6, 3, 5, 4});
    array46.set_name("arr46");
    array46.lin();
    array46.get_shape().print();

    Array<float> array43({3, 3, 5, 4});
    array43.set_name("arr43");
    array43.lin();
    array43.get_shape().print();

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

    // std::cout<<"------------------------------------------"<<std::endl;
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

    // std::cout<<std::endl<<"arr3.arr3.t()"<<std::endl;
    // result = array3.dot(array3t);
    // result.get_shape().print();

    // std::cout<<std::endl<<"arr3.t().arr3"<<std::endl;
    // result = array3t.dot(array3);
    // result.get_shape().print();

    // std::cout<<std::endl<<"arr3.arr31"<<std::endl;
    // result = array3.dot(array31);
    // result.get_shape().print();

    // std::cout<<std::endl<<"arr3.arr32"<<std::endl;
    // result = array3.dot(array32);
    // result.get_shape().print();

    // std::cout<<std::endl<<"arr3.arr33"<<std::endl;
    // result = array3.dot(array33);
    // result.get_shape().print();

    // std::cout<<std::endl<<"arr3.arr34"<<std::endl; // won't compile
    // result = array3.dot(array34);
    // result.get_shape().print();

    std::cout<<"------------------------------------------"<<std::endl;
    std::cout<<std::endl<<"arr4.arr1.t()"<<std::endl;
    result = array4.dot(array1t);
    result.get_shape().print();

    std::cout<<std::endl<<"arr1.arr4.t()"<<std::endl;
    result = array1.dot(array4t);
    result.get_shape().print();

    std::cout<<std::endl<<"arr4.arr2.t()"<<std::endl;
    result = array4.dot(array2t);
    result.get_shape().print();

    std::cout<<std::endl<<"arr2.t().arr4"<<std::endl;
    result = array2t.dot(array4);
    result.get_shape().print();

    std::cout<<std::endl<<"arr4.arr3.t()"<<std::endl;
    result = array4.dot(array3t);
    result.get_shape().print();

    std::cout<<std::endl<<"arr3.t().arr4"<<std::endl;
    result = array3t.dot(array4);
    result.get_shape().print();

    std::cout<<std::endl<<"arr4.arr34"<<std::endl;
    result = array4.dot(array33);
    result.get_shape().print();

    std::cout<<std::endl<<"arr4.arr31"<<std::endl;
    result = array4.dot(array31);
    result.get_shape().print();

    std::cout<<std::endl<<"arr4.arr4.t()"<<std::endl;
    result = array4.dot(array4t);
    result.get_shape().print();

    std::cout<<std::endl<<"arr4.t().arr4"<<std::endl;
    result = array4t.dot(array4);
    result.get_shape().print();

    std::cout<<std::endl<<"arr4.arr41"<<std::endl;
    result = array4.dot(array41);
    result.get_shape().print();

    std::cout<<std::endl<<"arr4.arr46"<<std::endl;
    result = array4.dot(array46);
    result.get_shape().print();

    // std::cout<<std::endl<<"arr4.arr43"<<std::endl; // won't compile
    // result = array4.dot(array43);
    // result.print();

    return 0;
}

int main()
{
    test_dot();
}