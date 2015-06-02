all:
	gcc -Wall poisson.c -lgsl -lgslcblas -lm -o poisson

