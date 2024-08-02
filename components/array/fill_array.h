#include "to_array.h"

void Array::fill_arr(float _data[], int size){
    if (size > this->shape.size()) size = this->shape.size();
    int remainder = size - this->shape.size();

    for(int i = 0; i < size; i++){
        data[i] = _data[i];
        dots[i] = 1.;
    }

    // for(int i = 0; i < remainder; i++){
    //     data[size + i] = 0.;
    //     dots[size + i] = 1.;
    // }
}
void Array::fill_vec(std::vector<float> _data, int size){
    if (size > this->shape.size()) size = this->shape.size();
    int remainder = size - this->shape.size();

    for(int i = 0; i < size; i++){
        data[i] = _data[i];
        dots[i] = 1.;
    }

    // for(int i = 0; i < remainder; i++){
    //     data[size + i] = 0.;
    //     dots[size + i] = 1.;
    // }
}
void Array::fill_grad_vec(std::vector<float> _data, std::vector<float> _dots, int size){
    if (data.size() != dots.size()) {
        std::cout << "Data and gradient vectors mus be the same size";
        exit(0);
    }
    if (size > this->shape.size()) size = this->shape.size();
    int remainder = size - this->shape.size();

    for(int i = 0; i < size; i++){
        data[i] = _data[i];
        dots[i] = _dots[i];
    }

    // for(int i = 0; i < remainder; i++){
    //     data[size + i] = 0.;
    //     dots[size + i] = 1.;
    // }
}


inline Array Array::ones(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = 1.;
        dots[i] = 1.;
    }

    return *this;
}
inline Array Array::random(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = float((std::rand() % 1000) + 1)/1000;
        dots[i] = 1.;
    }

    return *this;
}
inline Array Array::zeros(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = 0.;
        dots[i] = 1.;
    }

    return *this;
}
inline Array Array::lin(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = float(i);
        dots[i] = 1.;
    }

    return *this;
}

inline Array Array::ones(int shape_0){
    Array arr(shape_0);
    arr.ones();
    return arr;
}
inline Array Array::ones(int shape_0, int shape_1){

}
inline Array Array::ones(int shape_0, int shape_1, int shape_2){
 
}
inline Array Array::ones(int shape_0, int shape_1, int shape_2, int shape_3){

}

int test_fill_array(){

    float arr[16] = {3.,5.,3.,4.,7.,6.,7.,8.,9.,10.,11.,12.,21.,30.,15.,16};
    std::vector<float> vec(32, 5.);

    Array array1(16);
    array1.fill_arr(arr, 16);

    std::cout<<"fill_arr:"<<std::endl;
    array1.print();

    array1.fill_vec(vec, 10);
    std::cout<<"fill_vec:"<<std::endl;    
    array1.print();
    std::cout<<std::endl;    

    Array array2(2, 3);
    
    array2.ones();
    std::cout<<"ones:"<<std::endl;    
    array2.print();

    array2.zeros();
    std::cout<<"zeros:"<<std::endl;    
    array2.print();
    std::cout<<std::endl;    

    Array array3(2, 3, 4);
    
    array3.lin();
    std::cout<<"lin:"<<std::endl;    
    array3.print();
    std::cout<<std::endl;    

    Array array4(2, 3, 4, 5);
    
    array4.random();
    std::cout<<"random:"<<std::endl;    
    array4.print();
    
    return 0;
}

int test_fill_array_static(){
    Array arr = Array::ones(1);
    arr.print();
}