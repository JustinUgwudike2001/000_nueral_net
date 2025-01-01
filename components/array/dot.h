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
        // arr1.arr1
        result = this->try_dot(*this, rhs);
        break;
    case 2:
        // arr1.arr2
        result = this->try_dot(*this, rhs);
        break;
    case 3:
        // arr1.arr3
        printf("here1\n");
        dim1 = rhs.shape.shape()[1];
        dim2 = rhs.shape.shape()[2];
        printf("here2\n");
        _rhs = rhs;
        printf("here3\n");
        _rhs.reshape({rhs.shape.shape()[0], dim1 * dim2});
        printf("here5\n");
        result = this->try_dot(*this, _rhs);
        printf("here5\n");
        result = result.reshape({this->get_shape().shape()[0], dim1, dim2});
        printf("here6\n");
        result = result.squeeze(0);
        printf("here7\n");
        break;
    case 4:
        // arr1.arr4
        arrays = rhs.split(3);
        dim1 = rhs.shape.shape()[1];
        dim2 = rhs.shape.shape()[2];

        for (int i = 0; i < rhs.shape.shape()[3]; i++)
        {
            _rhs = arrays[i];
            _rhs.reshape({arrays[0].shape.shape()[0], dim1 * dim2});

            result = this->try_dot(*this, _rhs);
            result = result.reshape({this->shape.shape()[0], dim1, dim2});
            result_arrays.push_back(result);
        }

        result = stack(result_arrays, 3);
        result = result.squeeze(0);
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
        // arr2.arr1
        result = this->try_dot(*this, rhs);
        break;
    case 2:
        // arr2.arr2
        result = this->try_dot(*this, rhs);
        break;
    case 3:
        // arr2.arr3
        dim1 = rhs.shape.shape()[1];
        dim2 = rhs.shape.shape()[2];

        _rhs = rhs;
        _rhs.reshape({rhs.shape.shape()[0], dim1 * dim2});
        result = this->try_dot(*this, _rhs);
        result = result.reshape({this->get_shape().shape()[0], dim1, dim2});
        break;
    case 4:
        // arr2.arr4
        arrays = rhs.split(3);
        dim1 = rhs.shape.shape()[1];
        dim2 = rhs.shape.shape()[2];

        for (int i = 0; i < rhs.shape.shape()[3]; i++)
        {
            _rhs = arrays[i];
            _rhs.reshape({arrays[0].shape.shape()[0], dim1 * dim2});

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
    Array<D> lhs, _rhs, result;
    int dim1, dim2, dim3, dim4;

    switch (rhs.rank)
    {
    case 1:
        // arr3.arr1
        lhs = *this;
        dim1 = lhs.shape.shape()[0];
        dim2 = lhs.shape.shape()[1];

        lhs.reshape({dim1 * dim2, lhs.shape.shape()[2]});

        result = this->try_dot(lhs, rhs);
        result = result.reshape({dim1, dim2, rhs.shape.shape()[1]});
        result = result.squeeze(2);
        break;
    case 2:
        // arr3.arr2
        lhs = *this;
        dim1 = lhs.shape.shape()[0];
        dim2 = lhs.shape.shape()[1];

        lhs.reshape({dim1 * dim2, lhs.shape.shape()[2]});

        result = this->try_dot(lhs, rhs);
        result = result.reshape({dim1, dim2, rhs.shape.shape()[1]});
        break;
    case 3:
        // arr3.arr3
        lhs = *this;
        _rhs = rhs;

        dim1 = lhs.shape.shape()[0];
        dim2 = lhs.shape.shape()[1];
        dim3 = rhs.shape.shape()[1];
        dim4 = rhs.shape.shape()[2];

        lhs.reshape({dim1 * dim2, lhs.shape.shape()[2]});
        _rhs.reshape({rhs.shape.shape()[0], dim3 * dim4});

        result = this->try_dot(lhs, _rhs);
        result = result.reshape({dim1, dim2, dim3, dim4});
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
    std::vector<Array<D>> arrays, result_arrays;

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
            lhs.reshape({dim1 * dim2, arrays[0].get_shape().shape()[2]});

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
            lhs.reshape({dim1 * dim2, arrays[0].get_shape().shape()[2]});

            result = this->try_dot(lhs, rhs);
            result = result.reshape({dim1, dim2, rhs.get_shape().shape()[1]});
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
        std::cout << "These arrays are not equal size";
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
        }
    }

    result.fill_vec(data, dim_x * dim_y);

    return result;
}

