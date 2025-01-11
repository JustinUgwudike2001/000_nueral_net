#include "model2.h"

template <typename D>
class MultiHeadAttention : public Model<D> {

    private:
        // Define params
        Array<D> weights;
        Array<D> bias;
        int d_model;
        int num_heads;
        int head_dim;

        FullyConnected<D> fc_q;
        FullyConnected<D> fc_k;
        FullyConnected<D> fc_v;
        FullyConnected<D> fc_out;

    public:

        MultiHeadAttention(){};
        
        MultiHeadAttention(int d_model, int num_heads) :
        d_model(d_model),
        num_heads(num_heads),
        fc_q(d_model, d_model),
        fc_k(d_model, d_model),
        fc_v(d_model, d_model),
        fc_out(d_model, d_model)
        {
            // Initialise params
            this->head_dim = d_model / num_heads;

            // Save params
            this->add_params(this->fc_q.parameters);
            this->add_params(this->fc_k.parameters);
            this->add_params(this->fc_v.parameters);
            this->add_params(this->fc_out.parameters);
        }

        Array<D> scaled_dot_product(Array q, Array k, Array v, Array mask){
            float d_k = float(this->head_dim);

            // 30 x 8 x 10 x 10
            Array<D> scaled = q.dot(k.permute({0, 1, 3, 2})) / std::sqrt(d_k);

            scaled = scaled + mask;
            Array<D> scores = softmax(scaled);
            
            // 30 x 8 x 10 x 3 v
            Array<D> values = score.dot(v);
        }

        Array<D> forward(Array<D> x) override {
            // Create the model
            this->out = x.dot(weights) + bias;
            return this->out;
        }
};

int test_multihead_attention(){

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