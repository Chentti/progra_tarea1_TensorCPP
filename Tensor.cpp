//
// Created by Edmundo on 05/04/2026.
//

#include "Tensor.h"
#include <iostream>
#include <initializer_list>
#include <vector>

using namespace std;

Tensor::Tensor(const vector<size_t>& shape, const vector<double>& values) {
    ndims = shape.size();

    if(ndims < 1 or ndims > 3){
        cout << "Error: máximo 3 dimensiones\n";
        exit(1);
    }
    int temp[3]={1,1,1};

    for (int i=0;i<ndims;i++) {
        temp[i] = shape[i];
    }

    filas = temp[0];
    columnas= temp[1];
    capa=temp[2];

    int total = filas * columnas * capa;

    if (total != values.size() ) {
        cout << "Error: El tamaño no es correcto\n";
        exit(1);
    }

    int idx = 0;
    if (ndims == 1) {
        vector_d = new double[filas];
        for (int i=0;i<filas;i++) {
            vector_d[i] = values[idx++];
        }
    }
    else if (ndims == 2) {
        matrix = new double*[filas];
        for(int i = 0; i < filas; i++) {
            matrix[i] = new double[columnas];
            for (int j = 0; j < columnas; j++) {
                matrix[i][j] = values[idx++];
            }
        }
    }
    else if (ndims == 3) {
        matrix_tri = new double**[filas];
        for(int i = 0; i < filas; i++) {
            matrix_tri[i] = new double*[columnas];
            for(int j = 0; j < columnas; j++) {
                matrix_tri[i][j] = new double[capa];
                for(int k = 0; k < capa; k++) {
                    matrix_tri[i][j][k] = values[idx++];
                }
            }
        }
    }
}
Tensor Tensor::zeros(const vector<size_t>& shape) {
    int total = 1;
    for(auto x : shape) total *= x;

    vector<double> vals(total, 0.0);
    return Tensor (shape, vals);
}
Tensor Tensor::ones(const vector<size_t>& shape) {
    int total = 1;
    for(auto x : shape) total *= x;

    vector<double> vals(total, 1);
    return Tensor (shape, vals);
}

Tensor Tensor::random(const vector<size_t>& shape, double min, double max) {
    int total = 1;
    for(auto x : shape) total *= x;

    vector<double> vals(total);

    srand(time(0));

    for(int i = 0; i < total; i++){
        double r = rand();
        double r2 = r / RAND_MAX;
        double r3 = r2 * (max - min);
        double final = min + r3;
        vals[i] = final;
    }

    return Tensor(shape, vals);
}
Tensor Tensor::arange(int inicio, int fin){

    int n = fin - inicio;

    vector<size_t> shape = {(size_t)n};
    vector<double> vals(n);

    for(int i = 0; i < n; i++){
        vals[i] = inicio + i;
    }

    return Tensor(shape, vals);
}

Tensor::Tensor(const Tensor& other) {
cout << "Se aplico el constructor de copia " << endl;
    ndims = other.ndims;
    filas = other.filas;
    columnas = other.columnas;
    capa = other.capa;

    if(ndims == 1) {
        vector_d = new double[filas];
        for (int i=0;i<filas;i++) {
            vector_d[i] = other.vector_d[i];
        }
    }
    else if (ndims == 2) {
        matrix = new double*[filas];
        for (int i = 0; i < filas; i++) {
            matrix[i] = new double[columnas];
            for (int j = 0; j < columnas; j++) {
                matrix[i][j] = other.matrix[i][j];
            }
        }
    }
    else if (ndims == 3) {
        matrix_tri = new double**[filas];
        for (int i=0;i<filas;i++) {
            matrix_tri[i]=new double*[columnas];
            for (int j=0;j<columnas;j++) {
                matrix_tri[i][j] = new double[capa];
                for (int k=0;k<capa;k++) {
                    matrix_tri[i][j][k]= other.matrix_tri[i][j][k];
                }
            }
        }
    }

}
Tensor::Tensor(Tensor&& other)noexcept{
cout<<"Se aplico el constructor de movimiento"<<endl;
    ndims = other.ndims;
    filas = other.filas;
    columnas = other.columnas;
    capa = other.capa;

    vector_d = other.vector_d;
    matrix = other.matrix;
    matrix_tri = other.matrix_tri;

    other.vector_d = nullptr;
    other.matrix = nullptr;
    other.matrix_tri = nullptr;

    other.ndims=0;
    other.filas=0;
    other.columnas=0;
    other.capa=0;
}

