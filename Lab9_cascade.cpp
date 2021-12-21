#include <iostream>
#include <mpi.h>
#define VEC_SIZE 1000000
using namespace std;

int main(int argc, char **argv)
{
    int rank, threads_num, part_size;
    MPI_Status status;
    double time_start, time_stop;
    int master_rank = 0;
    int *base_arr;
    int *arr_part;
    int loc_sum = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &threads_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == master_rank)
    {
        base_arr = new int[VEC_SIZE];
        for (int i = 0; i < VEC_SIZE; i++)
        {
            base_arr[i] = 1;
        }
        part_size = VEC_SIZE / threads_num;
    }
    MPI_Bcast(&part_size, 1, MPI_INT, master_rank, MPI_COMM_WORLD);
    arr_part = new int[part_size]();
    MPI_Scatter(base_arr, part_size, MPI_INT, arr_part, part_size, MPI_INT, master_rank, MPI_COMM_WORLD);

    for (int i = 0; i < part_size; i++)
    {
        loc_sum += arr_part[i];
    }
    
    if (rank == master_rank)
    {
        time_start = MPI_Wtime();
    }

    for (int reduce_order = 2, recv_val; reduce_order <= threads_num; reduce_order *= 2)
    {
        if (rank % reduce_order == 0)
        {
            if (rank + reduce_order / 2 < threads_num)
            {
                MPI_Recv(&recv_val, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                loc_sum += recv_val;
                printf("Slave process %d (reduce order = %d): I received the sum = %d from the slave process %d, my local sum = %d\n", rank, reduce_order, recv_val, status.MPI_SOURCE, loc_sum);
            }
        }
        else
        {
            MPI_Send(&loc_sum, 1, MPI_INT, rank - (rank % reduce_order), 0, MPI_COMM_WORLD);
            break;
        }
    }

    if (rank == master_rank)
    {
        time_stop = MPI_Wtime();
        printf("Master process %d: TOTAL SUM = %d\n", rank, loc_sum);
        printf("Merging took: %.0f [us]\n", (time_stop - time_start) * 1000000);
    }
    MPI_Finalize();
    return 0;
}