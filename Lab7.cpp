#include <iostream>
#include <mpi.h>
#define VEC_SIZE 1000000
using namespace std;

int main(int argc, char **argv)
{
    int proc_rank, proc_num, part_size;
    int root_rank = 0;
    int *vec_a, *vec_b;
    int sum = 0;
    int global_sum = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    
    if (proc_rank == root_rank)
    {
        vec_a = new int[VEC_SIZE];
        vec_b = new int[VEC_SIZE];
        part_size = VEC_SIZE / proc_num;
        for (int i = 0; i < VEC_SIZE; i++)
        {
            vec_b[i] = vec_a[i] = (i / part_size) + 1; // Set 1 to first part, 2 to second, etc
        }
        cout << "Two vectors of 1.000.000 elements were generated." << endl << "These vectors are devided in " << proc_num << 
        " parts, each containing " << part_size << " elements." << endl;
    }
    MPI_Bcast(&part_size, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
    int *vec_a_part = new int[part_size];
    int *vec_b_part = new int[part_size];
    MPI_Scatter(vec_a, part_size, MPI_INT, vec_a_part, part_size, MPI_INT, root_rank, MPI_COMM_WORLD);
    MPI_Scatter(vec_b, part_size, MPI_INT, vec_b_part, part_size, MPI_INT, root_rank, MPI_COMM_WORLD);
    for (int i = 0; i < part_size; i++)
    {
        sum += vec_a_part[i] * vec_b_part[i];
    }
    MPI_Reduce(&sum, &global_sum, 1, MPI_INT, MPI_SUM, root_rank, MPI_COMM_WORLD);
    if (proc_rank == root_rank)
    {
        cout << "Master process " << proc_rank << "; local sum = " << sum  << endl;
        cout << "Master process " << proc_rank << "; TOTAL sum = " << global_sum << endl;
        delete vec_a;
        delete vec_b;
    }
    else
    {
        cout << "Slave process " << proc_rank << "; local sum = " << sum  << endl;
    }
    delete vec_a_part;
    delete vec_b_part;
    MPI_Finalize();
    return 0;
}