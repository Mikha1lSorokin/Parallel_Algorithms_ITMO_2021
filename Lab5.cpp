#include <iostream>
#include "mpi.h"
#include <ctime>
using namespace std;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, n, i, message;
    double time_start, time_finish;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	srand(time(NULL));
	int chosen_thread = (rand() % 7) + 1;

    time_start = MPI_Wtime();

	if (rank == 0)
	{
		MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		cout << "Hello! It's process number " << message << "!\n";
		MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		cout << "My random nonzero integer is: " << message << "\n";
	}

	else if (rank == chosen_thread)
	{
		srand(time(NULL) + rank);
		int nonzero_number = (rand() % 999);
		MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(&nonzero_number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	else 	
	{
		int zero_number = 0;
	}

    time_finish = MPI_Wtime();
	cout << "Process: " << rank << "  time: " << (time_finish - time_start) << endl;

	MPI_Finalize();
	return 0;
}