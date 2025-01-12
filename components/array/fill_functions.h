#include "broadcast.h"

template <typename D>
Array<D> Array<D>::triu(int _offest = 0)
{
    Array<D> triu_arr(this->shape);

    int offset = -1 + _offest;

    switch(this->rank){
        case 2:
            for(int i = 0; i < this->shape.shape()[0]; i++){
                offset += 1;
                for(int j = 0; j < this->shape.shape()[1]; j++){
                    triu_arr.data[this->shape.strides()[0] * i + this->shape.strides()[1] * j] = (j < offset ? 0 : data[this->shape.strides()[0] * i + this->shape.strides()[1] * j]);
                    triu_arr.nodes[this->shape.strides()[0] * i + this->shape.strides()[1] * j] = (j < offset ? std::make_shared<Node<D>>(0) : nodes[this->shape.strides()[0] * i + this->shape.strides()[1] * j]);

                }
            }
            break;
        case 3:
            for(int i = 0; i < this->shape.shape()[0]; i++){
                offset = -1 + _offest;
                for(int j = 0; j < this->shape.shape()[1]; j++){
                    offset += 1;
                    for(int k = 0; k < this->shape.shape()[2]; k++){
                        triu_arr.data[this->shape.strides()[0] * i + this->shape.strides()[1] * j + this->shape.strides()[2] * k] = (k < offset ? 0 : data[this->shape.strides()[0] * i + this->shape.strides()[1] * j + this->shape.strides()[2] * k]);
                        triu_arr.data[this->shape.strides()[0] * i + this->shape.strides()[1] * j + this->shape.strides()[2] * k] = (k < offset ?  std::make_shared<Node<D>>(0) : nodes[this->shape.strides()[0] * i + this->shape.strides()[1] * j + this->shape.strides()[2] * k]);
                    }
                }
            }
            break;
        case 4:
            for(int i = 0; i < this->shape.shape()[0]; i++){
                for(int j = 0; j < this->shape.shape()[1]; j++){
                    offset = -1 + _offest;
                    for(int k = 0; k < this->shape.shape()[2]; k++){
                        offset += 1;
                        for(int l = 0; l < this->shape.shape()[3]; l++){
                            triu_arr.data[this->shape.strides()[0] * i + this->shape.strides()[1] * j + this->shape.strides()[2] * k + this->shape.strides()[3] * l] = (l < offset ? 0 : data[this->shape.strides()[0] * i + this->shape.strides()[1] * j + this->shape.strides()[2] * k+ this->shape.strides()[3] * l]);
                            triu_arr.data[this->shape.strides()[0] * i + this->shape.strides()[1] * j + this->shape.strides()[2] * k + this->shape.strides()[3] * l] = (l < offset ?  std::make_shared<Node<D>>(0) : nodes[this->shape.strides()[0] * i + this->shape.strides()[1] * j + this->shape.strides()[2] * k+ this->shape.strides()[3] * l]);
                        }
                    }
                }
            }
            break;
        default:
            printf("Cannot create triu array with Array%d", this->rank);
            exit(0);
            break;
    }

    return triu_arr;
}

int test_fill_functions(){

    Array<float> result;

    Array<float> arr2({10, 10});
    arr2.random();
    arr2.print();
    result = arr2.triu();
    result.print();

    result = arr2.triu(2);
    result.print();

    Array<float> arr3({2, 10, 10});
    arr3.random();
    arr3.print();
    result = arr3.triu();
    result.print();

    Array<float> arr4({2, 3, 5, 5});
    arr4.random();
    arr4.print();
    result = arr4.triu();
    result.print();



    return 0;
}