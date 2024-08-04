#include "reshape.h"

template <typename D>
Array<D> Array<D>::t(){
    Array arr = *this;

    switch(arr.rank){
        case 1:
            arr = arr.permute({1, 0});
            break;
        case 2:
            arr = arr.permute({1, 0});
            break;
        case 3:
            arr = arr.permute({0, 2, 1});
            break;
        case 4:
            arr = arr.permute({0, 1, 3, 2});
            break;
        default:
            std::cout<<"Invalid rank";
            exit(0);
            break;
    }

    return arr;
}

template <typename D>
Array<D> Array<D>::permute(std::vector<int> dims){

    if (this->shape.dims() != dims.size()) {
        printf("Dimension mismatch, input dims: %d not equal to array%d dims", dims.size(), this->rank);
        exit(0);
    }

    Array arr = *this;

    std::vector<D> new_data(arr.shape.size());
    std::vector<float> new_dots(arr.shape.size(), 0.);

    int count = 0;

    switch(dims.size()){
        case 1: case 2:
            for (int j = 0; j < arr.shape.shape()[dims[0]]; j++){
                for (int i = 0; i < arr.shape.shape()[dims[1]]; i++){
                    new_data[count] = arr.data[j * arr.shape.strides()[dims[0]] + i * arr.shape.strides()[dims[1]]];
                    new_dots[count] = arr.dots[j * arr.shape.strides()[dims[0]] + i * arr.shape.strides()[dims[1]]];
                    count+=1;
                }
             }
            break;
        case 3:
            for (int k = 0; k < arr.shape.shape()[dims[0]]; k++){
                for (int j = 0; j < arr.shape.shape()[dims[1]]; j++){
                    for (int i = 0; i < arr.shape.shape()[dims[2]]; i++){
                        new_data[count] = arr.data[k * arr.shape.strides()[dims[0]] + j * arr.shape.strides()[dims[1]] + i * arr.shape.strides()[dims[2]]];
                        new_dots[count] = arr.dots[k * arr.shape.strides()[dims[0]] + j * arr.shape.strides()[dims[1]] + i * arr.shape.strides()[dims[2]]];
                        count+=1;
                    }
                }
            }
            break;
        case 4:
            for (int l = 0; l < arr.shape.shape()[dims[0]]; l++){
                for (int k = 0; k < arr.shape.shape()[dims[1]]; k++){
                    for (int j = 0; j < arr.shape.shape()[dims[2]]; j++){
                        for (int i = 0; i < arr.shape.shape()[dims[3]]; i++){
                            new_data[count] = arr.data[l * arr.shape.strides()[dims[0]] + k * arr.shape.strides()[dims[1]] + j * arr.shape.strides()[dims[2]] + i * arr.shape.strides()[dims[3]]];
                            new_dots[count] = arr.dots[l * arr.shape.strides()[dims[0]] + k * arr.shape.strides()[dims[1]] + j * arr.shape.strides()[dims[2]] + i * arr.shape.strides()[dims[3]]];
                            count+=1;
                        }
                    }
                }
            }
            break;
        default:
            break;
    }

    arr.shape.permute(dims);

    arr.data = new_data;
    arr.dots = new_dots;

    return arr;
}

int test_permute(){
    
    Array<float> array1({4});
    array1.lin();
    array1.print();

    std::cout<<"array1 t():"<<std::endl;
    array1 = array1.t();
    array1.print();
    std::cout<<std::endl;

    Array<float> array2({3, 2});
    array2.lin();
    array2.print();

    std::cout<<"array2 t():"<<std::endl;
    array2 = array2.t();
    array2.print();
    std::cout<<std::endl;

    Array<float> array3({4, 3, 2});
    array3.lin();
    array3.print();

    std::cout<<"array3 t():"<<std::endl;
    array3 = array3.t();
    array3.print();
    std::cout<<std::endl;

    Array<float> array4({2, 4, 3, 2});
    array4.lin();
    array4.print();

    std::cout<<"array4 t():"<<std::endl;
    array4 = array4.t();
    array4.print();
    std::cout<<std::endl;

    std::cout<<"array4 permute(3, 2, 1, 0):"<<std::endl;
    Array<float> array5({2, 4, 3, 2});
    array5.lin();
    array5 = array5.permute({3,2,1,0});
    array5.print();
    std::cout<<std::endl;

    std::cout<<"array5: "<<std::endl;
    Array<float> array6({4, 3, 2});
    array6.lin();
    array6.print();

    std::cout<<"array5 permute(1, 0, 2):"<<std::endl;
    array6 = array6.permute({1,0,2});
    array6.print();
    std::cout<<std::endl;

    return 0;
}