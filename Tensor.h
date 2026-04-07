//
// Created by Edmundo on 05/04/2026.
//

#ifndef TENSOR_H
#define TENSOR_H
#include <ostream>
#include <vector>
#include <cmath>

using namespace std;
class Tensor;

class TensorTransform {
public:
    virtual Tensor apply(const Tensor& t) const = 0;
    virtual ~TensorTransform() = default;
};

class Tensor {
    int filas,columnas, capa;
    int ndims;

    double *vector_d = nullptr;
    double **matrix = nullptr;
    double ***matrix_tri = nullptr;

public:
    Tensor(const vector<size_t>& shape, const vector<double>& values);
    static Tensor zeros(const vector<size_t>& shape);
    static Tensor ones(const vector<size_t>& shape);
    static Tensor random(const vector<size_t>& shape, double min, double max);
    static Tensor arange(int inicio, int fin);

    Tensor(const Tensor& other);
    Tensor(Tensor&& other) noexcept;
    Tensor& operator=(const Tensor & other);
    Tensor& operator=(Tensor &&other) noexcept ;

    Tensor apply(const TensorTransform& transform) const;

    Tensor operator+(const Tensor& other) const;
    Tensor operator-(const Tensor& other) const;
    Tensor operator*(const Tensor& other) const;
    Tensor operator*(double escalar) const;

    Tensor view(const vector<size_t>& new_shape) const;
    Tensor unsqueeze(int dim) const;

    static Tensor concat(const vector<Tensor>& tensors, int axis);

    friend Tensor dot(const Tensor& a, const Tensor& b);
    friend Tensor matmul(const Tensor& a, const Tensor& b);

    friend void print(Tensor &mat);
    friend class ReLU;
    friend class Sigmoid;
    ~Tensor();

};
class ReLU : public TensorTransform {
public:
    Tensor apply(const Tensor& t) const override;
};

class Sigmoid : public TensorTransform {
public:
    Tensor apply(const Tensor& t) const override;
};


#endif //TENSOR_H
