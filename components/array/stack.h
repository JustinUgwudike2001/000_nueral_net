#include "permute.h"

template <typename D>
std::vector<Array<D>> Array<D>::split(int dim)
{
    Shape shape = this->shape;
    std::vector<int> dims = shape.shape();
    dims.erase(dims.begin() + dim);
    int split_size = shape.shape()[dim];
    int elem_size = shape.size() / split_size;

    std::vector<Array> arrays;
    std::vector<D> _data(elem_size, 0.);
    std::vector<std::shared_ptr<Node<D>>> dots(elem_size);

    Array<D> ref = *this;

    switch (this->rank)
    {
    case 2:
        if (dim)
            ref = this->t();
        break;
    case 3:
        if (dim == 1)
            ref = this->permute({1, 0, 2});
        if (dim == 2)
            ref = this->permute({2, 0, 1});
        break;
    case 4:
        if (dim == 1)
            ref = this->permute({1, 0, 2, 3});
        if (dim == 2)
            ref = this->permute({2, 0, 1, 3});
        if (dim == 3)
            ref = this->permute({3, 0, 1, 2});
        break;
    default:
        std::cout << "Invalid rank!" << std::endl;
        exit(0);
        break;
    }

    std::vector<int> strides = ref.get_shape().strides();

    for (int j = 0; j < split_size; j++)
    {
        Array<D> elem_array({elem_size});

        switch (this->rank)
        {
        case 2:
            elem_array = elem_array.reshape({dims[0]});
            break;
        case 3:
            elem_array = elem_array.reshape({dims[0], dims[1]});
            break;
        case 4:
            elem_array = elem_array.reshape({dims[0], dims[1], dims[2]});
            break;
        default:
            std::cout << "NAHHHHHH!" << std::endl;
            exit(0);
            break;
        }

        for (int i = 0; i < elem_size; i++)
        {
            _data[i] = ref.data[strides[0] * j + i];
            dots[i] = ref.nodes[strides[0] * j + i];
        }

        elem_array.fill_grad_vec(_data, dots, elem_size);
        arrays.push_back(elem_array);
    }

    return arrays;
}

template <typename D>
Array<D> stack(std::vector<Array<D>> arrays, int dim)
{
    Shape arr_shape = arrays[0].get_shape();
    int size = arrays.size();
    int array_size = arr_shape.size();
    int total_d_size = size * array_size;
    int num_dim = arr_shape.dims();
    std::vector<int> shape = arr_shape.shape();

    shape.insert(shape.begin(), size);
    Shape new_shape(shape, shape.size());
    Array<D> stacked_array(new_shape);

    std::vector<int> strides = stacked_array.get_shape().strides();

    std::vector<D> stacked_data(total_d_size);
    std::vector<std::shared_ptr<Node<D>>> stacked_dots(total_d_size);

    for (int j = 0; j < size; j++)
    {
        std::vector<D> data = arrays[j].get_data();
        std::vector<std::shared_ptr<Node<D>>> nodes = arrays[j].get_grad();
        for (int i = 0; i < array_size; i++)
        {
            stacked_data[strides[0] * j + i] = data[i];
            stacked_dots[strides[0] * j + i] = nodes[i];
        }
    }

    stacked_array.fill_grad_vec(stacked_data, stacked_dots, total_d_size);

    switch (num_dim + 1)
    {
    case 2:
        if (dim)
            stacked_array = stacked_array.t();
        break;
    case 3:
        if (dim == 1)
            stacked_array = stacked_array.permute({1, 0, 2});
        if (dim == 2)
            stacked_array = stacked_array.permute({1, 2, 0});
        break;
    case 4:
        if (dim == 1)
            stacked_array = stacked_array.permute({1, 0, 2, 3});
        if (dim == 2)
            stacked_array = stacked_array.permute({1, 2, 0, 3});
        if (dim == 3)
            stacked_array = stacked_array.permute({1, 2, 3, 0});
        break;
    default:
        std::cout << "NAHHHHHH!" << std::endl;
        exit(0);
        break;
    }
    return stacked_array;
}

int test_stack()
{

    std::cout << std::endl
              << "ARRAY3::::::::::: " << std::endl;
    Array<float> array3({2, 2, 3});
    array3.lin();
    array3.print();
    // array3.print_grad();

    std::cout << std::endl
              << "SPLIT: DIM 0::::::::::" << std::endl;
    std::vector<Array<float>> arrays = array3.split(0);
    for (int i = 0; i < 2; i++)
    {
        arrays[i].print();
        // arrays[i].print_grad();
    }

    std::cout << std::endl
              << "SPLIT: DIM 1::::::::::" << std::endl;
    arrays = array3.split(1);
    for (int i = 0; i < 2; i++)
    {
        arrays[i].print();
        // arrays[i].print_grad();
    }

    std::cout << std::endl
              << "SPLIT: DIM 2::::::::::" << std::endl;
    arrays = array3.split(2);
    for (int i = 0; i < 3; i++)
    {
        arrays[i].print();
        // arrays[i].print_grad();
    }

    std::cout << std::endl
              << "Arrays to be stacked:::" << std::endl;
    arrays = array3.split(0);
    for (int i = 0; i < 2; i++)
    {
        arrays[i].print();
        // arrays[i].print_grad();
    }

    std::cout << std::endl
              << "STACK: DIM 0::::::::::" << std::endl;
    Array<float> array3_1 = stack(arrays, 0);
    array3_1.print();

    std::cout << std::endl
              << "STACK: DIM 1::::::::::" << std::endl;
    array3_1 = stack(arrays, 1);
    array3_1.print();

    std::cout << std::endl
              << "STACK: DIM 2::::::::::" << std::endl;
    array3_1 = stack(arrays, 2);
    array3_1.print();

    return 0;
}