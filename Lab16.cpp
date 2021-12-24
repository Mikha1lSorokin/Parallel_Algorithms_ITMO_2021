#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int proc_rank, size, rank1, rank2, rank3;
    MPI_Init(&argc, &argv);
    MPI_Comm comm_revs;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    int root_rank = 0;
    if (root_rank == proc_rank)
    {
        printf("Setting color to (1)\n");
    }
    MPI_Comm_split(MPI_COMM_WORLD, 1, size - proc_rank, &comm_revs);
    MPI_Comm_rank(comm_revs, &rank1);
    printf("rank = %d, rank1 = %d\n", proc_rank, rank1);
    MPI_Comm_free(&comm_revs);
    sleep(1);
    if (root_rank == proc_rank)
    {
        printf("Setting color to (rank %% 2)\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Comm_split(MPI_COMM_WORLD, proc_rank % 2, size - proc_rank, &comm_revs);
    MPI_Comm_rank(comm_revs, &rank2);
    printf("rank = %d, rank2 = %d\n", proc_rank, rank2);
    MPI_Comm_free(&comm_revs);
    sleep(1);
    if (root_rank == proc_rank)
    {
        printf("Setting color to (rank %% 3)\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Comm_split(MPI_COMM_WORLD, proc_rank % 3, size - proc_rank, &comm_revs);
    MPI_Comm_rank(comm_revs, &rank3);
    printf("rank = %d, rank3 = %d\n", proc_rank, rank3);
    MPI_Comm_free(&comm_revs);
    MPI_Finalize();
}