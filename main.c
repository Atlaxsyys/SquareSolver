
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void square_solver(float coeff_a, float b, float c, float *x1, float *x2, int *empty_or_infinity);
void output(float x1, float x2, int empty_or_infinity);
bool ravenstvo(float a, float b); 

int main(void)
{
    float coeff_a = 0.0;
    float coeff_b = 0.0;
    float coeff_c = 0.0;
    float x1 = 0.0;
    float x2 = 0.0;
    int empty_or_infinity = -1; // if empty_or_infinity = 0 - There are no solutions; empty_or_infinity = 1 - x ∊ R

    if (scanf("%f %f %f", &coeff_a, &coeff_b, &coeff_c) == 3)
    {
        square_solver(coeff_a, coeff_b, coeff_c, &x1, &x2, &empty_or_infinity);
        output(x1, x2, empty_or_infinity);
    }
    else
    {
        printf("Error: All coefficients are not entered");
    }
    return 0;
}

void square_solver(float coeff_a, float coeff_b, float coeff_c, float *x1, float *x2, int *empty_or_infinity)
{ 
    float discriminant = (coeff_b * coeff_b - 4 * coeff_a * coeff_c);
    float sqrt_of_discriminant = sqrtf(discriminant);
    if (!ravenstvo(coeff_a, 0))
    {
        if (ravenstvo(discriminant, 0))
        {
            *x1 = -coeff_b / (2 * coeff_a);
            *x1 = *x2;
        }
        else if (discriminant > 0)
        {
            *x1 = (-coeff_b - sqrt_of_discriminant)/(2.0 * coeff_a);
            *x2 = (-coeff_b + sqrt_of_discriminant)/(2.0 * coeff_a);
        }
        else if (discriminant < 0)
        {
            *empty_or_infinity = 0;
        }
    }
    else if (ravenstvo(coeff_a, 0) && ravenstvo(coeff_b, 0) && !ravenstvo(coeff_c, 0)) // There are no solutions
    {
        *empty_or_infinity = 0;
    }
    else if (ravenstvo(coeff_a, 0) && !ravenstvo(coeff_b, 0)) // Linear equation - 1 solution
    {
        *x1 = -coeff_c / coeff_b;
        *x1 = *x2;
    }
    else if (ravenstvo(coeff_a, 0) && ravenstvo(coeff_b, 0) && ravenstvo(coeff_c, 0)) // x ∈ R
    {
        *empty_or_infinity = 1;
    }
}

void output(float x1, float x2, int empty_or_infinity)
{
    if (ravenstvo(x1, x2) && empty_or_infinity != 0 && empty_or_infinity != 1)
    {
        printf("%.2f", x1);
    }
    else if (!ravenstvo(x1, x2) && empty_or_infinity != 0 && empty_or_infinity != 1)
    {
        printf("%.2f %.2f", x1, x2);
    }
    else if (empty_or_infinity == 0)
    {
        printf("Нет решений");
    }
    else if (empty_or_infinity == 1)
    {
        printf("x ∈ R");
    }
}   

bool ravenstvo(float a, float b)
{
    double eps = 1e-7;
    return (fabs(a-b) < eps);
}