#include "stack.h"

Array Array::squeeze(int dim){
    if (dim < 0 || dim > this->shape.dims()){
        std::cout<<"Invalid dim: "<<dim<<std::endl;
        exit(0);
    }
    if (this->rank < 2){
        std::cout<<"Array rank: "<<this->rank<<" too small to squeeze"<<std::endl;
        exit(0);
    }
    if(this->shape.shape()[dim] != 1){
        std::cout<<"This dimension: "<<this->shape.shape()[dim]<<" is greater than 1"<<std::endl;
        exit(0); 
    }

    std::vector<int> dims = this->shape.shape();
    dims.erase(dims.begin() + dim); 

    Shape shape(dims, this->shape.dims() - 1);
    Array array(shape);

    array.fill_grad_vec(this->get_data(), this->get_grad(), shape.size());

    return array;
}

Array Array::unsqueeze(int dim){
    if (dim < 0 || dim > this->shape.dims()){
        std::cout<<"Invalid dim: "<<dim<<std::endl;
        exit(0);
    }
    if (this->rank > 3){
        std::cout<<"Array rank: "<<this->rank<<" too big to unsqueeze"<<std::endl;
        exit(0);
    }

    std::vector<int> dims = this->shape.shape();
    dims.insert(dims.begin() + dim, 1); 

    Shape shape(dims, this->shape.dims() + 1);
    Array array(shape);

    array.fill_grad_vec(this->get_data(), this->get_grad(), shape.size());

    return array;
}

int test_squeeze(){
    
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

    return 0;
}