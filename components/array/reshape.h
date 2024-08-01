#include "access_operators.h"

Array Array::reshape(int shape_0){
    Shape shape({1, shape_0}, 2);

    if (this->shape.size() != shape.size()) {
        std::cout << "Shape size not equal";
        exit(0);
    }

    this->shape = shape;
    this->rank = 1;
    strcpy(this->name, "array1");
    
    return *this;
}

Array Array::reshape(int shape_0, int shape_1){
    Shape shape({shape_0, shape_1}, 2);

    if (this->shape.size() != shape.size()) {
        std::cout << "Shape size not equal";
        exit(0);
    }

    this->shape = shape;
    this->rank = 2;
    strcpy(this->name, "array2");
    
    return *this;
}

Array Array::reshape(int shape_0, int shape_1, int shape_2){
    Shape shape({shape_0, shape_1, shape_2}, 3);

    if (this->shape.size() != shape.size()) {
        std::cout << "Shape size not equal";
        exit(0);
    }

    this->shape = shape;
    this->rank = 3;
    strcpy(this->name, "array3");

    return *this;
}

Array Array::reshape(int shape_0, int shape_1, int shape_2, int shape_3){
    Shape shape({shape_0, shape_1, shape_2, shape_3}, 4);

    if (this->shape.size() != shape.size()) {
        std::cout << "Shape size not equal";
        exit(0);
    }

    this->shape = shape;
    this->rank = 4;
    strcpy(this->name, "array4");

    return *this;
}

int test_reshape(){
        
    Array array1(16);
    array1.random();
    array1.print();
    std::cout<<std::endl;

    array1.reshape(4,4);
    array1.print();
    std::cout<<std::endl;

    array1.reshape(2,2,4);
    array1.print();
    std::cout<<std::endl;

    array1.reshape(2,2,2,2);
    array1.print();
    std::cout<<std::endl;

    Array array2(2,2,3,4);
    array2.lin();
    array2.print();
    std::cout<<std::endl;

    array2.reshape(2,2,12);
    array2.print();
    std::cout<<std::endl;

    array2.reshape(2,24);
    array2.print();
    std::cout<<std::endl;

    array2.reshape(48);
    array2.print();

    return 0;
}