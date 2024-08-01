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