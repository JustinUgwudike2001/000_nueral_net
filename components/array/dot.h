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
        // arr1.arr4
        arrays = rhs.split(0);
        dim1 = rhs.shape.shape()[1];
        dim2 = rhs.shape.shape()[3];

        for (int i = 0; i < rhs.shape.shape()[0]; i++)
        {
            _rhs = arrays[i];
            _rhs = _rhs.reshape({arrays[0].shape.shape()[2], dim1 * dim2});

            result = this->try_dot(*this, _rhs);
            result = result.reshape({this->shape.shape()[1], dim1, dim2});
            result_arrays.push_back(result);
        }

        result = stack(result_arrays, 0);
        result = result.squeeze(3);
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
        // arr2.arr4
        arrays = rhs.split(3);
        dim1 = rhs.shape.shape()[1];
        dim2 = rhs.shape.shape()[2];

        for (int i = 0; i < rhs.shape.shape()[3]; i++)
        {
            _rhs = arrays[i];
            _rhs = _rhs.reshape({arrays[0].shape.shape()[0], dim1 * dim2});

            result = this->try_dot(*this, _rhs);
            result = result.reshape({this->shape.shape()[0], dim1, dim2});
            result_arrays.push_back(result);
        }

        result = stack(result_arrays, 3);
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
    Array<D> lhs, _rhs, result, result_arrays;
    int dim1, dim2, dim3, dim4;

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
        // arr3.arr3
        lhs = *this;

        _rhs = rhs.permute({1,0,2});
        dim1 = _rhs.shape.shape()[1];
        dim2 = _rhs.shape.shape()[2];

        for(int i = 0; i < lhs.shape.shape()[0]; i++){

            lhs = lhs.reshape({dim1 * dim2, lhs.shape.shape()[2]});
            _rhs = _rhs.reshape({rhs.shape.shape()[0], dim3 * dim4});

            result_arrays.push_back(this->try_dot(lhs, _rhs));
        }

        result = stack(result_arrays, 0)

        result = result.reshape({rhs, dim2, dim3, dim4});
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
    int dim1, dim2, dim3, dim4;
    std::vector<Array<D>> arrays, arrays1, arrays2, arrays3, result_arrays;

    switch (rhs.rank)
    {
    case 1:
        // arr4.arr1
        arrays = this->split(0);
        dim1 = this->shape.shape()[1];
        dim2 = this->shape.shape()[2];

        for (int i = 0; i < this->shape.shape()[0]; i++)
        {
            lhs = arrays[i];
            lhs = lhs.reshape({dim1 * dim2, arrays[0].get_shape().shape()[2]});

            result = this->try_dot(lhs, rhs);
            result = result.reshape({dim1, dim2, rhs.get_shape().shape()[1]});
            result_arrays.push_back(result);
        }
        result = stack(result_arrays, 0);
        result = result.squeeze(3);
        break;
    case 2:
        // arr4.arr2
        arrays = this->split(0);
        dim1 = this->shape.shape()[1];
        dim2 = this->shape.shape()[2];

        for (int i = 0; i < this->shape.shape()[0]; i++)
        {
            lhs = arrays[i];
            lhs = lhs.reshape({dim1 * dim2, arrays[0].get_shape().shape()[2]});

            result = this->try_dot(lhs, rhs);
            result = result.reshape({dim1, dim2, rhs.get_shape().shape()[1]});
            result_arrays.push_back(result);
        }
        result = stack(result_arrays, 0);
        break;
    case 4:
        // arr4.arr4
        arrays = this->split(0);
        arrays1 = rhs.split(0);
        dim1 = this->shape.shape()[1];
        dim2 = this->shape.shape()[2];
        dim3 = rhs.shape.shape()[1];
        dim4 = rhs.shape.shape()[3];
                std::cout<<"heyho"<<std::endl;

        for (int i = 0; i < this->shape.shape()[0]; i++) {
            arrays2 = arrays[i].split(0);
            arrays3 = arrays1[i].split(0);
            std::vector<Array<D>> result_arrays1;
            for (int j = 0; j < this->shape.shape()[1]; j++) {
                lhs = arrays2[j];
                _rhs = arrays3[j];

                lhs.shape.print();
                _rhs.shape.print();
                std::cout<<"heyho0"<<std::endl;

                result = this->try_dot(lhs, _rhs);
                std::cout<<rhs.get_shape().shape()[3]<<std::endl;

                //result.shape.print();
                std::cout<<"heyho2"<<std::endl;

                result_arrays1.push_back(result);
            }
            result = stack(result_arrays1, 0);
            result_arrays.push_back(result);
        }
        std::cout<<"heyho3"<<std::endl;
        result = stack(result_arrays, 0);
        std::cout<<"heyho4"<<std::endl;

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
