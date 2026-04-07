#  TensorCPP - Biblioteca de Tensores en C++

## Edmundo Andre Centti Torres

Biblioteca de tensores en C++ con soporte para operaciones matemáticas, transformaciones y funciones de activación, inspirada en librerías como NumPy y PyTorch.

---

##  Requisitos

* Compilador C++ compatible con C++11 o superior (g++, clang++, MSVC)
* CMake (opcional)
* CLion u otro IDE compatible con C++

---

##  Estructura del Proyecto

```
TensorCPP/
├── Tensor.h          # Declaración de la clase Tensor
├── Tensor.cpp        # Implementación de métodos
├── main.cpp          # Archivo de pruebas
├── CMakeLists.txt    # Configuración (opcional)
└── README.md
```

---

##  Compilación y Ejecución

### Usando CLion (recomendado)

1. Abrir el proyecto en CLion
2. El IDE detecta automáticamente `CMakeLists.txt`
3. Ejecutar con `Shift + F10`
4. El ejecutable se genera en `cmake-build-debug/`

---


##  Funcionalidades Principales

---

###  Creación de Tensores

```cpp
Tensor A = Tensor::zeros({2, 3});
Tensor B = Tensor::ones({2, 3});
Tensor C = Tensor::random({2, 3}, 0.0, 1.0);
Tensor D = Tensor::arange(0, 5);

Tensor E = Tensor({2, 3}, {1, 2, 3, 4, 5, 6});
// [ 1 2 3 ]
// [ 4 5 6 ]
```

---

###  Operaciones Aritméticas

```cpp
Tensor A = Tensor::random({2, 3}, 0, 1);
Tensor B = Tensor::random({2, 3}, 0, 1);

Tensor C = A + B;
Tensor D = A - B;
Tensor E = A * B;
```

---

###  Broadcasting

```cpp
Tensor A = Tensor({4, 3}, {...});
Tensor B = Tensor({1, 3}, {1, 2, 3});

Tensor C = A + B;
```

✔ Soporta:

* `(n×m) + (1×m)`

---

###  Operaciones Matriciales

```cpp
// Producto punto (vectores)
Tensor A = Tensor::arange(0, 4);
Tensor B = Tensor::arange(0, 4);

Tensor C = dot(A, B);

// Multiplicación matricial
Tensor M1 = Tensor::ones({2, 3});
Tensor M2 = Tensor::ones({3, 2});

Tensor M3 = matmul(M1, M2);
```

---

###  Transformaciones

```cpp
Tensor A = Tensor::arange(0, 6);

Tensor B = A.view({2, 3});
Tensor C = A.unsqueeze(0);

vector<Tensor> lista = {B, B};
Tensor D = Tensor::concat(lista, 0);
```

---

###  Funciones de Activación

```cpp
ReLU relu;
Sigmoid sig;

Tensor A = Tensor::arange(-5, 5);

Tensor B = A.apply(relu);
Tensor C = A.apply(sig);
```

---

##  Pipeline Completo

```cpp
Tensor A = Tensor::random({4,3}, -1, 1);
Tensor W1 = Tensor::random({3,5}, -1, 1);

Tensor Z1 = matmul(A, W1);

ReLU relu;
Tensor A1 = Z1.apply(relu);

Tensor W2 = Tensor::random({5,2}, -1, 1);
Tensor Z2 = matmul(A1, W2);

Sigmoid sig;
Tensor output = Z2.apply(sig);
```

---

##  Notas Importantes

###  Limitaciones

* Soporte máximo: 3 dimensiones
* Tipo de dato: `double`
* Broadcasting limitado

---

###  Gestión de Memoria

La clase implementa:

* Constructor de copia (deep copy)
* Constructor de movimiento
* Operador de asignación
* Destructor para liberar memoria

---

###  Consideraciones

* Las operaciones validan dimensiones antes de ejecutarse
* `view()` no copia datos, solo reorganiza dimensiones
* Se utiliza manejo manual de memoria (new/delete)

---

