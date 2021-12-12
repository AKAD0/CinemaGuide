#include <iostream>
#include <cstdlib>

//creating matrice sample
class data {

private:
    int i, j;

public:
    float** arr;
    int n, m;
    //constructor
    data(int N, int M) {
        std::cout << "Constructor on." << std::endl;

        n = N;
        m = M;
        i = 0;
        j = 0;
        arr = new float* [n];
        for (i = 0; i < n; i++) {
            arr[i] = new float[m];
        }

        std::cout << "Constructor off." << std::endl;
    }

    //methods
    //1) initializing matrice
    void initialize() {
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                arr[i][j] = rand()%12;
            }
        }

    }

    //2) printing matrice
    void printing() {
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                std::cout << arr[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    //destructor
    ~data() {
        std::cout << "Destructor on." << std::endl;

        delete[] arr;

        std::cout << "Destructor off." << std::endl;
    }
};

class preprocessing {

private:
    int i, j, n, m;

public:
    //constructor
    preprocessing() {
        std::cout << "Constructor on." << std::endl;

        i = 0;
        j = 0;

        std::cout << "Constructor off." << std::endl;
    }

    //methods
    //1) outliers delete
    void OutlierDelete(float **mat, int mat_n, int mat_m) {
        n = mat_n;
        m = mat_m;
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                if (mat[i][j] > 10) {
                    mat[i][j] = 0;
                }
            }
        }

    }

    //destructor
    ~preprocessing() {
        std::cout << "Destructor on." << std::endl;
        std::cout << "Destructor off." << std::endl;
    }
};

class recomendation {

private:
    int i, j;

public:
    //constructor
    recomendation() {
        std::cout << "Constructor on." << std::endl;

        i = 0;
        j = 0;

        std::cout << "Constructor off." << std::endl;
    }

    //methods
    //1) CosMeasure
    float CosMVector() {
        // dotProduct(vecA,vecB) / math.sqrt(dotProduct(vecA,vecA)) / math.sqrt(dotProduct(vecB,vecB))
    }

    //destructor
    ~recomendation() {
        std::cout << "Destructor on." << std::endl;
        std::cout << "Destructor off." << std::endl;
    }
};

void main()
{
    //creating matrice sample
    data m1(5,7);
    m1.initialize();
    m1.printing();

    //preprocessing
    preprocessing p1;
    p1.OutlierDelete(m1.arr, m1.n, m1.m);
    m1.printing();

    //
}