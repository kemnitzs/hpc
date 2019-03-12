#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "jacobi.h"

/*
 * print result summary
 */
void PrintResults(const JacobiData& data)
{
    if (data.my_rank == 0) {
        std::chrono::duration<double> diff = data.end_timepoint-data.start_timepoint;
        printf(" Number of iterations : %d\n", data.effective_iter_count);
        printf(" Residual             : %le\n", data.residual);
        printf(" Solution Error       : %1.12lf\n", data.calculated_error);
        printf(" Elapsed Time         : %5.7lf\n", diff.count());
        printf(" MFlop/s              : %6.6lf\n", 
            0.000013 * data.effective_iter_count * (data.n_cols - 2) * (data.n_rows - 2)
            / diff.count() );
    	printf(" Flop/LUP	      : %d\n", 13);
	printf(" Byte/LUP	      : %d\n", 32);
	printf(" b_s MB/s	      : %d\n", 40000);
	printf(" P_max LUP/s (single) : %f\n", 40000.0/32.0);
	printf(" P_real LUP/s (/core) : %f\n",data.total/diff.count()/1e6/data.max_threads);
    }
    return;
}

/*
 * Checks error between numerical and exact solution
 */
void CheckError(JacobiData& data)
{
    double error = 0.0;

    for (int j = data.first_row; j <= data.last_row; j++)
    {
        if ((data.my_rank != 0 && j == data.first_row) || 
            (data.my_rank != data.n_processes - 1 && j == data.last_row))
            continue;

        for (int i = 0; i < data.n_cols; i++)
        {
            double xx   = -1.0 + data.dx * i;
            double yy   = -1.0 + data.dy * j;
            double temp = data.get_u(j,i) - (1.0 - xx * xx) * (1.0 - yy * yy);
            error += temp * temp;
        }
    }

    data.calculated_error = sqrt(error) / (data.n_cols * data.n_rows);
        
    return;
}


int main (int argc, char** argv)
{
    int retVal = 0;    /* return value */

    JacobiData myData;
    
    /* starting timer */
    myData.start_timepoint = std::chrono::high_resolution_clock::now();

    /* running calculations */
    myData.run();

    /* stopping timer */
    myData.end_timepoint = std::chrono::high_resolution_clock::now();

    /* error checking */
    CheckError(myData);

    /* print result summary */
    PrintResults(myData);
  
    return retVal;
}
