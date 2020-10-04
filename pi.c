/*
============================================================================
Filename    : pi.c
Author      : Your names goes here
SCIPER		: Your SCIPER numbers
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

double calculate_pi (int num_threads, int samples);

int main (int argc, const char *argv[]) {

    int num_threads, num_samples;
    double pi;

    if (argc != 3) {
        num_threads = 4;
        num_samples = 500000;
		//printf("Invalid input! Usage: ./pi <num_threads> <num_samples> \n");
		//return 1;
	} else {
        num_threads = atoi(argv[1]);
        num_samples = atoi(argv[2]);
	}

    set_clock();
    pi = calculate_pi (num_threads, num_samples);

    printf("- Using %d threads: pi = %.15g computed in %.4gs.\n", num_threads, pi, elapsed_time());

    return 0;
}


double calculate_pi (int num_threads, int samples) {
    double pi;
    /* Your code goes here */

    int i;
    int count = 0;
    rand_gen gen;
    omp_set_num_threads(num_threads);

#pragma omp parallel reduction(+:count)  private(i)
    gen = init_rand();
#pragma omp for

    for (i = 0; i < samples; i++) {
        double x = next_rand(gen);
        double y = next_rand(gen);
        if (x * x + y * y <= 1) {
            count++;
        }
    }
    free_rand(gen);
    pi = (double)count / samples * 4;
    return pi;
}
