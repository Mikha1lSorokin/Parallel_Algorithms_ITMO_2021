#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// function to generate random matrices
double** generate_random_matrix(int rows, int columns){
    
    double** matrix = new double*[rows];
        for (int i = 0; i < rows; i++){
            matrix[i] = new double[columns];
        }
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                matrix[i][j] = (double)rand() / RAND_MAX;
            }
        }
    return matrix;
}

// function to make the values of matrix zero
double** null_matrix(int N){
    double** matrix = new double*[N];
        for (int i = 0; i < N; i++){
            matrix[i] = new double[N];
        }
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                matrix[i][j] = 0;
            }
        }
    return matrix;
}

int main(int argc, char** argv){
    if (argc > 2) // if we pass arguments to function, argc will be more than 1 (depends on number of arguments)
    {
        int A =  atoi(argv[1]); // number of rows in matrix
        int B = atoi (argv[2]); // number of columns in matrix
        double **matrix_a, **matrix_b, **matrix_c; // initialize varibles for matrices
        // generate matrix A
        matrix_a = generate_random_matrix(A, B);
        // generate matrix B
        matrix_b = generate_random_matrix(B, A);
        // generate matrix C with zero values
        matrix_c = null_matrix(A);

        int* time_array = new int[10]; // initialize array that will store the execution time of matrix multiplication
        int sum_time = 0;
        //iterate over the number of threads
        for(int thread_num =1; thread_num < 11; thread_num++){
            matrix_c = null_matrix(A);
            auto start = high_resolution_clock::now(); // get the current time
            #pragma omp parallel for num_threads(thread_num)
            for (int i = 0; i < A; i++){
                for (int j = 0; j < A; j++){
                    for (int k = 0; k < B; k++){
                        matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
                    }
                }
            }
            auto stop = high_resolution_clock::now(); // get the stop time
            auto duration = duration_cast<microseconds>(stop - start); // calculate the duration
            time_array[thread_num - 1] = duration.count();
            sum_time += duration.count();
        }
        printf("i-j-k order");
        cout << endl;
        for (int i = 0; i < 10; i++){
            printf("Number of threads: %d, Time (in microseconds): %lld, Efficiency: %f\n", i + 1, time_array[i], float(time_array[i])/float(sum_time));
        }
    cout << endl;
    sum_time = 0;
    //iterate over the number of threads
        for(int thread_num =1; thread_num < 11; thread_num++){
            matrix_c = null_matrix(A);
            auto start = high_resolution_clock::now(); // get the current time
            #pragma omp parallel for num_threads(thread_num)
            for (int i = 0; i < A; i++){
                for (int k = 0; k < A; k++){
                    for (int j = 0; j < B; j++){
                        matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
                    }
                }
            }
            auto stop = high_resolution_clock::now(); // get the stop time
            auto duration = duration_cast<microseconds>(stop - start); // calculate the duration
            time_array[thread_num - 1] = duration.count();
            sum_time += duration.count();
        }
        printf("i-k-j order");
        cout << endl;
        for (int i = 0; i < 10; i++){
            printf("Number of threads: %d, Time (in microseconds): %lld, Efficiency: %f\n", i + 1, time_array[i], float(time_array[i])/float(sum_time));
        }
        cout << endl;
        sum_time = 0;
    //iterate over the number of threads
        for(int thread_num =1; thread_num < 11; thread_num++){
            matrix_c = null_matrix(A);
            auto start = high_resolution_clock::now(); // get the current time
            #pragma omp parallel for num_threads(thread_num)
            for (int j = 0; j < A; j++){
                for (int k = 0; k < A; k++){
                    for (int i = 0; i < B; i++){
                        matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
                    }
                }
            }
            auto stop = high_resolution_clock::now(); // get the stop time
            auto duration = duration_cast<microseconds>(stop - start); // calculate the duration
            time_array[thread_num - 1] = duration.count();
            sum_time += duration.count();
        }
        printf("j-k-i order");
        cout << endl;
        for (int i = 0; i < 10; i++){
            printf("Number of threads: %d, Time (in microseconds): %lld, Efficiency: %f\n", i + 1, time_array[i], float(time_array[i])/float(sum_time));
        }
        cout << endl;
        sum_time = 0;
    //iterate over the number of threads
        for(int thread_num =1; thread_num < 11; thread_num++){
            matrix_c = null_matrix(A);
            auto start = high_resolution_clock::now(); // get the current time
            #pragma omp parallel for num_threads(thread_num)
            for (int j = 0; j < A; j++){
                for (int i = 0; i < A; i++){
                    for (int k = 0; k < B; k++){
                        matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
                    }
                }
            }
            auto stop = high_resolution_clock::now(); // get the stop time
            auto duration = duration_cast<microseconds>(stop - start); // calculate the duration
            time_array[thread_num - 1] = duration.count();
            sum_time += duration.count();
        }
        printf("j-i-k order");
        cout << endl;
        for (int i = 0; i < 10; i++){
            printf("Number of threads: %d, Time (in microseconds): %lld, Efficiency: %f\n", i + 1, time_array[i], float(time_array[i])/float(sum_time));
        }
        cout << endl;
        sum_time = 0;
    //iterate over the number of threads
        for(int thread_num =1; thread_num < 11; thread_num++){
            matrix_c = null_matrix(A);
            auto start = high_resolution_clock::now(); // get the current time
            #pragma omp parallel for num_threads(thread_num)
            for (int k = 0; k < A; k++){
                for (int i = 0; i < A; i++){
                    for (int j = 0; j < B; j++){
                        matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
                    }
                }
            }
            auto stop = high_resolution_clock::now(); // get the stop time
            auto duration = duration_cast<microseconds>(stop - start); // calculate the duration
            time_array[thread_num - 1] = duration.count();
            sum_time += duration.count();
        }
        printf("k-i-j order");
        cout << endl;
        for (int i = 0; i < 10; i++){
            printf("Number of threads: %d, Time (in microseconds): %lld, Efficiency: %f\n", i + 1, time_array[i], float(time_array[i])/float(sum_time));
        }
        cout << endl;
        sum_time = 0;
    //iterate over the number of threads
        for(int thread_num =1; thread_num < 11; thread_num++){
            matrix_c = null_matrix(A);
            auto start = high_resolution_clock::now(); // get the current time
            #pragma omp parallel for num_threads(thread_num)
            for (int k = 0; k < A; k++){
                for (int j = 0; j < A; j++){
                    for (int i = 0; i < B; i++){
                        matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
                    }
                }
            }
            auto stop = high_resolution_clock::now(); // get the stop time
            auto duration = duration_cast<microseconds>(stop - start); // calculate the duration
            time_array[thread_num - 1] = duration.count();
            sum_time += duration.count();
        }
        printf("k-j-i order");
        cout << endl;
        for (int i = 0; i < 10; i++){
            printf("Number of threads: %d, Time (in microseconds): %lld, Efficiency: %f\n", i + 1, time_array[i], float(time_array[i])/float(sum_time));
        }
    }
    else if (argc == 2){
        cout << "You need to pass 2 values for matrix sizes!" << endl;
    }
    else
    {
        cout << "Not arguments were given" << endl;
    }
    return 0;
}