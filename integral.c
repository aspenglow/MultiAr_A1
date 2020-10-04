/*
============================================================================
Filename    : integral.c
Author      : Your names goes here
SCIPER		: Your SCIPER numbers
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "function.c"

double integrate (int num_threads, int samples, int a, int b, double (*f)(double));

int main (int argc, const char *argv[]) {

    int num_threads, num_samples, a, b;
    double integral;

    if (argc != 5) {
        num_threads = 1;
        num_samples = 5000000;
        a = 5;
        b = 9;
        // printf("Invalid input! Usage: ./integral <num_threads> <num_samples> <a> <b>\n");
		// return 1;
	} else {
        num_threads = atoi(argv[1]);
        num_samples = atoi(argv[2]);
        a = atoi(argv[3]);
        b = atoi(argv[4]);
	}

    set_clock();

    /* You can use your self-defined funtions by replacing identity_f. */
    integral = integrate (num_threads, num_samples, a, b, identity_f);

    printf("- Using %d threads: integral on [%d,%d] = %.15g computed in %.4gs.\n", num_threads, a, b, integral, elapsed_time());

    return 0;
}


double integrate (int num_threads, int samples, int a, int b, double (*f)(double)) {
    double integral;
    /* Your code goes here */
    //double pixel;
    int i;
    double domain = (double)(b-a);
    rand_gen gen = init_rand();
    double sum = 0;

#pragma omp parallel for num_threads(num_threads) reduction(+:sum) shared(samples) private(i)
    for (i = 0; i < samples; i++) {
        double x = next_rand(gen);
        x = (double)a+ domain * x;
        sum += f(x);
    }
    free_rand(gen);
    integral = sum / (double)samples * domain;
    return integral;
}
