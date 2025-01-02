#include "model_template.h"

template <typename D>
class TestModel : public Model<D> {

    private:
        // Define params
        Array<D> weights;
        Array<D> bias;

    public:
        // Save params
        TestModel(int input_size, int output_size) : Model({&weights, &bias}){
            // Initialise params
            this->weights = Array<D>({input_size, output_size}).random();
            this->bias = Array<D>({output_size}).ones();
        }

        Array<D> forward(Array<D> x) override {
            // Create the model
            this->out = x.dot(weights) + bias;
            return this->out;
        }
};

int test_test_model(){

    Array<float> inputs = Array<float>::from_array({5}, {1.,1.,1.,1.,1.});
    Array<float> labels = Array<float>::from_array({6}, {0.,0.,0.,1.,1.,1.,});
    labels.set_name("labels");

     TestModel<float> model(5, 6);

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