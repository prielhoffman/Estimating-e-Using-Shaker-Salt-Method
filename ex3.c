#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#define numGrains 100000 //  number of the salt grains
#define numShakes 10000 // number of shaking the grains
#define num_steps 128 // number of steps
#define probability_grain 0.0001 // the probability of a grain to be in the hole (and not on the paper)
#define e_val 2.718281828 // actual value of e

///////// An OpenMP-based parallel computer program that estimate e using the Shaker Salt method /////////

double estimate_e() // this function estimate e using the Shaker Salt method (for one step)
{
	unsigned int seed = time(NULL); // parameter for using rand_r() function (to get correct random number)
	int i=0,j=0,x=0,grains_on_paper=numGrains,grains_in_hole=0; // init the data
	for(i=0;i<numShakes;i++)
	{
		for (j=0;j<grains_on_paper;j++)
		{
			// check if the specific grain is in the hole
			if(((double)rand_r(&seed) / (double)RAND_MAX < probability_grain)) 
			{
				grains_in_hole+=1; // if yes -> count it
			}
		}
		grains_on_paper-=grains_in_hole; // update number of grains on the paper after one iteration of shaking
		grains_in_hole=0; // init grains_in_hole for the next iteration
	}
	return (double)numGrains/(double)grains_on_paper; // return e=all grains/grains that stay on the paper
}

void main() 
{
	int t=0,num_threads_current,run=0;
	double e_final=0,start_time,end_time,elapsed_time,error=0;
	int num_threads[] = {1,2,4,8}; // save all needed amount of threads
	for (; t < 4; t++) // repeat it per every amount of threads we need
	{
		e_final=0; // init the result (from the last run)
		num_threads_current = num_threads[t]; // update number of threads
		omp_set_num_threads(num_threads_current); // update number of threads
		start_time = omp_get_wtime(); // start the timer!
		#pragma omp parallel for reduction(+:e_final) // do it parallel and sum to the e_final variable
		for (run = 0; run < num_steps; run++) 
		{
			e_final+=estimate_e(numGrains, numShakes); // sum results from all the threads
		}
		e_final=e_final/num_steps; // calculate the average 
		end_time = omp_get_wtime(); // stop the timer!
		elapsed_time = end_time - start_time; // calculate the total time
		error = fabs(e_val - e_final); // calculate the error (relative to 2.718281828)
		// print the results:
		printf("Threads: %d\n", num_threads_current);
		printf("Final estimate of e: %f\n", e_final);
		printf("Error: %lf \n", error);
		printf("Elapsed time: %f seconds\n", elapsed_time);
		printf("===============================\n");
	}
}

