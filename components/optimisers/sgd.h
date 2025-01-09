#include "adam.h"

template <typename D>
class SGD : public Optimiser<D> {
    public:
        SGD(std::vector<Array<D>*> parameters, float lr, float momentum = 0.);
        void step();
    private:
        float momentum;
        
        bool init_params;
        std::vector<std::vector<float>> averages;
};

template <typename D>
SGD<D>::SGD(std::vector<Array<D>*> parameters, float lr, float momentum = 0.):
    init_params(false),
    averages(parameters.size())
{
    this->parameters = parameters;
    this-> learning_rate = lr;
    this->momentum = momentum;
}

template <typename D>
void SGD<D>::step(){

    if(this->init_params == false){
        this->init_params = true;

        for(int i = 0; i < this->parameters.size(); i++){
            this->averages[i] = std::vector<float>(this->parameters[i]->get_shape().size(), 0.);
        }
    }

    for(int i = 0; i < this->parameters.size(); i++){
        std::vector<D> updated_data;
        std::vector<D> data = parameters[i]->get_data();
        std::vector<std::shared_ptr<Node<D>>> nodes = parameters[i]->get_grad();
        for(int j = 0; j < this->parameters[i]->get_shape().size(); j++){
            float delta = (this->averages[i][j] * this->momentum) + (nodes[j]->gradient * (1.0 - this->momentum));

            this->averages[i][j] = delta;
            updated_data.push_back(data[j] -= delta * this->learning_rate);
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

    Array<float> weights({5, 6});
    weights.set_name("weights");
    Array<float> biases({6});
    biases.set_name("bias");
    
    weights.random();
    biases.ones();

    Array<float> inputs = Array<float>::from_array({5}, {1.,1.,1.,1.,1.});
    Array<float> labels = Array<float>::from_array({6}, {0.,0.,0.,1.,1.,1.,});
    labels.set_name("labels");

    std::vector<Array<float>*> params = {&weights, &biases};

    MSELoss loss_fn = MSELoss();
    SGD<float> optimiser(params, 0.05);

    Array<float> predictions;
    predictions.set_name("pds");

    for(int i = 0; i < 20; i++){

        printf("\niteration %d:=========================================\n", i);

        predictions = inputs.dot(weights)  + biases;
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