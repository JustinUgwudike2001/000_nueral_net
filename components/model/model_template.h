#include "../optimisers/sgd.h"

template <typename D>
class Model {

    protected:

        Model(){};
        Array<D> out;
        void add_params(const std::vector<Array<D>*>& params);

    public:
        std::vector<Array<D>*> parameters;
        virtual Array<D> forward(Array<D> x) = 0;

        void load();
        void save();

        void print();
        void print_grads();
};

template <typename D>
void Model<D>::add_params(const std::vector<Array<D>*>& params)
{
    // Just insert all the incoming pointers into this->parameters
    this->parameters.insert(
        this->parameters.end(),
        params.begin(),
        params.end()
    );
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

/*
given i have a model class:

template <typename D>
class Model {

    protected:

        Model(){};
        Array<D> out;
        void add_params(std::vector<std::vector<Array<D>*>> args);

    public:
        std::vector<Array<D>*> parameters;
        virtual Array<D> forward(Array<D> x) = 0;

        void load();
        void save();

        void print();
        void print_grads();
};

template <typename D>
void Model<D>::add_params(std::vector<std::vector<Array<D>*>> args){
    for (int i = 0; i < args.size(); i++){
        for(int j = 0; j < args[i].size(); j++){
            this->parameters.push_back(args[i][j]);
            std::cout<<"i"<<i<<std::endl;
            std::cout<<"j"<<j<<std::endl;
            std::cout<<std::endl<<"args.size: "<<args.size()<<"args[i].size: "<<args[i].size();

            //args[i][j]->print();
        }
    }
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

how can i make it so that i can define an ai model as a set of array computations then use the add_params(function) to create a reference to the models parameter arrays for gradient optimisation? as the function is now, i cannot add the parameters of a model class using the add_params function of the higher level model
*/