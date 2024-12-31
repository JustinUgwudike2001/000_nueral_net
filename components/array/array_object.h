#include <stdio.h>
#include <string.h>
#include <cstring>
#include "tape.h"
#include <math.h>

template <typename D>
class Array
{
public:
    Array();
    Array(Shape shape);
    Array(std::vector<int> dims);

    // basic ops
    Array operator=(const Array &arr2);
    // template <typename U>
    // Array& operator=(Array<U>& arr2);

    Array operator+(D rhs);
    Array operator-(D rhs);
    Array operator/(D rhs);
    Array operator*(D rhs);
    Array operator^(D rhs);

    // array ops
    Array operator+(Array &rhs);
    Array operator-(Array &rhs);
    Array operator*(Array &rhs);
    Array operator/(Array &rhs);

    // access ops
    D &operator()(std::vector<size_t> idxes);
    void operator()(D value, std::vector<size_t> idxes);

    Array reshape(std::vector<int> dims);
    Array permute(std::vector<int> dims);
    Array t();
    Array dot(Array &rhs);

    std::vector<Array> split(int dim);

    Array squeeze(int dim);
    Array unsqueeze(int dim);

    Array expand(std::vector<int> dims);
    Array broadcast_to(std::vector<int> dims);

    void set_name(std::string string);

    void fill_arr(D _data[], int size);
    void fill_vec(std::vector<D> _data, int size);
    void fill_grad_vec(std::vector<D> _data, std::vector<std::shared_ptr<Node<D>>> _nodes, int size);

    Array ones();
    Array random();
    Array zeros();
    Array lin();

    static Array zeros(std::vector<int> dims);
    static Array random(std::vector<int> dims);
    static Array ones(std::vector<int> dims);
    static Array lin(std::vector<int> dims);
    static Array from_array(std::vector<int> dims, std::vector<D> array);

    void print_grad();
    void print_tape();
    void print();

    inline Shape get_shape()
    {
        return this->shape;                 
    }
    inline std::vector<D> get_data()
    {
        return this->data;
    }
    inline std::vector<std::shared_ptr<Node<D>>> get_grad()
    {
        return this->nodes;
    }

    // Perform backpropagation
    void backward() {
        for (auto& node : nodes) {
            node->gradient = 1.0; // Start with gradient of 1.0 for final node
            node->computeGradient();
        }
    }
    
private:
    char name[10];
    Shape shape;
    int rank;

    std::vector<D> data;
    //std::vector<float> dots;
    std::vector<std::shared_ptr<Node<D>>> nodes;

    // struct Operation
    // {
    //     int op_type;
    //     Array<D>* a;
    //     Array<D>* b;
    //     std::shared_ptr<Array<D>> result;
    //     D scalar;

    //     Operation(
    //         int type, 
    //         Array<D>* in_a,
    //         Array<D>* in_b, 
    //         std::shared_ptr<Array<D>> out_result,
    //         D sca
    //     ){
    //         this->op_type = type;
    //         this->a = in_a;
    //         this->b = in_b;
    //         this->result = out_result;
    //         this->scalar = sca;

    //         // this->result->set_name("result");
    //         // this->result->print();
    //         // this->result->print_grad();
    //     }
    // };

    // struct Tape {

    //     int length;
    //     std::vector<Operation> operations;

    //     Tape(){
    //         operations.clear();
    //         length = 0;
    //     }

    //     void add_operation(
    //         int type,
    //         Array* a,
    //         Array* b,
    //         std::shared_ptr<Array<D>> result,
    //         D scalar
    //     ) {
    //         operations.push_back(Operation(type, a, b, result, scalar));
    //         length += 1;
    //     }

    //     void empty() {
    //         operations.clear();
    //         length = 0;
    //     }

    //     void backward() {

    //         for (int i = length - 1; i >= 0; i--){

    //             std::vector<float> in_a = operations[i].a->get_data();
    //             std::vector<float> grad_a = operations[i].a->get_grad();
    //             std::vector<float> in_b;
    //             std::vector<float> grad_b;

    //             if(operations[i].op_type < 4){
    //                 in_b = operations[i].b->get_data(); 
    //                 grad_b = operations[i].b->get_grad();
    //             }     

    //             std::vector<float> grad_result = operations[i].result->get_grad();

    //             int type = operations[i].op_type;

