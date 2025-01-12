#include "fill_functions.h"

template <typename D>
Array<D> Array<D>::sum()
{
    Array<D> sum_arr({1});
    sum_arr.zeros();
    for(int i = 0; i < this->shape.size(); i++){
        sum_arr.data[0] += this->data[i];
    }

    // Create a node for the sum
    std::shared_ptr<Node<D>> sumNode = std::make_shared<Node<D>>(sum_arr.data[0]);

    // Define backward function
    sumNode->backward = [nodes = nodes, sumNode]() {
        for (const auto& node : nodes) {
            node->gradient += 1.0 * sumNode->gradient; // ∂(sum)/∂a[i] = 1
        }
    };

    sum_arr.nodes[0] = sumNode;
    return sum_arr;
}

int test_sum(){

    Array<float> arr1({10});
    arr1.random();
    arr1.print();
    arr1 = arr1.sum();
    arr1.print();

    Array<int> arr2({10});
    arr2.lin();
    arr2.print();
    arr2 = arr2.sum();
    arr2.print();

    return 0;
}