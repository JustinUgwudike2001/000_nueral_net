#include "loss_function.h"

class MSELoss : public LossFunction {
    public:
        Array<float> forward(Array<float> &predictions, Array<float> &labels); 
};

Array<float> MSELoss::forward(Array<float> &predictions, Array<float> &labels) {
        Array<float> loss_arr;

        loss_arr = (labels - predictions) ^ 2;
        this->value = loss_arr.mean();

        return loss_arr;
    }