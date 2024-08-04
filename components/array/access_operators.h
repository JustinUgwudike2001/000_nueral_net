#include "basic_operators.h"


template <typename D>
inline D& Array<D>::operator()(std::vector<size_t> idxes){

    switch(idxes.size()){
        case 1:
            return data[idxes[0]];
            break;
        case 2:
            return data[(idxes[0] * this->shape.strides()[0]) + idxes[1]];
            break;
        case 3:
            return data[(idxes[0] * this->shape.strides()[0]) + (idxes[1] * this->shape.strides()[1]) + idxes[2]];
            break;
        case 4:
            return data[(idxes[0] * this->shape.strides()[0]) + (idxes[1] * this->shape.strides()[1]) + (idxes[2] * this->shape.strides()[2]) + idxes[3]];
            break;
        default:
            std::cout << "Incorrect indexing array"<<this->rank;
            exit(0);
            break;
    }
}

template <typename D>
inline void Array<D>::operator()(D value, std::vector<size_t> idxes){


    switch(idxes.size()){
        case 1:
            data[idxes[0]] = value;
            data[idxes[0]] = 1.;
            break;
        case 2:
            data[(idxes[0] * this->shape.strides()[0]) + idxes[1]] = value;
            dots[(idxes[0] * this->shape.strides()[0]) + idxes[1]] = 1.;
            break;
        case 3:
            data[(idxes[0] * this->shape.strides()[0]) + (idxes[1] * this->shape.strides()[1]) + idxes[2]] = value;
            data[(idxes[0] * this->shape.strides()[0]) + (idxes[1] * this->shape.strides()[1]) + idxes[2]] = 1.;
            break;
        case 4:
            data[(idxes[0] * this->shape.strides()[0]) + (idxes[1] * this->shape.strides()[1]) + (idxes[2] * this->shape.strides()[2]) + idxes[3]] = value;
            dots[(idxes[0] * this->shape.strides()[0]) + (idxes[1] * this->shape.strides()[1]) + (idxes[2] * this->shape.strides()[2]) + idxes[3]] = 1.;
            break;
        default:
            std::cout << "Incorrect indexing array"<<this->rank;
            exit(0);
            break;
    }
}

int test_access_operators(){

    Array<float> array1({16});
    array1.lin();
    array1.print();
    std::cout<<"array1[2]: "<<array1({2})<<std::endl<<std::endl;

    Array<int> array2({2, 4});
    array2.lin();
    array2.print();
    std::cout<<"array2[1][2]: "<<array2({1, 2})<<std::endl<<std::endl;
    
    Array<float> array3({2, 4, 5});
    array3.lin();
    array3.print();
    std::cout<<"array3[1][2][3]: "<<array3({1, 2, 3})<<std::endl<<std::endl;
    
    Array<float> array4({2, 4, 5, 6});
    array4.lin();
    array4.print();
    std::cout<<"array4[1][2][3][4]: "<<array4({1, 2, 3, 4})<<std::endl<<std::endl;

    std::cout<<"array1[1] = 10: "<<std::endl<<std::endl;
    array1({1}) = 10;
    array1.print();

    std::cout<<"array2[1][2] = 10: "<<std::endl<<std::endl;
    array2({1, 2}) = 10;
    array2.print();

    return 0;
}