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
int QuadrSolve (double a, double b, double c, double *x1, double *x2);


/**
 * This function is used for exact doubles comparison with zero
 *
 * @param [in] p double type number
 *
 * @note we are playing with ponters and data representation
 * @return true if p equals 0, false in an another case
 */
bool IsZero (double p); 


/**
 * Monkey function serves as a little IQ-test of our users.
 * This method determines user IQ by checking the correctness of input data.
 *
 * @note In a case of failure you will be asked to take part in retake.
 * @note Переэкзаменовки дисциплин кафедры высшей математики пройдут в дистанционном формате 27, 31 августа.
 */
void Monkey();



/**
 * This function is for simple unit testing.
 * Algorithm: solves 15 pseudo-random generated quadratic equation using our program.
 * And compares rightness of resulting roots.
 */
void Testing();



/**
 * Function for generating random double coefficients for test equations.
 * Taken from Eric Roberts' "The Art and Science of C"
 */
double RandomDouble();


/**
 * With given coefficients a, b, c and roots x1, x2 checks the rightness of ax^2 + bx + c = 0 solution
 *
 * @param [in] a a-coefficient
 * @param [in] b b-coefficient
 * @param [in] c c-coefficient
 * 
 * @param [in] x1 root for check
 * @param [in] x2 root for check
 *
 * @return true if x1, x2 are roots, false in an another case
 */
bool QuadrZero (double a, double b, double c, double x1, double x2);


/**
 * This function calculates the value of quadratic function ax^2 + bx + c
 * with given coefficients and in the given point
 *
 * @param [in] a a-coefficient
 * @param [in] b b-coefficient
 * @param [in] c c-coefficient
 *
 * @param [in] x some R value
 *
 * @returns ax^2 + bx + c
 */
double Parabola (double a, double b, double c, double x);



int main()
{
	printf ("This is quadratic equation solver!\n");
	printf ("Please, input a, b, c\n");

	double a = 0, b = 0, c = 0;
	while (scanf ("%lf %lf %lf", &a, &b, &c) != 3)
		Monkey();

	double x1 = 0, x2 = 0;
	int rootNumber = QuadrSolve (a, b, c, &x1, &x2);

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
			printf ("Something went wrong...\n");
	}

	int answer = -1;
	printf ("Would you like to see our unit tests? (1 or 0) \n");

	while (scanf ("%d", &answer) != 1)
		Monkey();

	switch (answer)
	{
		case 0:
			printf ("OK! Goodbye!\n");
			break;
		case 1:
			printf ("OK! Let`s start\n");
			Testing();
			break;
		default:
			printf("I don`t understand you\n");
	}
	

	return 0;
}

int QuadrSolve (double a, double b, double c, double *x1, double *x2)
{
	if (!(isfinite (a)) || !(isfinite (b)) || !(isfinite (c)))
		exit (EXIT_FAILURE);

	assert (x1 != x2);
	assert (x1 != NULL);
	assert (x2 != NULL);

	if (IsZero (a))
	{
		if (IsZero (b))
		{
			return (IsZero (c))? Q_FAIL : 0;
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
	else if (IsZero (discr))
	{
		*x1 = *x2 = - b / (2 * a);

		return 1;
	}
	else
	{
		return 0;
	}
}

bool IsZero (double p)
{
	///Pointer manipulations for bitwise access and zero comparation
	u_int8_t *bytePoint = (u_int8_t*)&p;
	
	for (size_t i = 0; i < sizeof (double); i++)
	{
		u_int8_t byte = bytePoint[i];
		
		for (int bit = 0; bit < 8; bit++)
		{
			if (byte & 1 != 0)
				return false;
			
			byte >>= 1;
		}
	}
	
	return true;
}

void Monkey()
{
	while (getchar() != '\n');
	printf ("Incorrect input. Please, try again \n");
}

double RandomDouble()
{
	double law = -7, high = 7;

	double random = (double) rand() / ((double) RAND_MAX + 1);

	return random;


}

double Parabola (double a, double b, double c, double x)
{
	double value = a * x * x + b * x + c;

	return value;
}

bool QuadrZero (double a, double b, double c, double x1, double x2)
{
	if ( (Parabola (a, b, c, x1) == 0) && (Parabola (a, b, c, x2) == 0))
		return true;
	
	return false;
}

void Testing()
{
	for (int i = 0; i < 20; i++)
	{
		double a = RandomDouble();
		double b = RandomDouble();
		double c = RandomDouble();
		
		double x1 = 0, x2 = 0;
		int testSolNumb = QuadrSolve (a, b, c, &x1, &x2);
		
		printf ("For a = %lf, b = %lf, c = %lf coefficients\n", a, b, c);

		switch (testSolNumb)
		{
			case 0:
				printf ("No roots\n");

                                ///We can be sure in this result because the sign and value of the discriminant is calculated exactly
                                printf ("Test passed\n");
                                break;

                        case Q_FAIL:
                                printf ("Infinite solution number\n");
                                printf ("Test passed\n");
				break;

                        default:
				printf ("root1 = %lf, root2 = %lf\n", x1, x2);

                                if (QuadrZero (a, b, c, x1, x2))
                                {
                                        printf ("Test passed!\n \n");
                                }
                                else
                                {
                                        printf ("Failed\n");
                                }
                }

        }
}