    //             switch(type){
    //                 case 0:
    //                     printf("add back function\n");
    //                     for (int j = 0; j < operations[i].a->get_shape().size(); ++j) {
    //                         grad_a[j] += grad_result[j];
    //                         grad_b[j] += grad_result[j];
    //                     }
    //                     break;
    //                 case 1:
    //                     printf("sub back function\n");
    //                     for (int j = 0; j < operations[i].a->get_shape().size(); ++j) {
    //                         grad_a[j] += grad_result[j];
    //                         grad_b[j] -= grad_result[j];
    //                     }
    //                     break;
    //                 case 2:
    //                     printf("mul back function\n");
    //                     for (int j = 0; j < operations[i].a->get_shape().size(); ++j) {
    //                         grad_a[j] += grad_result[j] * in_b[i];
    //                         grad_b[j] += grad_result[j] * in_a[i];
    //                     }
    //                     break;
    //                 case 3:
    //                     printf("div back function\n");
    //                     for (int j = 0; j < operations[i].a->get_shape().size(); ++j) {
    //                         grad_a[j] += grad_result[j] / in_b[i];
    //                         grad_b[j] -= grad_result[j] * in_a[i] / (in_b[i] * in_b[i]);
    //                     }
    //                     break;
    //                 case 4:
    //                     printf("sadd back function\n");
    //                     for (int j = 0; j < operations[i].a->get_shape().size(); ++j) {
    //                         grad_a[j] += operations[i].scalar;
    //                     }
    //                     break;
    //                 case 5:
    //                     printf("ssub back function\n");
    //                     for (int j = 0; j < operations[i].a->get_shape().size(); ++j) {
    //                         grad_a[j] -= operations[i].scalar;
    //                     }
    //                     break;
    //                 case 6:
    //                     printf("smul back function\n");
    //                     for (int j = 0; j < operations[i].a->get_shape().size(); ++j) {
    //                         grad_a[j] += grad_result[j] * operations[i].scalar;
    //                     }
    //                     break;
    //                 case 7:
    //                     printf("sdiv back function\n");
    //                     for (int j = 0; j < operations[i].a->get_shape().size(); ++j) {
    //                         grad_a[j] += grad_result[j] / operations[i].scalar;
    //                     }
    //                     break;
    //                 case 8:
    //                     printf("spow back function\n");
    //                     for (int j = 0; j < operations[i].a->get_shape().size(); ++j) {
    //                         grad_a[j] += grad_result[j] * operations[i].scalar * std::pow(in_a[j], operations[i].scalar - 1);
    //                     }
    //                     break;
    //                 default:
    //                     break;
    //             }

    //             operations[i].a->fill_grad_vec(operations[i].a->get_data(), in_a, operations[i].a->get_shape().size());
    //             if(operations[i].op_type < 4){
    //                 operations[i].b->fill_grad_vec(operations[i].b->get_data(), in_b, operations[i].b->get_shape().size());
    //             }
    //         }
    //     }

    //     void print() {
    //         std::cout<<"tape: {";
            
    //         for (int i = 0; i < length; i++){
    //             switch(operations[i].op_type){
    //                 case 0:
    //                     std::cout<<"add";
    //                     break;
    //                 case 1:
    //                     std::cout<<"sub";
    //                     break;
    //                 case 2:
    //                     std::cout<<"mul";
    //                     break;
    //                 case 3:
    //                     std::cout<<"div";
    //                     break;
    //                 case 4:
    //                     std::cout<<"sadd";
    //                     break;
    //                 case 5:
    //                     std::cout<<"ssub";
    //                     break;
    //                 case 6:
    //                     std::cout<<"smul";
    //                     break;
    //                 case 7:
    //                     std::cout<<"sdiv";
    //                     break;
    //                 case 8:
    //                     std::cout<<"spow";
    //                     break;
    //                 default:
    //                     std::cout<<"invalid op";
    //                     break;
    //             }

    //             if (i < length - 1){
    //                 std::cout<<", "; 
    //             }
    //         }

    //         std::cout<<"}, length: {"<<this->length<<"}"<<std::endl;
    //     }
    // };

    // Tape tape;

    void print_arr2();
    void print_arr3();
    void print_arr4();

    Array try_dot_arr1(Array &rhs);
    Array try_dot_arr2(Array &rhs);
    Array try_dot_arr3(Array &rhs);
    Array try_dot_arr4(Array &rhs);
    Array try_dot(Array &lhs, Array &rhs);

};

template <typename D>
void Array<D>::set_name(std::string string)
{
    if (string.size() > 8)
    {
        std::cout << "that name is too long!" << std::endl;
        return;
    }

    if (8 > string.size())
        string.insert(0, 8 - string.size(), ' ');

    strcpy(this->name, string.c_str());
}