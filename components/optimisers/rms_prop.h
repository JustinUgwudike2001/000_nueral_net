#include "optimiser.h"

template <typename D>
class RMSProp : public Optimiser<D> {
    public:
        RMSProp(std::vector<Array<D>*> parameters, float lr, float beta_1 = 0.9);
        void step();
    private:
        float beta_1;
        
        bool init_params;
        std::vector<std::vector<float>> s_ds;

};

template <typename D>
RMSProp<D>::RMSProp(std::vector<Array<D>*> parameters, float lr, float beta_1 = 0.9) :
    init_params(false),
    s_ds(parameters.size())
{
    this->parameters = parameters;
    this-> learning_rate = lr;
    this->beta_1 = beta_1;
}

template <typename D>
void RMSProp<D>::step(){

    if(this->init_params == false){
        this->init_params = true;

        for(int i = 0; i < this->parameters.size(); i++){
            this->s_ds[i] = std::vector<float>(this->parameters[i]->get_shape().size(), 0.);
        }
    }

    for(int i = 0; i < this->parameters.size(); i++){
        std::vector<D> updated_data;
        std::vector<D> data = parameters[i]->get_data();
        std::vector<std::shared_ptr<Node<D>>> nodes = parameters[i]->get_grad();
        for(int j = 0; j < this->parameters[i]->get_shape().size(); j++){

            this->s_ds[i][j] = (this->s_ds[i][j] * this->beta_1) + (std::pow(nodes[j]->gradient, 2) * (1.0 - this->beta_1));
                
            float delta = nodes[j]->gradient / (std::pow(this->s_ds[i][j], 0.5) + 1e-15);
            updated_data.push_back(data[j] -= delta * this->learning_rate);
        }
        this->parameters[i]->fill_vec(data, this->parameters[i]->get_shape().size());
    }
}


int test_rms_prop(){

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
    RMSProp<float> optimiser(params, 0.01);

    Array<float> predictions;
    predictions.set_name("pds");

    for(int i = 0; i < 100; i++){

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