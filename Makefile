all:
	gcc -Wall stress.c -lgsl -lgslcblas -lm -o stress

