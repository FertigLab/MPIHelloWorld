#include <mpi.h>
#include <stdio.h>
#include <Rcpp.h>

// [[Rcpp::export]]
void Hello_cpp()
{
    int world_size, world_rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);
    MPI_Finalize();
    //Rprintf("Hello World\n");
}
