#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


/**
 * @file solve.c
 *
 * @brief Program for solving quadratic equations
 * @brief just input a, b, c coefficients of ax^2 + bx + c = 0
 *
 * @author Ivan V. Tunyov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 8/27/2020
 */


const int Q_FAIL = 42; 


/**
 * This function solves quadratic equation and returns its roots number
 *
 * @param [in]  a a-coeff
 * @param [in]  b b-coeff
 * @param [in]  c c-coeff
 *
 * @param [out] x1 Pointer to the first root
 * @param [out] x2 Pointer to the second root
 *
 * @return Number of solutions
 *
 * @note If solution number is not finite returns Q_FAIL
 */
int quadrSolve (double a, double b, double c, double *x1, double *x2);


/**
 * This function is used for exact doubles comparison with zero
 *
 * @param [in] p double type number
 *
 * @note we are playing with ponters and data representation
 * @return true if p equals 0, false in an another case
 */
bool isZero (double p); 



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
		default:
			printf("Something went wrong...\n");
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

bool isZero (double p)
{
	///Pointer manipulations for bitwise access and zero comparation
	u_int8_t *bytePoint = (u_int8_t*)&p;
	
	for (size_t i = 0; i < sizeof(double); i++)
	{
		u_int8_t byte = bytePoint[i];
		
		for(int bit = 0; bit < 8; bit++)
		{
			if (byte & 1 != 0)
				return false;
			
			byte >>= 1;
		}
	}
	
	return true;
}

