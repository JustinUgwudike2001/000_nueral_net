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


Array Array::ones(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = 1.;
        dots[i] = 1.;
    }

    return *this;
}
Array Array::random(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = float((std::rand() % 1000) + 1)/1000;
        dots[i] = 1.;
    }

    return *this;
}
Array Array::zeros(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = 0.;
        dots[i] = 1.;
    }

    return *this;
}
Array Array::lin(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = float(i);
        dots[i] = 1.;
    }

    return *this;
}
    Shape s;
    switch(rank){
        case 1:
            s = Shape({shape[0]}, 1);
            break;
        case 2:
            s = Shape({shape[0], shape[1]}, 2);
            break;
        case 3:
            s = Shape({shape[0], shape[1], shape[2]}, 3);
            break;
        case 4:
            s = Shape({shape[0], shape[1], shape[2], shape[3]}, 4);
            break;
        default:
            std::cout<<"Invalid shape"<<std::endl;
            exit(0);
            break;
    }
    
    Array arr(s);
    arr.lin();

    return arr;
}