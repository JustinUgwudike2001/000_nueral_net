#include "../loss/mse_loss.h"

template <typename D>
class Optimiser {

    protected:
        Optimiser();
        std::vector<Array<D>*> parameters;
        float learning_rate;
};

template <typename D>
Optimiser<D>::Optimiser(){
    this->learning_rate = 0.01;
}