int test_dot()
{

    std::cout << "ARRAY1::::::::::: " << std::endl;
    Array<float> array1({5});
    array1.set_name("arr1");
    array1.lin();
    array1.print();

    Array<float> array1_1({5});
    array1_1.set_name("arr2");
    array1_1 = array1.t();
    array1_1.print();

    Array<float> result;
    result.set_name("result");

    // arr1.(arr1.t())
    std::cout << "arr1.arr2" << std::endl;
    result = array1.dot(array1_1);
    result.print();
    std::cout << std::endl;

    // arr1.t().arr1
    std::cout << "arr2.arr1" << std::endl;
    result = array1_1.dot(array1);
    result.print();
    std::cout << std::endl;

    std::cout << "ARRAY2::::::::::: " << std::endl;
    Array<float> array2({2, 5});
    array2.set_name("arr3");
    array2.lin();
    array2.print();

    Array<float> array2_1({5, 2});
    array2_1.set_name("arr4");
    array2_1.lin();
    array2_1.print();

    // arr2.(arr2.t())
    std::cout << "arr3.arr4" << std::endl;
    result = array2.dot(array2_1);
    result.print();
    std::cout << std::endl;

    // arr2.t().arr2
    std::cout << "arr4.arr3" << std::endl;
    result = array2_1.dot(array2);
    result.print();
    std::cout << std::endl;

    // arr1.(arr2.t())
    std::cout << "arr1.arr4" << std::endl;
    result = array1.dot(array2_1);
    result.print();
    std::cout << std::endl;

    // arr2.(arr1.t())
    std::cout << "arr3.arr2" << std::endl;
    result = array2.dot(array1_1);
    result.print();
    std::cout << std::endl;
    std::cout << "ARRAY3::::::::::: " << std::endl;

    Array<float> array3({5, 2, 3});
    array3.set_name("arr5");
    array3.lin();
    array3.print();

    Array<float> array3_1({3, 2, 5});
    array3_1.set_name("arr6");
    array3_1.lin();
    array3_1.print();

    // arr1.arr3
    std::cout << "arr1.arr5" << std::endl;
    result = array1.dot(array3);
    result.print();
    std::cout << std::endl;

    // arr3.permute().(arr1.t())
    std::cout << "arr5.arr2" << std::endl;
    array3 = array3.permute({2, 1, 0});
    result = array3.dot(array1_1);
    result.print();
    std::cout << std::endl;

    // arr3.permute().(arr2.t())
    std::cout << "arr5.arr4" << std::endl;
    result = array3.dot(array2_1);
    result.print();
    std::cout << std::endl;

    // arr3.t().(arr2)
    std::cout << "arr5.arr4" << std::endl;
    array3 = array3.permute({2, 1, 0});
    array3 = array3.t();
    // array3.print();
    result = array3.dot(array2);
    result.print();
    std::cout << std::endl;

    array3 = array3.t();

    // arr3.(arr3.t())
    std::cout << "arr5.arr4" << std::endl;
    result = array3.dot(array3_1);
    result.print();
    std::cout << std::endl;

    // arr3.t().arr3
    std::cout << "arr5.arr4" << std::endl;
    result = array3_1.dot(array3);
    result.print();
    std::cout << std::endl;

    std::cout << "ARRAY4::::::::::: " << std::endl;

    Array<float> array4({5, 4, 3, 2});
    array4.set_name("arr7");
    array4.lin();
    array4.print();

    Array<float> array4_1({2, 3, 4, 5});
    array4_1.set_name("arr8");
    array4_1.lin();
    array4_1.print();

    // arr1.t().arr4
    std::cout << "arr2.arr7" << std::endl;
    result = array1.dot(array4);
    result.print();
    std::cout << std::endl;

    // arr4.t().(arr1)
    std::cout << "arr8.arr1" << std::endl;
    result = array4_1.dot(array1_1);
    result.print();
    std::cout << std::endl;

    // arr2.(arr4)
    std::cout << "arr3.arr7" << std::endl;
    result = array2.dot(array4);
    result.print();
    std::cout << std::endl;

    // arr4.t().(arr2.t())
    std::cout << "arr8.arr4" << std::endl;
    result = array4_1.dot(array2_1);
    result.print();
    std::cout << std::endl;

    // arr4.t().(arr3.t())
    std::cout << "arr8.arr5" << std::endl;
    result = array4_1.dot(array3_1);
    result.print();
    std::cout << std::endl;

    return 0;
}