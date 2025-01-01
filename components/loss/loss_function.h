#include "../array/mean.h"

class LossFunction {

    protected:
        LossFunction();

    public:
        Array<float> value;
};

LossFunction::LossFunction(){
    this->value = Array<float>::zeros({1});
}

