#include "fully_connected.h"

template <typename D>
class Model2 : public Model<D> {

    private:
        // Define params
        FullyConnected<D> fc1;
        FullyConnected<D> fc2;

    public:
        // Save params
        Model2(int input_size, int output_size) : 
        fc1(input_size, 3), 
        fc2(3, output_size) {
            this->add_params(this->fc1.parameters);
            this->add_params(this->fc2.parameters);
        }

        Array<D> forward(Array<D> x) override {
            // Create the model
            this->out = this->fc1.forward(x);
            this->out = relu(this->out);
            this->out = this->fc2.forward(this->out);
            this->out = sigmoid(this->out);
            return this->out;
        }
};

int test_model2(){

    Array<float> inputs = Array<float>::from_array({5}, {1.,1.,1.,1.,1.});
    Array<float> labels = Array<float>::from_array({6}, {0.,0.,0.,1.,1.,1.,});
    labels.set_name("labels");

    Model2<float> model(5, 6);
    //model.print();

    MSELoss loss_fn = MSELoss();
    Adam<float> optimiser(model.parameters, 0.08);

    Array<float> predictions;
    predictions.set_name("pds");

    for(int i = 0; i < 20; i++){

        printf("\niteration %d:=========================================\n", i);

        predictions = model.forward(inputs);
        predictions.print();
        labels.print();

        Array<float> loss = loss_fn.forward(predictions, labels);
        loss_fn.print();
        loss.print();

        loss.backward();

        //model.print();
        //model.print_grads();

        optimiser.step();
    }

    return 0;
}