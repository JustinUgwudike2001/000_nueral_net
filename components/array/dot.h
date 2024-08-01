#include "squeeze.h"
Array Array::dot(Array& rhs){
    Array arr;
    
    switch(this->rank){
        case 1:
            arr = this->try_dot_arr1(rhs);
            break; 
        case 2:
            arr = this->try_dot_arr2(rhs);
            break; 
        case 3:
            arr = this->try_dot_arr3(rhs);
            break; 
        case 4:
            arr = this->try_dot_arr4(rhs);
            break; 
        default:
            std::cout<<"Cannot compute dot product between array" <<this->rank<<" and array"<<rhs.rank<<std::endl;
            exit(0);
            break; 
    }

    return arr;
}

Array Array::try_dot_arr1(Array& rhs){
    Array lhs, _rhs, result;
    int dim1, dim2;
    std::vector<Array> arrays, result_arrays;

    switch(rhs.rank){
        case 1:
            //arr1.arr1
            result = this->try_dot(*this, rhs);
            break;
        case 2:
            //arr1.arr2
            result = this->try_dot(*this, rhs);
            break;
        case 3:
            //arr1.arr3
            dim1 = rhs.shape.shape()[1];
            dim2 = rhs.shape.shape()[2];
            
            _rhs = rhs;
            _rhs.reshape(rhs.shape.shape()[0], dim1 * dim2);
            result = this->try_dot(*this, _rhs);
            result = result.reshape(this->get_shape().shape()[0], dim1, dim2);
            result = result.squeeze(0);
            break;
        case 4:
            //arr1.arr4
            arrays = rhs.split(3);
            dim1 = rhs.shape.shape()[1];
            dim2 = rhs.shape.shape()[2];

            for(int i = 0; i <rhs.shape.shape()[3]; i++){
                _rhs = arrays[i];
                _rhs.reshape(arrays[0].shape.shape()[0], dim1 * dim2);

                result = this->try_dot(*this, _rhs);
                result = result.reshape(this->shape.shape()[0], dim1, dim2);
                result_arrays.push_back(result);
            }

            result = stack(result_arrays, rhs.shape.shape()[3], 3);
            result = result.squeeze(0);
            break;
        default: 
            std::cout<<"Cannot compute dot product between array" <<this->rank<<" and array"<<rhs.rank<<std::endl;
            exit(0);
            break;
    }
    
    return result;
}
Array Array::try_dot_arr2(Array& rhs){
    Array lhs, _rhs, result;
    int dim1, dim2;
    std::vector<Array> arrays, result_arrays;

    switch(rhs.rank){
        case 1:
            //arr2.arr1
            result = this->try_dot(*this, rhs);
            break;
        case 2:
            //arr2.arr2
            result = this->try_dot(*this, rhs);
            break;
        case 3:
            //arr2.arr3
            dim1 = rhs.shape.shape()[1];
            dim2 = rhs.shape.shape()[2];

            _rhs = rhs;
            _rhs.reshape(rhs.shape.shape()[0], dim1 * dim2);
            result = this->try_dot(*this, _rhs);
            result = result.reshape(this->get_shape().shape()[0], dim1, dim2);
            break;
        case 4:
            //arr2.arr4
            arrays = rhs.split(3);
            dim1 = rhs.shape.shape()[1];
            dim2 = rhs.shape.shape()[2];

            for(int i = 0; i <rhs.shape.shape()[3]; i++){
                _rhs = arrays[i];
                _rhs.reshape(arrays[0].shape.shape()[0], dim1 * dim2);
                
                result = this->try_dot(*this, _rhs);
                result = result.reshape(this->shape.shape()[0], dim1, dim2);
                result_arrays.push_back(result);
            }

            result = stack(result_arrays, rhs.shape.shape()[3], 3);
            break;
        default:
            std::cout<<"Cannot compute dot product between array" <<this->rank<<" and array"<<rhs.rank<<std::endl;
            exit(0);
            break;
    }

    return result;
}
Array Array::try_dot_arr3(Array& rhs){
    Array lhs, _rhs, result;
    int dim1, dim2, dim3, dim4;


    switch(rhs.rank){
        case 1:
            //arr3.arr1 
            lhs = *this;
            dim1 = lhs.shape.shape()[0];
            dim2 = lhs.shape.shape()[1];

            lhs.reshape(dim1 * dim2, lhs.shape.shape()[2]);

            result = this->try_dot(lhs, rhs);
            result = result.reshape(dim1, dim2, rhs.shape.shape()[1]);
            result = result.squeeze(2);
            break;
        case 2:
            //arr3.arr2
            lhs = *this;
            dim1 = lhs.shape.shape()[0];
            dim2 = lhs.shape.shape()[1];

            lhs.reshape(dim1 * dim2, lhs.shape.shape()[2]);

            result = this->try_dot(lhs, rhs);
            result = result.reshape(dim1, dim2, rhs.shape.shape()[1]);
            break;
        case 3:
            //arr3.arr3
            lhs = *this;
            _rhs = rhs;

            dim1 = lhs.shape.shape()[0];
            dim2 = lhs.shape.shape()[1];
            dim3 = rhs.shape.shape()[1];
            dim4 = rhs.shape.shape()[2];

            lhs.reshape(dim1 * dim2, lhs.shape.shape()[2]);
            _rhs.reshape(rhs.shape.shape()[0], dim3 * dim4);

            result = this->try_dot(lhs, _rhs);
            result = result.reshape(dim1, dim2, dim3, dim4);
            break;
        default:
            std::cout<<"Cannot compute dot product between array" <<this->rank<<" and array"<<rhs.rank<<std::endl;
            exit(0);
            break;
    }

    return result;
}
Array Array::try_dot_arr4(Array& rhs){
    Array lhs, _rhs, result;
    int dim1, dim2, dim3, dim4;
    std::vector<Array> arrays, result_arrays;

    switch(rhs.rank){
        case 1:
            //arr4.arr1
            arrays = this->split(0);
            dim1 = this->shape.shape()[1];
            dim2 = this->shape.shape()[2];

            for(int i = 0; i < this->shape.shape()[0]; i++){
                lhs = arrays[i];
                lhs.reshape(dim1 * dim2, arrays[0].get_shape().shape()[2]);

                result = this->try_dot(lhs, rhs);
                result = result.reshape(dim1, dim2, rhs.get_shape().shape()[1]);
                result_arrays.push_back(result);
            }
            result = stack(result_arrays, this->shape.shape()[0], 0);
            result = result.squeeze(3);
            break;
        case 2:
            //arr4.arr2
            arrays = this->split(0);
            dim1 = this->shape.shape()[1];
            dim2 = this->shape.shape()[2];

            for(int i = 0; i < this->shape.shape()[0]; i++){
                lhs = arrays[i];
                lhs.reshape(dim1 * dim2, arrays[0].get_shape().shape()[2]);

                result = this->try_dot(lhs, rhs);
                result = result.reshape(dim1, dim2, rhs.get_shape().shape()[1]);
                result_arrays.push_back(result);
            }
            result = stack(result_arrays, this->shape.shape()[0], 0);
            break;
        default:
            std::cout<<"Cannot compute dot product between array" <<this->rank<<" and array"<<rhs.rank<<std::endl;
            exit(0);
            break;
    }

    return result;
}

Array Array::try_dot(Array& lhs, Array& rhs){
    if (lhs.shape.shape()[1] != rhs.shape.shape()[0]) {
        std::cout << "These arrays are not equal size";
        exit(0);
    }

    int dim_x = lhs.shape.shape()[0];
    int dim_y = rhs.shape.shape()[1];
    int sum_dim = lhs.shape.shape()[1];


    std::vector<float> data(dim_x * dim_y, 0.);


    Array result(dim_x, dim_y);

    for (int k = 0; k < dim_x; k++){
        for(int j = 0; j < dim_y; j++){
            int sum = 0;
            for (int i = 0; i < sum_dim; i++){
                sum += lhs.data[k *  lhs.shape.strides()[0] + i] * rhs.data[j + i * rhs.shape.strides()[0]];
            }
            data[k * dim_y + j] = sum;
        }
    }

    result.fill_vec(data, dim_x * dim_y);

    return result;
}
