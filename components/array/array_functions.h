#include "access_operators.h"

// Sin Functions
template <typename D>
D sin(D x){
    return std::sin(x);
}
template <typename D>
D cos(D x){
    return std::cos(x);
}
template <typename D>
D tan(D x){
    return std::tan(x);
}
template <typename D>
D sinh(D x){
    return std::sinh(x);
}
template <typename D>
D cosh(D x){
    return std::cosh(x);
}
template <typename D>
D tanh(D x){
    return std::tanh(x);
}

template <typename D>
Array<D> sin(Array<D> &x){
    Array<D> arr = Array<D>(x.get_shape());
    std::vector<std::shared_ptr<Node<D>>> resultNodes;
    
    std::vector<D> data = x.get_data();
    std::vector<std::shared_ptr<Node<D>>> nodes = x.get_grad(); 
    std::vector<D> new_data;

    for (int i = 0; i < arr.get_shape().size(); i++)
    {
        new_data.push_back(std::sin(data[i]));

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(data[i]);
        newNode->addInput(nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], newNode]() {
            node1->gradient += std::cos(node1->value) * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.fill_grad_vec(new_data, resultNodes, arr.get_shape().size());
    return arr;
}
template <typename D>
Array<D> cos(Array<D> &x){
    Array<D> arr = Array<D>(x.get_shape());
    std::vector<std::shared_ptr<Node<D>>> resultNodes;
    
    std::vector<D> data = x.get_data();
    std::vector<std::shared_ptr<Node<D>>> nodes = x.get_grad(); 
    std::vector<D> new_data;

    for (int i = 0; i < arr.get_shape().size(); i++)
    {
        new_data.push_back(std::cos(data[i]));

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(new_data[i]);
        newNode->addInput(nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], newNode]() {
            node1->gradient +=  -std::sin(node1->value) * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.fill_grad_vec(new_data, resultNodes, arr.get_shape().size());
    return arr;
}
template <typename D>
Array<D> tan(Array<D> &x){
    Array<D> arr = Array<D>(x.get_shape());
    std::vector<std::shared_ptr<Node<D>>> resultNodes;
    
    std::vector<D> data = x.get_data();
    std::vector<std::shared_ptr<Node<D>>> nodes = x.get_grad(); 
    std::vector<D> new_data;

    for (int i = 0; i < arr.get_shape().size(); i++)
    {
        new_data.push_back(std::tan(data[i]));

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(new_data[i]);
        newNode->addInput(nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], newNode]() {
            node1->gradient += (1.0 / std::pow(std::cos(node1->value), 2)) * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.fill_grad_vec(new_data, resultNodes, arr.get_shape().size());
    return arr;
}
template <typename D>
Array<D> sinh(Array<D> &x){
    Array<D> arr = Array<D>(x.get_shape());
    std::vector<std::shared_ptr<Node<D>>> resultNodes;
    
    std::vector<D> data = x.get_data();
    std::vector<std::shared_ptr<Node<D>>> nodes = x.get_grad(); 
    std::vector<D> new_data;

    for (int i = 0; i < arr.get_shape().size(); i++)
    {
        new_data.push_back(std::sinh(data[i]));

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(new_data[i]);
        newNode->addInput(nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], newNode]() {
            node1->gradient += std::cosh(node1->value) * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.fill_grad_vec(new_data, resultNodes, arr.get_shape().size());
    return arr;
}
template <typename D>
Array<D> cosh(Array<D> &x){
    Array<D> arr = Array<D>(x.get_shape());
    std::vector<std::shared_ptr<Node<D>>> resultNodes;
    
    std::vector<D> data = x.get_data();
    std::vector<std::shared_ptr<Node<D>>> nodes = x.get_grad(); 
    std::vector<D> new_data;

    for (int i = 0; i < arr.get_shape().size(); i++)
    {
        new_data.push_back(std::cosh(data[i]));

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(new_data[i]);
        newNode->addInput(nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], newNode]() {
            node1->gradient +=  std::sinh(node1->value) * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.fill_grad_vec(new_data, resultNodes, arr.get_shape().size());
    return arr;
}
template <typename D>
Array<D> tanh(Array<D> &x){
    Array<D> arr = Array<D>(x.get_shape());
    std::vector<std::shared_ptr<Node<D>>> resultNodes;
    
    std::vector<D> data = x.get_data();
    std::vector<std::shared_ptr<Node<D>>> nodes = x.get_grad(); 
    std::vector<D> new_data;

    for (int i = 0; i < arr.get_shape().size(); i++)
    {
        new_data.push_back(std::tanh(data[i]));

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(new_data[i]);
        newNode->addInput(nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], newNode]() {
            node1->gradient += (1.0 - std::pow(std::tanh(node1->value), 2)) * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.fill_grad_vec(new_data, resultNodes, arr.get_shape().size());
    return arr;
}

// Additional functions
template <typename D>
D exp(D x){
    return std::exp(x);
}
template <typename D>
D log(D x){
    return std::log(x);
}

template <typename D>
Array<D> exp(Array<D> &x){
    Array<D> arr = Array<D>(x.get_shape());
    std::vector<std::shared_ptr<Node<D>>> resultNodes;
    
    std::vector<D> data = x.get_data();
    std::vector<std::shared_ptr<Node<D>>> nodes = x.get_grad(); 
    std::vector<D> new_data;

    for (int i = 0; i < arr.get_shape().size(); i++)
    {
        new_data.push_back(std::exp(data[i]));

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(new_data[i]);
        newNode->addInput(nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], newNode]() {
            node1->gradient += newNode->value * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.fill_grad_vec(new_data, resultNodes, arr.get_shape().size());
    return arr;
}
template <typename D>
Array<D> log(Array<D> &x){
    Array<D> arr = Array<D>(x.get_shape());
    std::vector<std::shared_ptr<Node<D>>> resultNodes;
    
    std::vector<D> data = x.get_data();
    std::vector<std::shared_ptr<Node<D>>> nodes = x.get_grad(); 
    std::vector<D> new_data;

    for (int i = 0; i < arr.get_shape().size(); i++)
    {
        new_data.push_back(std::log(data[i]));

        // Create a node for the operation
        std::shared_ptr<Node<D>> newNode = std::make_shared<Node<D>>(new_data[i]);
        newNode->addInput(nodes[i]);

        // Define backward function
        newNode->backward = [node1 = nodes[i], newNode]() {
            node1->gradient += (1.0 / node1->value) * newNode->gradient;
        };

        resultNodes.push_back(newNode);
    }

    arr.fill_grad_vec(new_data, resultNodes, arr.get_shape().size());
    return arr;
}

// Activation functions


int test_array_functions()
{
    Array<float> arrin({10});
    arrin.set_name("arrin");
    arrin.lin();
    arrin.print();

    Array<float> arrsin = sin(arrin);
    arrsin.set_name("sin");
    arrsin.print();

    Array<float> arrscos = cos(arrin);
    arrscos.set_name("cos");
    arrscos.print();

    Array<float> arrtan= tan(arrin);
    arrtan.set_name("tan");
    arrtan.print();

    Array<float> arrsinh = sinh(arrin);
    arrsinh.set_name("sinh");
    arrsinh.print();

    Array<float> arrcosh = cosh(arrin);
    arrcosh.set_name("cosh");
    arrcosh.print();

    Array<float> arrtanh = tanh(arrin);
    arrtanh.set_name("tanh");
    arrtanh.print();

    Array<float> arrpow = arrin ^ arrin;
    arrpow.set_name("pow");
    arrpow.print();

    Array<float> arrexp = exp(arrin);
    arrexp.set_name("exp");
    arrexp.print();

    Array<float> arrlog = log(arrin);
    arrlog.set_name("log");
    arrlog.print();    

    return 0;
}