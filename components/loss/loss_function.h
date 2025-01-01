#include "../array/mean.h"

class LossFunction {

    protected:
        LossFunction();

    public:
        Array<float> value;
        void print();
};

LossFunction::LossFunction(){
    this->value = Array<float>::zeros({1});
    this->value.set_name("loss");
}

void LossFunction::print(){
    std::cout << "    loss : " << this->value.get_data()[0] << std::endl;
}