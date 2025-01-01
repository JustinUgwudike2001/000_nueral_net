#include "../mse_loss.h"

int main()
{


    Array<float> weights({5});
    Array<float> biases({5});
    
    weights.random();
    biases.ones();

    Array<float> inputs = Array<float>::from_array({5}, {0.,0.,0.,0.,0.});
    Array<float> labels = Array<float>::from_array({5}, {1.,1.,0.,0.,1.});

    Array<float> predictions = inputs * weights + biases;

    MSELoss loss_fn = MSELoss();

    Array<float> loss = loss_fn.forward(predictions, labels);
    loss_fn.value.print();
    
    loss.backward();
    weights.print_grad();
    biases.print_grad();
}