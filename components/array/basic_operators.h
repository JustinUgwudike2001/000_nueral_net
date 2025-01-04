#include "fill_array.h"

template <typename D>
inline Array<D> Array<D>::operator=(const Array &arr2)
{

    if (this == &arr2)
        return *this;

    this->data = arr2.data;
    this->shape = arr2.shape;
    this->rank = arr2.rank;
    this->nodes = arr2.nodes;
    //this->tape = arr2.tape;
    // strcpy(arr2.name, this->name);

    return *this;
}

// template <typename D>
// template <typename U>
// inline Array<D>& Array<D>::operator=(Array<U>& arr2){
//     // Clear current data and resize
//     data.clear();
//     data.resize(arr2.get_shape().size());

//     this->shape = arr2.get_shape();
//     this->rank = arr2.get_shape().dims();

//     std::vector<U> new_data = arr2.get_data();
//     std::vector<float> new_dots = arr2.get_grad();

//     for(int i = 0; i < arr2.get_shape().size(); i++){
//         data[i] = new_data[i];
//         dots[i] = new_dots[i];
//     }

//     return *this;
// }

template <typename D>
Array<D> Array<D>::operator+(D rhs)
{
    Array<D> arr = Array<D>(this->shape);
    std::vector<std::shared_ptr<Node<D>>> resultNodes;

    for (int i = 0; i < this->shape.size(); i++)
    {
        arr.data[i] = this->data[i] + rhs;

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(arr.data[i]);
        newNode->addInput(nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], newNode]() {
            node1->gradient += 1.0 * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.nodes = resultNodes;
    return arr;
}
template <typename D>
Array<D> Array<D>::operator-(D rhs)
{
    Array<D> arr = Array<D>(this->shape);
    std::vector<std::shared_ptr<Node<D>>> resultNodes;

    for (int i = 0; i < this->shape.size(); i++)
    {
        arr.data[i] = this->data[i] - rhs;

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(arr.data[i]);
        newNode->addInput(nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], newNode]() {
            node1->gradient += 1.0 * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.nodes = resultNodes;
    return arr;
}
template <typename D>
Array<D> Array<D>::operator/(D rhs)
{
    Array<D> arr = Array<D>(this->shape);
    std::vector<std::shared_ptr<Node<D>>> resultNodes;

    for (int i = 0; i < this->shape.size(); i++)
    {
        arr.data[i] = this->data[i] / rhs;

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(arr.data[i]);
        newNode->addInput(nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], rhs, newNode]() {
            node1->gradient += (1.0 / rhs) * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.nodes = resultNodes;
    return arr;
}
template <typename D>
Array<D> Array<D>::operator*(D rhs)
{
    Array<D> arr = Array<D>(this->shape);
    std::vector<std::shared_ptr<Node<D>>> resultNodes;

    for (int i = 0; i < this->shape.size(); i++)
    {
        arr.data[i] = this->data[i] * rhs;

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(arr.data[i]);
        newNode->addInput(nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], rhs, newNode]() {
            node1->gradient += rhs * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.nodes = resultNodes;
    return arr;
}
template <typename D>
Array<D> Array<D>::operator^(D rhs)
{
    Array<D> arr = Array<D>(this->shape);
    std::vector<std::shared_ptr<Node<D>>> resultNodes;

    for (int i = 0; i < this->shape.size(); i++)
    {
        arr.data[i] = std::pow(this->data[i], rhs);
        
        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(arr.data[i]);
        newNode->addInput(nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], rhs, newNode]() {
            node1->gradient += rhs * std::pow(node1->value, rhs - 1) * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.nodes = resultNodes;
    return arr;
}

template <typename D>
Array<D> Array<D>::operator+(Array &rhs)
{

    if (this->shape.size() != rhs.shape.size())
    {
        std::cout << "These arrays are not equal size";
        exit(0);
    }

    Array<D> arr = Array<D>(this->shape);
    std::vector<std::shared_ptr<Node<D>>> resultNodes;

    for (int i = 0; i < this->shape.size(); i++)
    {
        arr.data[i] = this->data[i] + rhs.data[i];

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(arr.data[i]);
        newNode->addInput(nodes[i]);
        newNode->addInput(rhs.nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], node2 = rhs.nodes[i], newNode]() {
            node1->gradient += 1.0 * newNode->gradient;
            node2->gradient += 1.0 * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.nodes = resultNodes;
    return arr;
}
template <typename D>
Array<D> Array<D>::operator-(Array &rhs)
{

    if (this->shape.size() != rhs.shape.size())
    {
        std::cout << "These arrays are not equal size";
        exit(0);
    }

    Array<D> arr = Array<D>(this->shape);
    std::vector<std::shared_ptr<Node<D>>> resultNodes;

    for (int i = 0; i < this->shape.size(); i++)
    {
        arr.data[i] = this->data[i] - rhs.data[i];

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(arr.data[i]);
        newNode->addInput(nodes[i]);
        newNode->addInput(rhs.nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], node2 = rhs.nodes[i], newNode]() {
            node1->gradient += 1.0 * newNode->gradient;
            node2->gradient -= 1.0 * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.nodes = resultNodes;
    return arr;
}
template <typename D>
Array<D> Array<D>::operator/(Array &rhs)
{

    if (this->shape.size() != rhs.shape.size())
    {
        std::cout << "These arrays are not equal size";
        exit(0);
    }

    Array<D> arr = Array<D>(this->shape);
    std::vector<std::shared_ptr<Node<D>>> resultNodes;

    for (int i = 0; i < this->shape.size(); i++)
    {
        arr.data[i] = this->data[i] / rhs.data[i];

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(arr.data[i]);
        newNode->addInput(nodes[i]);
        newNode->addInput(rhs.nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], node2 = rhs.nodes[i], newNode]() {
            node1->gradient += (1.0 / node2->value) * newNode->gradient;  
            node2->gradient -= (node1->value / (node2->value * node2->value)) * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.nodes = resultNodes;
    return arr;
}
template <typename D>
Array<D> Array<D>::operator*(Array &rhs)
{

    if (this->shape.size() != rhs.shape.size())
    {
        std::cout << "These arrays are not equal size";
        exit(0);
    }

    Array<D> arr = Array<D>(this->shape);
    std::vector<std::shared_ptr<Node<D>>> resultNodes;

    for (int i = 0; i < this->shape.size(); i++)
    {
        arr.data[i] = this->data[i] * rhs.data[i];

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(arr.data[i]);
        newNode->addInput(nodes[i]);
        newNode->addInput(rhs.nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], node2 = rhs.nodes[i], newNode]() {
            node1->gradient += node2->value * newNode->gradient;
            node2->gradient += node1->value * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.nodes = resultNodes;
    return arr;
}
template <typename D>
Array<D> Array<D>::operator^(Array<D> &rhs)
{
    Array<D> arr = Array<D>(this->shape);
    std::vector<std::shared_ptr<Node<D>>> resultNodes;

    for (int i = 0; i < this->shape.size(); i++)
    {
        arr.data[i] = std::pow(this->data[i], rhs.data[i]);
        
        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(arr.data[i]);
        newNode->addInput(nodes[i]);
        newNode->addInput(rhs.nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], node2 = rhs.nodes[i], newNode]() {
            node1->gradient += (node2->value * std::pow(node1->value, node2->value - 1)) * newNode->gradient; // ∂(a^b)/∂a
            node2->gradient += (std::log(node1->value) * newNode->value) * newNode->gradient; // ∂(a^b)/∂b
        };

        resultNodes.push_back(newNode);
    }

    arr.nodes = resultNodes;
    return arr;
}

int test_basic_operators()
{

    Array<float> array1({16});
    array1.lin();
    array1.print();
    Array<float> array1_1({16});
    array1_1.ones();
    array1_1.set_name("array1_1");
    array1_1.print();

    array1 = array1 + array1_1;

    std::cout << "array1 + array1_1: " << std::endl;
    array1.print();

    std::cout << "array1 + 5: " << std::endl;
    array1_1 = array1 + 5;
    array1_1.print();

    std::cout << "array1 - 5: " << std::endl;
    array1_1 = array1 - 5;
    array1_1.print();

    std::cout << "array1 * 5: " << std::endl;
    array1_1 = array1 * 5;
    array1_1.print();

    std::cout << "array1 / 5: " << std::endl;
    array1_1 = array1 / 5;
    array1_1.print();

    std::cout << "array1 ^ 3: " << std::endl;
    array1_1 = array1 ^ 3;
    array1_1.print();

    std::cout << std::endl;

    Array<float> array2({4, 4});
    array2.zeros();
    array2.print();

    std::cout << "array2 * array1: " << std::endl;
    array2 = array2 + array1;
    array2.print();

    std::cout << "array2 / array1: " << std::endl;
    array2 = array2 / array1;
    array2.print();

    std::cout << "array2 * array1: " << std::endl;
    array2 = array2 * array1;
    array2.print();
    std::cout << std::endl;

    Array<float> array4({2, 2, 2, 2});
    array4.ones();
    array4.print();

    std::cout << "array4 - array1: " << std::endl;
    array4 = array4 - array1;
    array4.print();

    // Array<int> ints({10});
    // ints.lin();
    // ints.print();
    // Array<float> floats({10});
    // floats = ints;
    // floats.print();

    return 0;
}