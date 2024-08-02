#include <stdio.h>
#include <string.h>
#include <cstring>
#include "shape.h"
#include <math.h>

template<typename D>
class Array {
    public:

        Array();
        Array(Shape shape);
        Array(int _shape_0); //Array1;
        Array(int _shape_0, int _shape_1); //Array2
        Array(int _shape_0, int _shape_1, int _shape_2); //Array3
        Array(int _shape_0, int _shape_1, int _shape_2, int _shape_3); //Array4

        //basic ops
        Array operator=(const Array& arr2);
        Array operator+(D rhs);
        Array operator-(D rhs);
        Array operator/(D rhs);
        Array operator*(D rhs);
        Array operator^(D rhs);

        //array ops
        Array operator+(Array& rhs);
        Array operator-(Array& rhs);
        Array operator*(Array& rhs);
        Array operator/(Array& rhs);

        //access ops
        D& operator()(std::size_t idx_1);
        D& operator()(std::size_t idx_1, std::size_t idx_2);
        D& operator()(std::size_t idx_1, std::size_t idx_2, std::size_t idx_3);
        D& operator()(std::size_t idx_1, std::size_t idx_2, std::size_t idx_3, std::size_t idx_4);

        Array broadcast();

        Array reshape(int shape_0);
        Array reshape(int shape_0, int shape_1);
        Array reshape(int shape_0, int shape_1, int shape_2);
        Array reshape(int shape_0, int shape_1, int shape_2, int shape_3);
            
        
        Array permute(int dim1, int dim2);
        Array permute(int dim1, int dim2, int dim3);
        Array permute(int dim1, int dim2, int dim3, int dim4);
        Array t();
        Array dot(Array& rhs);

        std::vector<Array> split(int dim);
        
        Array squeeze(int dim);
        Array unsqueeze(int dim);
        
        Array expand(int dim1, int dim2);
        Array expand(int dim1, int dim2, int dim3);
        Array expand(int dim1, int dim2, int dim3, int dim4);

        Array broadcast_to(int dim1, int dim2);
        Array broadcast_to(int dim1, int dim2, int dim3);
        Array broadcast_to(int dim1, int dim2, int dim3, int dim4);

        void set_name(std::string string);

        void fill_arr(D _data[], int size);
        void fill_vec(std::vector<D> _data, int size);
        void fill_grad_vec(std::vector<D> _data, std::vector<float> _dots, int size);

        Array ones();
        static Array ones(int shape_0);
        static Array ones(int shape_0, int shape_1);
        static Array ones(int shape_0, int shape_1, int shape_2);
        static Array ones(int shape_0, int shape_1, int shape_2, int shape_3);
        Array random();
        static Array random(int shape_0);
        static Array random(int shape_0, int shape_1);
        static Array random(int shape_0, int shape_1, int shape_2);
        static Array random(int shape_0, int shape_1, int shape_2, int shape_3);
        Array zeros();
        static Array zeros(int shape_0);
        static Array zeros(int shape_0, int shape_1);
        static Array zeros(int shape_0, int shape_1, int shape_2);
        static Array zeros(int shape_0, int shape_1, int shape_2, int shape_3);
        Array lin();
        static Array lin(int shape_0);
        static Array lin(int shape_0, int shape_1);
        static Array lin(int shape_0, int shape_1, int shape_2);
        static Array lin(int shape_0, int shape_1, int shape_2, int shape_3);


        void print_grad();
        void print();

        inline Shape get_shape(){
            return this->shape;
        }
        inline std::vector<D> get_data(){
            return this->data;  
        }
        inline std::vector<float> get_grad(){
            return this->dots;
        }

        //void to_array2();

    private:
        char name[10];
        Shape shape;
        int rank;

        std::vector<D> data;
        std::vector<float> dots;

        Array create_arr();

        void print_arr2();
        void print_arr3();
        void print_arr4();

        Array try_dot_arr1(Array& rhs);
        Array try_dot_arr2(Array& rhs);
        Array try_dot_arr3(Array& rhs);
        Array try_dot_arr4(Array& rhs);
        
        Array try_dot(Array& lhs, Array& rhs);
};

template <typename D>
void Array<D>::set_name(std::string string){
    if (string.size() > 8) {
        std::cout << "that name is too long!"<< std::endl;
        return; 
    }

    if(8 > string.size())
        string.insert(0, 8 - string.size(), ' ');

    strcpy(this->name, string.c_str());
}