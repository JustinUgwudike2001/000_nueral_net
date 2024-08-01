#include "array_object.h"

Array::Array(){
    strcpy(this->name, "array");
}
Array::Array(Shape s){
    this->shape = s;
    this->rank = s.dims();
    strcpy(this->name, "array");

    for(int i = 0; i< this->shape.size(); i++){
        data.push_back(0.);
        dots.push_back(1.);
    }
}

Array::Array(int _shape){
    Shape s({_shape}, 1);
    this->shape = s;
    this->rank = 1;
    strcpy(this->name, "array1");

    for(int i = 0; i< this->shape.size(); i++){
        data.push_back(0.);
        dots.push_back(1.);
    }
}
Array::Array(int _shape_0, int _shape_1){
    Shape s({_shape_0, _shape_1}, 2);
    this->shape = s;
    this->rank = 2;
    strcpy(this->name, "array2");

    for(int i = 0; i< this->shape.size(); i++){
        data.push_back(0.);
        dots.push_back(1.);
    }
}
Array::Array(int _shape_0, int _shape_1, int _shape_2){
    Shape s({_shape_0, _shape_1, _shape_2}, 3);
    this->shape = s;
    this->rank = 3;
    strcpy(this->name, "array3");

    for(int i = 0; i< this->shape.size(); i++){
        data.push_back(0.);
        dots.push_back(1.);
    }
}
Array::Array(int _shape_0, int _shape_1, int _shape_2, int _shape_3){
    Shape s({_shape_0, _shape_1, _shape_2, _shape_3}, 4);
    this->shape = s;
    this->rank = 4;
    strcpy(this->name, "array4");

    for(int i = 0; i< this->shape.size(); i++){
        data.push_back(0.);
        dots.push_back(1.);
    }
}

Array Array::create_arr(){
    std::vector<int> shape = this->get_shape().shape();

    switch(this->rank){
        case 1:
            return Array(this->shape.size());
        case 2:
            return Array(shape[0],shape[1]);
        case 3:
            return Array(shape[0], shape[1], shape[2]);
        case 4:
            return Array(shape[0], shape[1], shape[2], shape[3]);
        default:
            return Array(this->shape.size());
    }
}

int test_constructors(){

    Array empty_arr;

    Array array1(100);
    std::cout<<"array1 shape: "
        <<array1.get_shape().shape()[0]<<", "
        <<array1.get_shape().shape()[1]
        <<std::endl;      
        
    Array array2(10, 10);
    std::cout<<"array2 shape: "
        <<array2.get_shape().shape()[0]<<", "
        <<array2.get_shape().shape()[1]
        <<std::endl;

    Array array3(10, 5, 2);
    std::cout<<"array3 shape: "
        <<array3.get_shape().shape()[0]<<", "
        <<array3.get_shape().shape()[1]<<", "
        <<array3.get_shape().shape()[2]
        <<std::endl;

    Array array4(2, 5, 5, 2);
    std::cout<<"array4 shape: "
        <<array4.get_shape().shape()[0]<<", "
        <<array4.get_shape().shape()[1]<<", "
        <<array4.get_shape().shape()[2]<<", "
        <<array4.get_shape().shape()[3]
        <<std::endl;

    return 0;

}