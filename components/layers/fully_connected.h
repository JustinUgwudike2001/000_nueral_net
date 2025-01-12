#include "../model/test_model.h"

template <typename D>
class FullyConnected : public Model<D> {

    private:
        // Define params
        Array<D> weights;
        Array<D> bias;

    public:

        FullyConnected(){};
        
        FullyConnected(int input_size, int output_size) :
        weights({input_size,  output_size}), 
        bias({output_size})
        {
            // Initialise params
            this->weights.random();
            this->bias.ones();

            // Save params
            this->add_params({&weights, &bias});
        }

        Array<D> forward(Array<D>& x) override {
            // Create the model
            this->out = x.dot(weights) + bias;
            return this->out;
        }
};

int test_fc(){

    Array<float> inputs = Array<float>::from_array({5}, {1.,1.,1.,1.,1.});
    Array<float> labels = Array<float>::from_array({6}, {0.,0.,0.,1.,1.,1.,});
    labels.set_name("labels");

    FullyConnected<float> model(5, 6);

    MSELoss loss_fn = MSELoss();
    SGD<float> optimiser(model.parameters, 0.05);

    Array<float> predictions;
    predictions.set_name("pds");

    for(int i = 0; i < 20; i++){

        printf("\niteration %d:=========================================\n", i);

        predictions = model.forward(inputs);
        predictions.print();
        labels.print();

        Array<float> loss = loss_fn.forward(predictions, labels);
        loss_fn.print();

        loss.backward();

        //model.print();
        //model.print_grads();

        optimiser.step();
    }

    return 0;
}