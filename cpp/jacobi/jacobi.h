#ifndef _JACOBI_H
#define _JACOBI_H

#include <vector>
#include <chrono>

struct JacobiData
{
    // types
    using time_point = decltype(std::chrono::high_resolution_clock::now());

    // functions
    JacobiData();
    
    auto& get_u( size_t j, size_t i ){
      return U[((j)-first_row) * n_cols + (i)];
    }
    auto& get_f( size_t j, size_t i ){
      return F[((j)-first_row) * n_cols + (i)];
    }

    void init_matrix();

    // data

    /* input data */
    int n_rows;
    int n_cols;
    int first_row;
    int last_row;
    int max_iterations;
    double alpha;
    double relax;
    double tolerance;
    
    /* calculated dx & dy */
    double dx;
    double dy;

    std::vector<double> U;
    std::vector<double> F;


    void run();
    
    /* start and end timestamps */
    time_point start_timepoint;
    time_point end_timepoint;

    /* calculated residual (output jacobi) */
    double residual;
    /* effective interation count (output jacobi) */
    int effective_iter_count;

    /* calculated error (output error_check) */
    double calculated_error;
    
    /* MPI-Variables */
    int my_rank;   /* current process rank (number) */
    int n_processes; /* how many processes */
	
    long total;	
    int max_threads;
};


#endif

