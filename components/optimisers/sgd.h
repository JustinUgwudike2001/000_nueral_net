#include "optimiser.h"

template <typename D>
class SGD : public Optimiser<D> {
    public:
        SGD(std::vector<Array<D>*> parameters, float lr, float momentum = 0.);
        void step();
    private:
        float momentum;
};

template <typename D>
SGD<D>::SGD(std::vector<Array<D>*> parameters, float lr, float momentum = 0.){
    this->parameters = parameters;
    this-> learning_rate = lr;
    this->momentum = momentum;
}

template <typename D>
void SGD<D>::step(){
    for(int i = 0; i < this->parameters.size(); i++){
        std::vector<D> updated_data;
        std::vector<D> data = parameters[i]->get_data();
        std::vector<std::shared_ptr<Node<D>>> nodes = parameters[i]->get_grad();
        for(int j = 0; j < this->parameters[i]->get_shape().size(); j++){
            updated_data.push_back(data[j] -= nodes[j]->gradient * this->learning_rate);
        }
        this->parameters[i]->fill_vec(data, this->parameters[i]->get_shape().size());
    }
}

int test_sgd(){

    Array<float> weights({5});
    weights.set_name("weights");
    Array<float> biases({5});
    biases.set_name("biases");
    
    weights.random();
    biases.ones();

    Array<float> inputs = Array<float>::from_array({5}, {1.,1.,1.,1.,1.});
    Array<float> labels = Array<float>::from_array({5}, {1.,0.,1.,0.,1.});
    labels.set_name("labels");

    std::vector<Array<float>*> params = {&weights, &biases};

    MSELoss loss_fn = MSELoss();
    SGD<float> optimiser(params, 0.3);

    Array<float> predictions;
    predictions.set_name("pds");

    for(int i = 0; i < 20; i++){

        printf("\niteration %d:=========================================\n", i);

        predictions = inputs * weights + biases;
        predictions.print();
        labels.print();

        Array<float> loss = loss_fn.forward(predictions, labels);
        loss_fn.print();

        loss.backward();

        optimiser.step();

        weights.print();
        biases.print();
    }

    return 0;
}

int test_sgd_dot(){

    Array<float> weights({5, 3});
    weights.set_name("weights");
    Array<float> biases({3});
    biases.set_name("bias");
    
    weights.random();
    biases.ones();

    Array<float> inputs = Array<float>::from_array({5}, {1.,1.,1.,1.,1.});
    Array<float> labels = Array<float>::from_array({3}, {1.,0.,1.});
    labels.set_name("labels");

    std::vector<Array<float>*> params = {&weights, &biases};

    MSELoss loss_fn = MSELoss();
    SGD<float> optimiser(params, 0.09);

    Array<float> predictions;
    predictions.set_name("pds");

    for(int i = 0; i < 20; i++){

        printf("\niteration %d:=========================================\n", i);

        predictions = inputs.dot(weights) + biases;
        predictions.print();
        labels.print();

        Array<float> loss = loss_fn.forward(predictions, labels);
        loss_fn.print();

        loss.backward();

        optimiser.step();

        weights.print();
        biases.print();
    }

    return 0;
}