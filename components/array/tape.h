#include <memory>
#include <functional>
#include "shape.h"

template <typename D>
struct Node {
    std::string op; // Operation name (e.g., "add", "multiply")
    std::vector<std::shared_ptr<Node>> inputs; // Input nodes
    D value; // Result of the operation
    float gradient; // Gradient w.r.t this node
    std::function<void()> backward; // Function to compute the gradients
    bool visited; // Prevent duplicate backward calls

    Node(D value) : value(value), gradient(0.0), backward([]() {}), visited(false) {}

    void addInput(const std::shared_ptr<Node>& input) {
        inputs.push_back(input);
    }

    void computeGradient() {
        if (visited) return; // Avoid re-computing gradients for the same node
        visited = true;
        
        backward(); // Compute this node's gradient

        // Recursively compute gradients for input nodes
        for (const auto& input : inputs) {
            input->computeGradient();
        }
    }
};