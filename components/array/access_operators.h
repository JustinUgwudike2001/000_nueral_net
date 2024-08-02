#include "basic_operators.h"

inline float& Array::operator()(std::size_t idx_1){
    if (this->rank != 1) {
        std::cout << "Incorrect indexing array"<<this->rank;
        exit(0);
    }
    if (idx_1 >= this->shape.size()) {
        std::cout << "Array index out of bound, exiting";
        exit(0);
    }
    return data[idx_1];
}

inline float& Array::operator()(std::size_t idx_1, std::size_t idx_2){
    if (this->rank != 2) {
        std::cout << "Incorrect indexing array"<<this->rank;
        exit(0);
    }
    if (idx_1 >= this->shape.shape()[0] || idx_2 >= this->shape.shape()[1]) {
        std::cout << "Array index out of bound, exiting";
        exit(0);
    }

    return data[(idx_1 * this->shape.strides()[0]) + idx_2];
}

inline float& Array::operator()(std::size_t idx_1, std::size_t idx_2, std::size_t idx_3){
    if (this->rank != 3) {
        std::cout << "Incorrect indexing array"<<this->rank;
        exit(0);
    }
    if (idx_1 >= this->shape.shape()[0] || idx_2 >= this->shape.shape()[1] || idx_3 >= this->shape.shape()[2]) {
        std::cout << "Array index out of bound, exiting";
        exit(0);
    }

    return data[(idx_1 * this->shape.strides()[0]) + (idx_2 * this->shape.strides()[1]) + idx_3];
}


inline float& Array::operator()(std::size_t idx_1, std::size_t idx_2, std::size_t idx_3, std::size_t idx_4){
    if (this->rank != 4) {
        std::cout << "Incorrect indexing array"<<this->rank;
        exit(0);
    }
    if (idx_1 >= this->shape.shape()[0] || idx_2 >= this->shape.shape()[1] || idx_3 >= this->shape.shape()[2] || idx_4 >= this->shape.shape()[3]) {
        std::cout << "Array index out of bound, exiting";
        exit(0);
    }

    return data[(idx_1 * this->shape.strides()[0]) + (idx_2 * this->shape.strides()[1]) + (idx_3 * this->shape.strides()[2]) + idx_4];
}

int test_access_operators(){

    Array array1(16);
    array1.lin();
    array1.print();
    std::cout<<"array1[2]: "<<array1(2)<<std::endl<<std::endl;

    Array array2(2, 4);
    array2.lin();
    array2.print();
    std::cout<<"array2[1][2]: "<<array2(1, 2)<<std::endl<<std::endl;
    
    Array array3(2, 4, 5);
    array3.lin();
    array3.print();
    std::cout<<"array3[1][2][3]: "<<array3(1, 2, 3)<<std::endl<<std::endl;
    
    Array array4(2, 4, 5, 6);
    array4.lin();
    array4.print();
    std::cout<<"array4[1][2][3][4]: "<<array4(1, 2, 3, 4)<<std::endl<<std::endl;

    return 0;
}