Tensor& Tensor::operator=(const Tensor& other) {
    cout<< "Asignacion por copia\n";
    if (this == &other)return *this;

    if (ndims == 1 ) {
        delete[] vector_d;
    }
    else if (ndims == 2) {
        for (int i=0;i<filas;i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    else if (ndims == 3) {
        for (int i=0;i<filas;i++) {
            for (int j=0;j<columnas;j++) {
                delete[] matrix_tri[i][j];
            }
            delete[] matrix_tri[i];
        }
        delete[] matrix_tri;
    }

    ndims = other.ndims;
    filas = other.filas;
    columnas = other.columnas;
    capa = other.capa;

    if (ndims == 1) {
        vector_d = new double[filas];
        for (int i=0;i<filas;i++) {
            vector_d[i] = other.vector_d[i];
        }
    }
    else if (ndims == 2) {
        matrix = new double*[filas];
        for (int i=0;i<filas;i++) {
            matrix[i] = new double[columnas];
            for (int j=0;j<columnas;j++) {
                matrix[i][j] = other.matrix[i][j];
            }
        }
    }
    else if (ndims == 3) {
        matrix_tri = new double**[filas];
        for (int i=0;i<filas;i++) {
            matrix_tri[i]=new double*[columnas];
            for (int j=0;j<columnas;j++) {
                matrix_tri[i][j]=new double[capa];
                for (int k=0;k<capa;k++) {
                    matrix_tri[i][j][k]=other.matrix_tri[i][j][k];
                }
            }
        }
    }
    return *this;
}
Tensor& Tensor::operator=(Tensor &&other) noexcept {
    cout<< "Asignacion de movimiento\n";
    if (this == &other)return *this;

    if (ndims == 1 ) {
        delete[] vector_d;
    }
    else if (ndims == 2) {
        for (int i=0;i<filas;i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    else if (ndims == 3) {
        for (int i=0;i<filas;i++) {
            for (int j=0;j<columnas;j++) {
                delete[] matrix_tri[i][j];
            }
            delete[] matrix_tri[i];
        }
        delete[] matrix_tri;
    }

    ndims = other.ndims;
    filas = other.filas;
    columnas = other.columnas;
    capa = other.capa;

    vector_d = other.vector_d;
    matrix = other.matrix;
    matrix_tri = other.matrix_tri;

    other.vector_d = nullptr;
    other.matrix = nullptr;
    other.matrix_tri = nullptr;

    other.ndims = 0;
    other.filas = 0;
    other.columnas = 0;
    other.capa = 0;

    return *this;
}

Tensor Tensor::apply(const TensorTransform& transform) const {
    return transform.apply(*this);
}

Tensor ReLU::apply(const Tensor& t) const {

    Tensor result = t;

    if(t.ndims == 1){
        for(int i = 0; i < t.filas; i++)
            result.vector_d[i] = max(0.0, t.vector_d[i]);
    }

    else if(t.ndims == 2){
        for(int i = 0; i < t.filas; i++)
            for(int j = 0; j < t.columnas; j++)
                result.matrix[i][j] = max(0.0, t.matrix[i][j]);
    }

    else if(t.ndims == 3){
        for(int i = 0; i < t.filas; i++)
            for(int j = 0; j < t.columnas; j++)
                for(int k = 0; k < t.capa; k++)
                    result.matrix_tri[i][j][k] =
                        max(0.0, t.matrix_tri[i][j][k]);
    }

    return result;
}
Tensor Sigmoid::apply(const Tensor& t) const {

    Tensor result = t;

    if(t.ndims == 1){
        for(int i = 0; i < t.filas; i++)
            result.vector_d[i] = 1.0 / (1.0 + exp(-t.vector_d[i]));
    }

    else if(t.ndims == 2){
        for(int i = 0; i < t.filas; i++)
            for(int j = 0; j < t.columnas; j++)
                result.matrix[i][j] =
                    1.0 / (1.0 + exp(-t.matrix[i][j]));
    }

    else if(t.ndims == 3){
        for(int i = 0; i < t.filas; i++)
            for(int j = 0; j < t.columnas; j++)
                for(int k = 0; k < t.capa; k++)
                    result.matrix_tri[i][j][k] =
                        1.0 / (1.0 + exp(-t.matrix_tri[i][j][k]));
    }

    return result;
}

Tensor Tensor::operator+(const Tensor& other) const {

    Tensor result = *this;


    if(filas == other.filas && columnas == other.columnas){

        for(int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++){
                result.matrix[i][j] =
                    matrix[i][j] + other.matrix[i][j];
            }
        }
    }


    else if(other.filas == 1 && other.columnas == columnas){

        for(int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++){
                result.matrix[i][j] =
                    matrix[i][j] + other.matrix[0][j];
            }
        }
    }

    else{
        throw runtime_error("Dimensiones incompatibles en suma");
    }

    return result;
}
Tensor Tensor::operator-(const Tensor& other) const {

    Tensor result = *this;

    if(ndims == 1){
        for(int i = 0; i < filas; i++)
            result.vector_d[i] = vector_d[i] - other.vector_d[i];
    }

    else if(ndims == 2){
        for(int i = 0; i < filas; i++)
            for(int j = 0; j < columnas; j++)
                result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
    }

    else if(ndims == 3){
        for(int i = 0; i < filas; i++)
            for(int j = 0; j < columnas; j++)
                for(int k = 0; k < capa; k++)
                    result.matrix_tri[i][j][k] =
                        matrix_tri[i][j][k] - other.matrix_tri[i][j][k];
    }

    return result;
}
Tensor Tensor::operator*(const Tensor& other) const {

    Tensor result = *this;

    if(ndims == 1){
        for(int i = 0; i < filas; i++)
            result.vector_d[i] = vector_d[i] * other.vector_d[i];
    }

    else if(ndims == 2){
        for(int i = 0; i < filas; i++)
            for(int j = 0; j < columnas; j++)
                result.matrix[i][j] = matrix[i][j] * other.matrix[i][j];
    }

    else if(ndims == 3){
        for(int i = 0; i < filas; i++)
            for(int j = 0; j < columnas; j++)
                for(int k = 0; k < capa; k++)
                    result.matrix_tri[i][j][k] =
                        matrix_tri[i][j][k] * other.matrix_tri[i][j][k];
    }

    return result;
}
Tensor Tensor::operator*(double escalar) const {

    Tensor result = *this;

    if(ndims == 1){
        for(int i = 0; i < filas; i++)
            result.vector_d[i] *= escalar;
    }

    else if(ndims == 2){
        for(int i = 0; i < filas; i++)
            for(int j = 0; j < columnas; j++)
                result.matrix[i][j] *= escalar;
    }

    else if(ndims == 3){
        for(int i = 0; i < filas; i++)
            for(int j = 0; j < columnas; j++)
                for(int k = 0; k < capa; k++)
                    result.matrix_tri[i][j][k] *= escalar;
    }

    return result;
}

Tensor Tensor::view(const vector<size_t>& new_shape) const {

    int total_old = filas * columnas * capa;
    int total_new = 1;

    for(size_t x : new_shape)
        total_new *= x;

    if(total_old != total_new)
        throw runtime_error("Error: tamaños incompatibles");

    Tensor result = *this;

    result.filas = new_shape[0];
    result.columnas = (new_shape.size() > 1) ? new_shape[1] : 1;
    result.capa = (new_shape.size() > 2) ? new_shape[2] : 1;
    result.ndims = new_shape.size();

    return result;
}
Tensor Tensor::unsqueeze(int dim) const  {

    Tensor result = *this;

    if(dim == 0){
        result.capa = result.columnas;
        result.columnas = result.filas;
        result.filas = 1;
    }
    else if(dim == 1){
        result.capa = result.columnas;
        result.columnas = 1;
    }

    result.ndims++;

    return result;
}

Tensor Tensor::concat(const vector<Tensor>& tensors, int axis){

    if(tensors.empty())
        throw runtime_error("Error: lista vacía");

    int total_filas = 0;
    int columnas = tensors[0].columnas;

    for(const auto& t : tensors){
        if(t.columnas != columnas)
            throw runtime_error("Error: columnas incompatibles");
        total_filas += t.filas;
    }

    Tensor result = Tensor::zeros({(size_t)total_filas, (size_t)columnas});

    int offset = 0;

    for(const auto& t : tensors){
        for(int i = 0; i < t.filas; i++){
            for(int j = 0; j < columnas; j++){
                result.matrix[offset + i][j] = t.matrix[i][j];
            }
        }
        offset += t.filas;
    }

    return result;
}

Tensor dot(const Tensor& a, const Tensor& b){

    if(a.ndims != 1 || b.ndims != 1)
        throw runtime_error("Error: dot solo para vectores");

    if(a.filas != b.filas)
        throw runtime_error("Error: tamaños distintos");

    double suma = 0;

    for(int i = 0; i < a.filas; i++){
        suma += a.vector_d[i] * b.vector_d[i];
    }

    return Tensor({1}, {suma});
}
Tensor matmul(const Tensor& a, const Tensor& b){

    if(a.ndims != 2 || b.ndims != 2)
        throw runtime_error("Error: matmul solo para matrices");

    if(a.columnas != b.filas)
        throw runtime_error("Error: dimensiones incompatibles");

    Tensor result = Tensor::zeros({(size_t)a.filas, (size_t)b.columnas});

    for(int i = 0; i < a.filas; i++){
        for(int j = 0; j < b.columnas; j++){
            for(int k = 0; k < a.columnas; k++){
                result.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
            }
        }
    }

    return result;
}

void print(Tensor &mat) {
    if(mat.ndims == 1) {
        for(int i = 0; i < mat.filas; i++) {
            cout << mat.vector_d[i] << " ";
        }
        cout << endl;
    }
    else if (mat.ndims == 2) {
        for(int i = 0; i < mat.filas; i++) {
            for(int j = 0; j < mat.columnas; j++) {
                cout << mat.matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    else if (mat.ndims == 3) {
        for(int k = 0; k < mat.capa; k++) {
            cout << "Capa " << k << ":\n";

            for(int i = 0; i < mat.filas; i++) {
                for(int j = 0; j < mat.columnas; j++) {
                    cout << mat.matrix_tri[i][j][k] << " ";
                }
                cout << endl;
            }

            cout << endl;
        }
    }

}
Tensor::~Tensor() {

    if(ndims == 1){
        delete[] vector_d;
    }

    else if(ndims == 2){
        for(int i = 0; i < filas; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    else if(ndims == 3){
        for(int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++){
                delete[] matrix_tri[i][j];
            }
            delete[] matrix_tri[i];
        }
        delete[] matrix_tri;
    }
}
