#include "fill_array.h"

template <typename D>
inline Array<D> Array<D>::operator=(const Array& arr2){

    if (this == &arr2)
        return *this;

    this->data = arr2.data;
    this->dots = arr2.dots;
    this->shape = arr2.shape;
    this->rank = arr2.rank;
    //strcpy(arr2.name, this->name);
    
    return *this;
}

template <typename D>
template <typename U>
inline Array<D>& Array<D>::operator=(Array<U>& arr2){    
    // Clear current data and resize
    data.clear();
    data.resize(arr2.get_shape().size());

    std::vector<U> new_data = arr2.get_data();
    std::vector<float> new_dots = arr2.get_grad();

    for(int i = 0; i < arr2.get_shape().size(); i++){
        data[i] = new_data[i];
        dots[i] = new_dots[i];
    }

    return *this;
}

template <typename D>
Array<D> Array<D>::operator+(D rhs){
    Array<D> arr = Array<D>(this->shape);

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] + rhs;
        arr.dots[i] = this->dots[i] + rhs;
    }

    return arr;
}
template <typename D>
Array<D> Array<D>::operator-(D rhs){
    Array<D> arr = Array<D>(this->shape);

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] - rhs;
        arr.dots[i] = this->dots[i] - rhs;
    }

    return arr;
}
template <typename D>
Array<D> Array<D>::operator/(D rhs){
    Array<D> arr = Array<D>(this->shape);

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] / rhs;
        arr.dots[i] = this->dots[i] / rhs;
    }

    return arr;
}
template <typename D>
Array<D> Array<D>::operator*(D rhs){
    Array<D> arr = Array<D>(this->shape);

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] * rhs;
        arr.dots[i] = this->dots[i] * rhs;
    }

    return arr;
}
template <typename D>
Array<D> Array<D>::operator^(D rhs){
    Array<D> arr = Array<D>(this->shape);
    
    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = std::pow(this->data[i], rhs);
        arr.dots[i] = rhs * this->dots[i] * std::pow(this->data[i], rhs - 1);
    }

    return arr;
}
template <typename D>
Array<D> Array<D>::operator+(Array& rhs){

    if (this->shape.size() != rhs.shape.size()) {
        std::cout << "These arrays are not equal size";
        exit(0);
    }

    Array<D> arr = Array<D>(this->shape);

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] + rhs.data[i];
        arr.dots[i] = this->dots[i] + rhs.dots[i];
    }

    return arr;
}
template <typename D>
Array<D> Array<D>::operator-(Array& rhs){

    if (this->shape.size() != rhs.shape.size()) {
        std::cout << "These arrays are not equal size";
        exit(0);
    }

    Array<D> arr = Array<D>(this->shape);

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] - rhs.data[i];
        arr.dots[i] = this->dots[i] - rhs.dots[i];
    }

    return arr;
}
template <typename D>
Array<D> Array<D>::operator/(Array& rhs){

    if (this->shape.size() != rhs.shape.size()) {
        std::cout << "These arrays are not equal size";
        exit(0);
    }

    Array<D> arr = Array<D>(this->shape);

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] / rhs.data[i];
        arr.dots[i] = (this->dots[i] * rhs.data[i] - this->data[i] * rhs.dots[i])/(rhs.data[i] * rhs.data[i]);
    }

    return arr;
}
template <typename D>
Array<D> Array<D>::operator*(Array& rhs){

    if (this->shape.size() != rhs.shape.size()) {
        std::cout << "These arrays are not equal size";
        exit(0);
    }

    Array<D> arr = Array<D>(this->shape);

    for(int i = 0; i < this->shape.size(); i++){
        arr.data[i] = this->data[i] * rhs.data[i];
        arr.dots[i] = (this->data[i] * rhs.dots[i]) + (this->dots[i] * rhs.data[i]);
    }

    return arr;
}

int test_basic_operators(){

    Array<float> array1({16});
    array1.lin();
    array1.print();
    Array<float> array1_1({16});
    array1_1.ones();
    array1_1.set_name("array1_1");
    array1_1.print();

    array1 = array1 + array1_1;

    std::cout<<"array1 + array1_1: " <<std::endl;
    array1.print();

    std::cout<<"array1 + 5: " <<std::endl;
    array1_1 = array1 + 5;
    array1_1.print();

    std::cout<<"array1 - 5: " <<std::endl;
    array1_1 = array1 - 5;
    array1_1.print();

    std::cout<<"array1 * 5: " <<std::endl;
    array1_1 = array1 * 5;
    array1_1.print();

    std::cout<<"array1 / 5: " <<std::endl;
    array1_1 = array1 / 5;
    array1_1.print();

    std::cout<<"array1 ^ 3: " <<std::endl;
    array1_1 = array1 ^ 3;
    array1_1.print();

    std::cout<<std::endl;

    Array<float> array2({4,4});
    array2.zeros();
    array2.print();

    std::cout<<"array2 * array1: " <<std::endl;
    array2 = array2 + array1;
    array2.print();

    std::cout<<"array2 / array1: " <<std::endl;
    array2 = array2 / array1;
    array2.print();

    std::cout<<"array2 * array1: " <<std::endl;
    array2 = array2 * array1;
    array2.print();
    std::cout<<std::endl;

    Array<float> array4({2,2,2,2});
    array4.ones();
    array4.print();

    std::cout<<"array4 - array1: " <<std::endl;
    array4 = array4 - array1;
    array4.print();

    Array<int> ints({10});
    ints.lin();
    ints.print();
    Array<float> floats({10});
    floats = ints;
    floats.print();
    
    return 0;
}