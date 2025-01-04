#include "fully_connected.h"

template <typename D>
class Sigmoid : public Model<D> {
    public:
        // Save params
        Tanh() : Model({}){}

        Array<D> forward(Array<D> x) override {
            // Create the model
            this->out = tanh(x);
            return this->out;
        }
};

int test_tanh(){

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

        model.print();
        model.print_grads();

        optimiser.step();
    }

    return 0;
}