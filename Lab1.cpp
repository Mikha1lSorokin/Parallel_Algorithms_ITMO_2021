#include <iostream>
#include <cstdlib>
#include <vector>
#include <omp.h>
#include <chrono>
using namespace std;

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        int vector_length = atoi(argv [1]);
        vector<double> randArray(vector_length);
        for (auto &vec_item: randArray) // Generating random values
        {vec_item = (double)rand() / RAND_MAX;}
        
        // Output the max value if the vector length is 10 (or less) and the 3nd parameter is given
        if (argc > 2 and vector_length <= 10)
        {
            cout<<"Generated elements: ";
            for (auto &vec_item: randArray)
            {
                cout << vec_item << "  ";
            }
            cout << endl;
        }
        // Iterate from 1 to 10 threads
        for(auto thread_num = 1; thread_num < 11; thread_num++)
        {
            double max_val = -1.0;
            auto time_start = chrono::high_resolution_clock::now(); // Start time
#pragma omp parallel for num_threads(thread_num) reduction (max:max_val)
            for (auto i = 0; i < vector_length; i++)
            {
                if (randArray[i] > max_val)
                {
                    max_val = randArray[i];
                }
            }
            auto time_stop = chrono::high_resolution_clock::now(); // Stop time
            auto duration = chrono::duration_cast<chrono::microseconds>(time_stop - time_start);
            cout << "Number of threads:" << thread_num << "  Execution time (in microseconds): " <<  duration.count() << endl;
            if (argc > 2 and vector_length <= 10)
            {
                cout<<"Maximum value: " << max_val << endl;
            }
        }
    }
    else
    {
        cout << "Please input the arguments" << endl;
    }
    return 0;
}