#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int
main (int argc, char *argv[])
{
	if(argc != 2) {
		fprintf(stderr, "Usage: %s <numvars>");
		return 1;
		}
	print_numbers(strtol(argv[1], (char **)NULL, 10));
	return 0;
}

void print_numbers(int n)
{
  const gsl_rng_type * T;
  gsl_rng * r;

  int i, n = 10;
  double mu = 50.0;

  /* create a generator chosen by the 
     environment variable GSL_RNG_TYPE */

  gsl_rng_env_setup();

  T = gsl_rng_default;
  r = gsl_rng_alloc (T);

  /* print n random variates chosen from 
     the poisson distribution with mean 
     parameter mu */

  for (i = 0; i < n; i++) 
    {
      unsigned int k = gsl_ran_poisson (r, mu);
      printf (" %u", k);
    }

  printf ("\n");
  gsl_rng_free (r);
  return 0;
}
