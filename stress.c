#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#define PERIOD_IN_US 2000

int stress_cpu(float, float);
// return difference of two timevals in microseconds
int timeval_diff(struct timeval start, struct timeval end) {
	return (end.tv_sec - start.tv_sec)*1000000+(end.tv_usec - start.tv_usec);
}

gsl_rng *init_rand() {
	const gsl_rng_type * T;
	gsl_rng * r;

	/* create a generator chosen by the 
	   environment variable GSL_RNG_TYPE */

	gsl_rng_env_setup();

	T = gsl_rng_default;
	r = gsl_rng_alloc (T);
	return r;
}

int main(int argc, char *argv[]) {
	if(argc != 3) {
		fprintf(stderr, "Usage: %s <percentage_busy_avg> <total_time_sec>", argv[0]);
		return 1;
	}
	gsl_rng *random_generator = init_rand();
	float expectation = strtof(argv[1], NULL);
	float total_time_sec = strtof(argv[2], NULL);
	// TODO test cpu_percentage for NAN or so (http://www.cplusplus.com/reference/cstdlib/strtof/)

	// forever 
	while(1) {
		float cpu_percentage = gsl_ran_poisson (random_generator, expectation);
		printf("Stressing CPU with %.1f%% for %.0f seconds\n", cpu_percentage, total_time_sec);

		if(!stress_cpu(cpu_percentage, total_time_sec*1000000)) {
			return 1;
		}

	}
	gsl_rng_free (random_generator);

	return 0;
}

int stress_cpu(float cpu_percentage, float total_time_usec) {
	struct timeval tv_func_start;
	if(gettimeofday(&tv_func_start, NULL) != 0) {
		fprintf(stderr, "Error getting time of day");
		return 0;
	}

	float busy_time = PERIOD_IN_US * cpu_percentage / 100.0;
	struct timeval tv_start, tv_end;
	do {
		if(gettimeofday(&tv_start, NULL) != 0) {
			fprintf(stderr, "Error getting time of day");
			return 0;
		}
		do {
			if(gettimeofday(&tv_end, NULL) != 0) {
				fprintf(stderr, "Error getting time of day");
				return 0;
			}
		} while(timeval_diff(tv_start, tv_end) < busy_time);

		// wait the rest of the time
		usleep(PERIOD_IN_US - busy_time);
	} while(timeval_diff(tv_func_start, tv_end) < total_time_usec);
	return 1;
}


