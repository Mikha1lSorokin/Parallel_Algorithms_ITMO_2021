#include <iostream>
#include <iomanip>
#include <mpi.h>
using namespace std;
void send_int_arr(int src, int dest, int size, int *arr, MPI_Status status, int n_times)
{
    int L = size * sizeof(int);
    double start, end, T, R, s;
    start = MPI_Wtime();
    for (int i = 0; i < n_times; i++)
    {
        MPI_Send(arr, size, MPI_INT, dest, 0, MPI_COMM_WORLD);
    }
    end = MPI_Wtime();
    T = (end - start) * 1000000;
    if (size > 0)
    {
        R = (2 * L * n_times) / (T * 1024 * 1024);
        cout << "Process " << right << src << " sends; message size = " << setw(7) << size <<
        "; average time = " << setw(8) <<  T/n_times << " [us]; bandwidth = " << setw(8) << left << R << " [MB/s]." << endl;
    }
    else
    {
        s = T / (2 * n_times);
        cout << "Process " << right << src << " sends; message size = " << setw(7) << size <<
        "; average time = " << setw(8) <<  T/n_times << " [us]; latency = " << setw(8) << left << s << " [us]." << endl;
    }

}

void recv_int_arr(int src, int dest, int size, int *arr, MPI_Status status, int n_times)
{
    for (int i = 0; i < n_times; i++)
    {
        MPI_Recv(arr, size, MPI_INT, dest, 0, MPI_COMM_WORLD, &status);
    }
}

int main(int argc, char **argv)
{
    int rank, size, n_times = 10;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    for (int message_size = 0; message_size <= 1000000; message_size *= 10)
    {
        int *arr = new int[message_size]();
        if (rank == 0)
        {
            for (int i = 0; i < message_size; i++)
            {
                arr[i] = 1;
            }
            send_int_arr(0, 1, message_size, arr, status, n_times);
            recv_int_arr(0, 1, message_size, arr, status, n_times);
        }
        else if (rank == 1)
        {
            recv_int_arr(1, 0, message_size, arr, status, n_times);
            send_int_arr(1, 0, message_size, arr, status, n_times);
        }
        delete arr;
        if (message_size == 0)
        {
            message_size = 1;
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}