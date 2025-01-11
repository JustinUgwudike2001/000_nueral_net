#include "squeeze.h"

template <typename D>
Array<D> Array<D>::dot(Array<D> &rhs)
{
    Array<D> arr;

    switch (this->rank)
    {
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
        std::cout << "Cannot compute dot product between array" << this->rank << " and array" << rhs.rank << std::endl;
        exit(0);
        break;
    }

    return arr;
}

template <typename D>
Array<D> Array<D>::try_dot_arr1(Array<D> &rhs)
{
    Array<D> lhs, _rhs, result;
    int dim1, dim2;
    std::vector<Array<D>> arrays, result_arrays;

    switch (rhs.rank)
    {
    case 1:
        // arr1.arr1 OK
        result = this->try_dot(*this, rhs);
        break;
    case 2:
        // arr1.arr2 OK
        result = this->try_dot(*this, rhs);
        break;
    case 3:
        // arr1.arr3 OK
        _rhs = rhs.permute({1,0,2});
        dim1 = _rhs.shape.shape()[1];
        dim2 = _rhs.shape.shape()[2];

        _rhs = _rhs.reshape({_rhs.shape.shape()[0], dim1 * dim2});

        result = this->try_dot(*this, _rhs);
        result = result.reshape({this->get_shape().shape()[0], dim1, dim2});
        result = result.permute({1,0,2});

        break;
    case 4:
        // arr1.arr4 OK
        _rhs = rhs.permute({0, 2, 1, 3});
        arrays = _rhs.split(0);
        dim1 = _rhs.shape.shape()[2];
        dim2 = _rhs.shape.shape()[3];

        for (int i = 0; i < rhs.shape.shape()[0]; i++)
        {
            _rhs = arrays[i];
            _rhs = _rhs.reshape({arrays[0].shape.shape()[0], dim1 * dim2});

            result = this->try_dot(*this, _rhs);
            result = result.reshape({this->shape.shape()[0], dim1, dim2});
            result_arrays.push_back(result.permute({1,0,2}));
        }

        result = stack(result_arrays, 0);
        break;
    default:
        std::cout << "Cannot compute dot product between array" << this->rank << " and array" << rhs.rank << std::endl;
        exit(0);
        break;
    }

    return result;
}
template <typename D>
Array<D> Array<D>::try_dot_arr2(Array<D> &rhs)
{
    Array<D> lhs, _rhs, result;
    int dim1, dim2;
    std::vector<Array<D>> arrays, result_arrays;

    switch (rhs.rank)
    {
    case 1:
        // arr2.arr1 OK
        result = this->try_dot(*this, rhs);
        break;
    case 2:
        // arr2.arr2 OK
        result = this->try_dot(*this, rhs);
        break;
    case 3:
        // arr2.arr3 OK
        _rhs = rhs.permute({1,0,2});
        dim1 = _rhs.shape.shape()[1];
        dim2 = _rhs.shape.shape()[2];

        _rhs = _rhs.reshape({_rhs.shape.shape()[0], dim1 * dim2});

        result = this->try_dot(*this, _rhs);
        result = result.reshape({this->get_shape().shape()[0], dim1, dim2});
        result = result.permute({1,0,2});
        break;
    case 4:
        // arr2.arr4 OK
        _rhs = rhs.permute({0, 2, 1, 3});
        arrays = _rhs.split(0);
        dim1 = _rhs.shape.shape()[2];
        dim2 = _rhs.shape.shape()[3];

        for (int i = 0; i < rhs.shape.shape()[0]; i++)
        {
            _rhs = arrays[i];
            _rhs = _rhs.reshape({arrays[0].shape.shape()[0], dim1 * dim2});

            result = this->try_dot(*this, _rhs);
            result = result.reshape({this->shape.shape()[0], dim1, dim2});
            result_arrays.push_back(result.permute({1,0,2}));
        }

        result = stack(result_arrays, 0);
        break;
    default:
        std::cout << "Cannot compute dot product between array" << this->rank << " and array" << rhs.rank << std::endl;
        exit(0);
        break;
    }

    return result;
}
template <typename D>
Array<D> Array<D>::try_dot_arr3(Array<D> &rhs)
{
    Array<D> lhs, _rhs, result;
    int dim1, dim2, length, length1, lhs_incr = 1, rhs_incr = 1;
    std::vector<Array<D>> lhs_arrays, lhs_arrays1, rhs_arrays, rhs_arrays1, result_arrays;

    switch (rhs.rank)
    {
    case 1:
        // arr3.arr1 OK
        lhs = *this;
        dim1 = lhs.shape.shape()[0];
        dim2 = lhs.shape.shape()[1];

        lhs = lhs.reshape({dim1 * dim2, lhs.shape.shape()[2]});

        result = this->try_dot(lhs, rhs);
        result = result.reshape({dim1, dim2, rhs.shape.shape()[1]});
        break;
    case 2:
        // arr3.arr2 OK
        lhs = *this;
        dim1 = lhs.shape.shape()[0];
        dim2 = lhs.shape.shape()[1];

        lhs = lhs.reshape({dim1 * dim2, lhs.shape.shape()[2]});

        result = this->try_dot(lhs, rhs);
        result = result.reshape({dim1, dim2, rhs.shape.shape()[1]});
        break;
    case 3:
        // arr3.arr3 OK

        lhs = *this;

        if(rhs.shape.shape()[0] > lhs.shape.shape()[0]){
            if(rhs.shape.shape()[0] % lhs.shape.shape()[0] != 0){
                std::cout << "Cannot compute dot product between arrays with these shapes";
                exit(0);
            }
            else{
                length = rhs.shape.shape()[0];
                rhs_incr = length;
                lhs_incr = lhs.shape.shape()[0];
            }
        }else{
            if(lhs.shape.shape()[0] % rhs.shape.shape()[0] != 0){
                std::cout << "Cannot compute dot product between arrays with these shapes";
                exit(0);
            }
            else{
                length = lhs.shape.shape()[0];
                lhs_incr = length;
                rhs_incr = rhs.shape.shape()[0];
            }
        }

        lhs_arrays = lhs.split(0);
        rhs_arrays = rhs.split(0);

        for(int i = 0; i < length; i++){

            lhs = lhs_arrays[i % lhs_incr];
            _rhs = rhs_arrays[i % rhs_incr];

            result = this->try_dot(lhs, _rhs);
            result_arrays.push_back(result);
        }

        result = stack(result_arrays, 0);
        break;
    case 4:
        // arr3.arr4 

        lhs = *this;

        if(rhs.shape.shape()[1] > lhs.shape.shape()[0]){
            if(rhs.shape.shape()[1] % lhs.shape.shape()[0] != 0){
                std::cout << "Cannot compute dot product between arrays with these shapes";
                exit(0);
            }
            else{
                length = rhs.shape.shape()[1];
                rhs_incr = length;
                lhs_incr = lhs.shape.shape()[0];
            }
        }else{
            if(lhs.shape.shape()[0] % rhs.shape.shape()[1] != 0){
                std::cout << "Cannot compute dot product between arrays with these shapes";
                exit(0);
            }
            else{
                length = lhs.shape.shape()[0];
                lhs_incr = length;
                rhs_incr = rhs.shape.shape()[1];
            }
        }

        lhs_arrays = lhs.split(0);
        rhs_arrays = rhs.split(0);
        length1 = rhs.shape.shape()[0];

        for(int i = 0; i < length1; i++){

            rhs_arrays1 = rhs_arrays[i].split(0);
            std::vector<Array<D>> result_arrays1;

            for(int j = 0; j < length; j++){

                lhs = lhs_arrays[j % lhs_incr];
                _rhs = rhs_arrays1[j % rhs_incr];

                result = this->try_dot(lhs, _rhs);
                result_arrays1.push_back(result);
            }
            result = stack(result_arrays1, 0);
            result_arrays.push_back(result);
        }

        result = stack(result_arrays, 0);
        break;
    default:
        std::cout << "Cannot compute dot product between array" << this->rank << " and array" << rhs.rank << std::endl;
        exit(0);
        break;
    }

    return result;
}
template <typename D>
Array<D> Array<D>::try_dot_arr4(Array<D> &rhs)
{
    Array<D> lhs, _rhs, result;
    int dim1, dim2, length, length1, lhs_incr = 1, rhs_incr = 1, lhs_incr1 = 1, rhs_incr1 = 1;
    std::vector<Array<D>> lhs_arrays, lhs_arrays1, rhs_arrays, rhs_arrays1, result_arrays;

    switch (rhs.rank)
    {
    case 1:
        // arr4.arr1 OK
        lhs_arrays = this->split(0);
        dim1 = this->shape.shape()[1];
        dim2 = this->shape.shape()[2];

        for (int i = 0; i < this->shape.shape()[0]; i++)
        {
            lhs = lhs_arrays[i];
            lhs = lhs.reshape({dim1 * dim2, lhs_arrays[0].shape.shape()[2]});

            result = this->try_dot(lhs, rhs);
            result = result.reshape({dim1, dim2, rhs.shape.shape()[1]});
            result_arrays.push_back(result);
        }
        result = stack(result_arrays, 0);
        break;
    case 2:
        // arr4.arr2 OK
        lhs_arrays = this->split(0);
        dim1 = this->shape.shape()[1];
        dim2 = this->shape.shape()[2];

        for (int i = 0; i < this->shape.shape()[0]; i++)
        {
            lhs = lhs_arrays[i];
            lhs = lhs.reshape({dim1 * dim2, lhs_arrays[0].shape.shape()[2]});

            result = this->try_dot(lhs, rhs);
            result = result.reshape({dim1, dim2, rhs.shape.shape()[1]});
            result_arrays.push_back(result);
        }
        result = stack(result_arrays, 0);
        break;
    case 3:
        // arr4.arr3 OK
        lhs = *this;

        if(rhs.shape.shape()[0] > lhs.shape.shape()[1]){
            if(rhs.shape.shape()[0] % lhs.shape.shape()[1] != 0){
                std::cout << "Cannot compute dot product between arrays with these shapes";
                exit(0);
            }
            else{
                length = rhs.shape.shape()[0];
                rhs_incr = length;
                lhs_incr = lhs.shape.shape()[1];
            }
        }else{
            if(lhs.shape.shape()[1] % rhs.shape.shape()[0] != 0){
                std::cout << "Cannot compute dot product between arrays with these shapes";
                exit(0);
            }
            else{
                length = lhs.shape.shape()[1];
                lhs_incr = length;
                rhs_incr = rhs.shape.shape()[0];
            }
        }

        lhs_arrays = lhs.split(0);
        rhs_arrays = rhs.split(0);

        for(int i = 0; i< this->shape.shape()[0]; i++){

            lhs_arrays1 = lhs_arrays[i].split(0);
            std::vector<Array<D>> result_arrays1;

            for(int j = 0; j < length; j++){

                lhs = lhs_arrays1[j % lhs_incr];
                _rhs = rhs_arrays[j % rhs_incr];

                result = this->try_dot(lhs, _rhs);
                result_arrays1.push_back(result);
            }
            result = stack(result_arrays1, 0);
            result_arrays.push_back(result);
        }

        result = stack(result_arrays, 0);
        break;
    case 4:
        // arr4.arr4
        lhs = *this;

        lhs_incr = lhs.shape.shape()[0];
        rhs_incr = rhs.shape.shape()[0];
        rhs_incr1 = rhs.shape.shape()[1];
        lhs_incr1 = lhs.shape.shape()[1];

        if(rhs.shape.shape()[0] > lhs.shape.shape()[0]){
            if(rhs.shape.shape()[0] % lhs.shape.shape()[0] != 0){
                std::cout << "Cannot compute dot product between arrays with these shapes";
                exit(0);
            }
            else{
                length = rhs.shape.shape()[0];
            }
        }else{
            if(lhs.shape.shape()[0] % rhs.shape.shape()[0] != 0){
                std::cout << "Cannot compute dot product between arrays with these shapes";
                exit(0);
            }
            else{
                length = lhs.shape.shape()[0];
            }
        }

        if(rhs.shape.shape()[1] > lhs.shape.shape()[1]){
            if(rhs.shape.shape()[1] % lhs.shape.shape()[1] != 0){
                std::cout << "Cannot compute dot product between arrays with these shapes";
                exit(0);
            }
            else{
                length1 = rhs.shape.shape()[1];
            }
        }else{
            if(lhs.shape.shape()[1] % rhs.shape.shape()[1] != 0){
                std::cout << "Cannot compute dot product between arrays with these shapes";
                exit(0);
            }
            else{
                length1 = lhs.shape.shape()[1];
            }
        }

        lhs_arrays = lhs.split(0);
        rhs_arrays = rhs.split(0);

        for(int i = 0; i< length; i++){

            lhs_arrays1 = lhs_arrays[i % lhs_incr].split(0);
            rhs_arrays1 = rhs_arrays[i % rhs_incr].split(0);
            std::vector<Array<D>> result_arrays1;

            for(int j = 0; j < length1; j++){

                lhs = lhs_arrays1[j % lhs_incr1];
                _rhs = rhs_arrays1[j % rhs_incr1];

                result = this->try_dot(lhs, _rhs);
                result_arrays1.push_back(result);
            }
            result = stack(result_arrays1, 0);
            result_arrays.push_back(result);
        }

        result = stack(result_arrays, 0);
        break;
    default:
        std::cout << "Cannot compute dot product between array" << this->rank << " and array" << rhs.rank << std::endl;
        exit(0);
        break;
    }

    return result;
}

