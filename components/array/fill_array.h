#include "to_array.h"

template <typename D>
inline void Array<D>::fill_arr(D _data[], int size){
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

template <typename D>
inline void Array<D>::fill_vec(std::vector<D> _data, int size){
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

template <typename D>
inline void Array<D>::fill_grad_vec(std::vector<D> _data, std::vector<float> _dots, int size){
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

template <>
inline Array<float> Array<float>::ones(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = float(1.);
        dots[i] = 1.;
    }

    return *this;
}
template <>
inline Array<int> Array<int>::ones(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = int(1);
        dots[i] = 1.;
    }

    return *this;
}
template <>
inline Array<float> Array<float>::random(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = float((std::rand() % 1000) + 1)/1000;
        dots[i] = 1.;
    }

    return *this;
}
template <>
inline Array<int> Array<int>::random(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = int((std::rand() % 1000) + 1);
        dots[i] = 1.;
    }

    return *this;
}
template <>
inline Array<float> Array<float>::zeros(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = float(0.);
        dots[i] = 1.;
    }

    return *this;
}
template <>
inline Array<int> Array<int>::zeros(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = int(0);
        dots[i] = 1.;
    }

    return *this;
}
template <>
inline Array<float> Array<float>::lin(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = float(i);
        dots[i] = 1.;
    }

    return *this;
}
template <>
inline Array<int> Array<int>::lin(){
    for(int i = 0; i< this->shape.size(); i++){
        data[i] = int(i);
        dots[i] = 1.;
    }

    return *this;
}

template <typename D>
inline Array<D> Array<D>::ones(std::initializer_list<int> dims){
    Array<D> arr(dims);
    arr.ones();
    return arr;
}

template <typename D>
inline Array<D> Array<D>::zeros(std::initializer_list<int> dims){
    Array<D> arr(dims);
    arr.zeros();
    return arr;
}

template <typename D>
inline Array<D> Array<D>::random(std::initializer_list<int> dims){
    Array<D> arr(dims);
    arr.random();
    return arr;
}

template <typename D>
inline Array<D> Array<D>::lin(std::initializer_list<int> dims){
    Array<D> arr(dims);
    arr.lin();
    return arr;
}


template <typename D>
inline Array<D> Array<D>::from_array(std::initializer_list<int> dims, std::initializer_list<D> array){
    std::vector<D> data(array);
    std::vector<D> flat_data;
    Array<D> arr(dims);

    if (arr.shape.size() != array.size()){
        printf("The size: %d of the array does not match the size of the array: %d.", arr.shape.size(), array.size());
        exit(0);
    }

    // for (const auto& subVector : data) {
    //     flat_data.insert(flat_data.end(), subVector.begin(), subVector.end());
    // }

    arr.fill_vec(data, arr.shape.size());
    return arr;
}

int test_fill_array(){

    std::cout<<"FILL_ARR:::::::::::::::::::::::::::::"<<std::endl;

    float arr[16] = {3.,5.,3.,4.,7.,6.,7.,8.,9.,10.,11.,12.,21.,30.,15.,16};
    std::vector<float> vec(32, 5.);

    Array<float> array1({16});
    array1.fill_arr(arr, 16);

    std::cout<<"fill_arr:"<<std::endl;
    array1.print();

    array1.fill_vec(vec, 10);
    std::cout<<"fill_vec:"<<std::endl;    
    array1.print();
    std::cout<<std::endl;    

    Array<float> array2({2, 3});
    
    array2.ones();
    std::cout<<"ones:"<<std::endl;    
    array2.print();

    array2.zeros();
    std::cout<<"zeros:"<<std::endl;    
    array2.print();
    std::cout<<std::endl;    

    Array<float> array3({2, 3, 4});
    
    array3.lin();
    std::cout<<"lin:"<<std::endl;    
    array3.print();
    std::cout<<std::endl;    

    Array<float> array4({2, 3, 4, 5});
    
    array4.random();
    std::cout<<"random:"<<std::endl;    
    array4.print();
    
    return 0;
}
int test_fill_array_static(){

    std::cout<<"FILL_ARR_STATIC:::::::::::::::::::::::::::::"<<std::endl;
    Array<int> arr = Array<int>::ones({1});
    arr.print();

    Array<int> arr1 = Array<int>::ones({1, 2});
    arr1.print();

    Array<int> arr2 = Array<int>::ones({1, 2, 3});
    arr2.print();

    Array<int> arr3 = Array<int>::ones({1, 2, 3, 4});
    arr3.print();

    Array<float> arr4 = Array<float>::random({1});
    arr4.print();

    Array<int> arr5 = Array<int>::random({1, 2});
    arr5.print();

    Array<int> arr6 = Array<int>::random({1, 2, 3});
    arr6.print();

    Array<float> arr7 = Array<float>::random({1, 2, 3, 4});
    arr7.print();

    Array<int> arr8 = Array<int>::from_array({2, 4}, {1, 2, 3, 4, 4, 4, 4, 5});
    arr8.print();

    Array<float> arr9 = Array<float>::from_array({1, 8}, {1., 2., 3., 4., 4., 4., 4., 5.});
    arr9.print();

    return 0;

}