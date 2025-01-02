#include "../optimisers/sgd.h"

template <typename D>
class Model {

    protected:
        Model(std::vector<Array<D>*> params);
        Array<D> out;

    public:
        std::vector<Array<D>*> parameters;
        virtual Array<D> forward(Array<D> x) = 0;
        void print();
        void print_grads();
};

template <typename D>
Model<D>::Model(std::vector<Array<D>*> params) {
    this->parameters = params;
}

template <typename D>
void Model<D>::print() {
    for (int i = 0; i < this->parameters.size(); i++){
        this->parameters[i]->print();
    }
}

template <typename D>
void Model<D>::print_grads() {
    for (int i = 0; i < this->parameters.size(); i++){
        this->parameters[i]->print_grad();
    }
}