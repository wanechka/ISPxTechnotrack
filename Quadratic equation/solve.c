#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

const int Q_FAIL = 42; 


int quadrSolve (double a, double b, double c, double *x1, double *x2);
int isZero (double p); 



int main()
{
	printf ("This is quadratic equation solver!\n");
	printf ("Please, input a, b, c\n");

	double a = 0, b = 0, c = 0;
	scanf ("%lf %lf %lf", &a, &b, &c);

	double x1 = 0, x2 = 0;
	int rootNumber = quadrSolve (a, b, c, &x1, &x2);

	switch (rootNumber)
	{
		case 0:
			printf ("No roots!\n");
			break;
		case 1:
			printf ("%lf is the only root of the given equation\n", x1);
			break;
		case 2:
			printf ("%lf, %lf are roots of the given equation\n", x1, x2);
			break;
		case Q_FAIL:
			printf ("Ooh! Infinite number of roots!\n");
			break;
	}

	return 0;
}

int quadrSolve (double a, double b, double c, double *x1, double *x2)
{
	if (!(isfinite(a)) || !(isfinite(b)) || !(isfinite(c)))
		exit (EXIT_FAILURE);

	assert (x1 != x2);
	assert (x1 != NULL);
	assert (x2 != NULL);

	if (isZero (a))
	{
		if (isZero (b))
		{
			return (isZero (c))? Q_FAIL : 0;
		}
		else
		{
			*x1 = - c / b;

			return 1;
		}
	}

	double discr = b * b - 4 * a * c;

	if (discr > 0)
	{
		*x1 = (-b + sqrt(discr)) / (2 * a);
		*x2 = (-b - sqrt(discr)) / (2 * a);
		
		return 2;
	}
	else if(isZero(discr))
	{
		*x1 = *x2 = - b / (2 * a);

		return 1;
	}
	else
	{
		return 0;
	}
}

int isZero (double p){
	if (p)
		return 0;

	return 1;
}