template <typename D>
Array<D> Array<D>::try_dot(Array<D> &lhs, Array<D> &rhs)
{
    if (lhs.shape.shape()[1] != rhs.shape.shape()[0])
    {
        std::cout << "(try_dot): These arrays are not equal size";
        exit(0);
    }

    int dim_x = lhs.shape.shape()[0];
    int dim_y = rhs.shape.shape()[1];
    int sum_dim = lhs.shape.shape()[1];

    std::vector<D> data(dim_x * dim_y);
    Array<D> result({dim_x, dim_y});
    std::vector<std::shared_ptr<Node<D>>> resultNodes;


    for (int k = 0; k < dim_x; k++)
    {
        for (int j = 0; j < dim_y; j++)
        {
            D sum = 0;
            for (int i = 0; i < sum_dim; i++)
            {
                sum += lhs.data[k * lhs.shape.strides()[0] + i] * rhs.data[j + i * rhs.shape.strides()[0]];
            }
            data[k * dim_y + j] = sum;
       
            // Create a node for the dot product element
            std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(sum);

            // Add dependencies for gradient propagation
            for (int i = 0; i < sum_dim; ++i) {
                newNode->addInput(lhs.nodes[k * lhs.shape.strides()[0] + i]);
                newNode->addInput(rhs.nodes[i * rhs.shape.strides()[0] + j]);
            }

            // Define backward function
            newNode->backward = [newNode, lhsNodes = lhs.nodes, rhsNodes = rhs.nodes, k, j, sum_dim, lhsStride = lhs.shape.strides()[0], rhsStride = rhs.shape.strides()[0]]() {
                for (int i = 0; i < sum_dim; ++i) {
                    // Gradient for LHS
                    lhsNodes[k * lhsStride + i]->gradient += rhsNodes[i * rhsStride + j]->value * newNode->gradient;
                    // Gradient for RHS
                    rhsNodes[i * rhsStride + j]->gradient += lhsNodes[k * lhsStride + i]->value * newNode->gradient;
                }
            };

            resultNodes.push_back(newNode);
        }
    }

    result.fill_vec(data, dim_x * dim_y);
    result.nodes = resultNodes;

    return result;
}
