#include "model2.h"
#include <limits>

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

        Array<D> q;
        Array<D> k;
        Array<D> v;

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

        Array<D> create_mask(int dim){
            Array<D> mask({dim, dim});
            mask.zeros();
            mask = mask - std::numeric_limits<D>::infinity();
            mask = mask.triu(1);
            return mask;
        }

        Array<D> scaled_dot_product(Array<D> q, Array<D> k, Array<D> v, Array<D> mask){
            float d_k = float(this->head_dim);

            // 30 x 8 x 10 x 10
            Array<D> scaled = q.dot(k.permute({0, 1, 3, 2})) / std::sqrt(d_k);

            scaled = scaled + mask;
            Array<D> scores = sigmoid(scaled);
            
            // 30 x 8 x 10 x 3 v
            Array<D> values = scores.dot(v);

            return values;
        }

        Array<D> forward(Array<D>& x) override {
            // Create the model

            int batch_size = x.get_shape().shape()[0];
            int sequence_length = x.get_shape().shape()[1];
            int _d_model = x.get_shape().shape()[2];

            // 30 x 8 x 10 x 10
            Array<D> mask = this->create_mask(sequence_length);

            // 30 x 10 x 24
            Array<D> q = this->fc_q.forward(x);
            Array<D> k = this->fc_k.forward(x);
            Array<D> v = this->fc_v.forward(x);

            // 30 x 10 x 8 x 3
            q = q.reshape({batch_size, sequence_length, this->num_heads, this->head_dim});
            k = k.reshape({batch_size, sequence_length, this->num_heads, this->head_dim});
            v = v.reshape({batch_size, sequence_length, this->num_heads, this->head_dim});

            // 30 x 8 x 10 x 3
            q = q.permute({0, 2, 1, 3});
            k = k.permute({0, 2, 1, 3});
            v = v.permute({0, 2, 1, 3});

            // 30 x 8 x 10 x 3 
            this->out = this->scaled_dot_product(q, k, v, mask);

            // 30 x 10 x 8 x 3 
            this->out = this->out.permute({0, 2, 1, 3});

            // 30 x 10 x 24
            this->out = this->out.reshape({batch_size, sequence_length, _d_model});
            this->out = this->fc_out.forward(this->out);

            return this->out;
        }
};

int test_multihead_attention(){

    Array<float> inputs({1, 5, 16});
    inputs.ones();
    Array<float> labels({1, 5, 16});
    labels.random();
    labels.set_name("labels");

    MultiHeadAttention<float> model(16, 8);

    MSELoss loss_fn = MSELoss();
    Adam<float> optimiser(model.parameters, 0.01);

    Array<float> predictions;
    predictions.set_name("pds");

    for(int i = 0; i < 500; i++){

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