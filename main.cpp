#include <iostream>
#include <vector>
#include "Tensor.h"

using namespace std;

int main(){
    Tensor A = Tensor::random({4,3}, -1.0, 1.0);
    cout << "Entrada A:\n";
    print(A);

    Tensor W1 = Tensor::random({3,5}, -1.0, 1.0);

    Tensor Z1 = matmul(A, W1);

    Tensor b1 = Tensor::random({1,5}, -1.0, 1.0);

    Z1 = Z1 + b1;

    cout << "\nZ1:\n";
    print(Z1);

    ReLU relu;
    Tensor A1 = Z1.apply(relu);

    cout << "\nA1 (ReLU):\n";
    print(A1);

    Tensor W2 = Tensor::random({5,2}, -1.0, 1.0);

    Tensor Z2 = matmul(A1, W2);

    Tensor b2 = Tensor::random({1,2}, -1.0, 1.0);

    Z2 = Z2 + b2;

    cout << "\nZ2:\n";
    print(Z2);

    Sigmoid sig;
    Tensor output = Z2.apply(sig);

    cout << "\nOutput (Sigmoid):\n";
    print(output);

    return 0;
}