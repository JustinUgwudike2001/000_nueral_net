#include "sum.h"

template <typename D>
Array<D> Array<D>::mean()
{
    Array<D> mean_arr({1});
    mean_arr.zeros();
    for(int i = 0; i < this->shape.size(); i++){
        mean_arr.data[0] += this->data[i];
    }

    int n = this->shape.size();

    mean_arr.data[0] /= n;

    // Create a node for the sum
    std::shared_ptr<Node<D>> sumNode = std::make_shared<Node<D>>(mean_arr.data[0]);

    // Define backward function
    sumNode->backward = [nodes = nodes, sumNode, n]() {
        for (const auto& node : nodes) {
            node->gradient += (1.0 / n) * sumNode->gradient; // ∂(sum)/∂a[i] = 1
        }
    };

    mean_arr.nodes[0] = sumNode;
    return mean_arr;
}

int test_mean(){

    Array<float> arr1({10});
    arr1.random();
    arr1.print();
    arr1 = arr1.mean();
    arr1.print();

    Array<float> arr2({10});
    arr2.lin();
    arr2.print();
    arr2 = arr2.mean();
    arr2.print();

    return 0;
}