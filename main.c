
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

void clean_buffer(void);
int square_solver(float coeff_a, float coeff_b, float coeff_c, float *root1, float *root2);
void output(float root1, float root2, int roots);
bool ravenstvo(float a, float b); 
void input(float *coeff_a, float *coeff_b, float *coeff_c);

enum number_of_roots {inf = -1, zero, one, two};


int main(void)
{
    float coeff_a = 0;
    float coeff_b = 0;
    float coeff_c = 0;
    float root1 = 0;
    float root2 = 0;

    input(&coeff_a, &coeff_b, &coeff_c);
    int roots = square_solver(coeff_a, coeff_b, coeff_c, &root1, &root2);
    output(root1, root2, roots);
    return 0;
}

void clean_buffer(void)
{
    int some_char = 0;
    while ((some_char = getchar()) != '\n' && some_char != EOF);
}

void input(float *coeff_a, float *coeff_b, float *coeff_c)
{
    printf("Enter the coefficients of the quadratic equation a  b  c accordingly\n");
    do 
    {
        int flag = 0;
        int count = 0;
        count = scanf("%f %f %f", coeff_a, coeff_b, coeff_c);
        if (count != 3)
        {
            printf("Incorrect data was entered. Enter only the coefficient\n");
            clean_buffer();
            continue;
        }
        int ch = 0;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            if (!isspace(ch))
            {
                flag++;
                clean_buffer();
                printf("Incorrect data was entered. Enter only the coefficient\n");
                continue;
            }
        }
        if (flag > 0)
            continue;
        break;
    } while (true);
}

int square_solver(float coeff_a, float coeff_b, float coeff_c, float *root1, float *root2)
{
    if (ravenstvo(coeff_a, 0))
    {
        if (ravenstvo(coeff_b, 0))
        {
            return (coeff_c == 0) ? inf : zero;
        }
        else if (!ravenstvo(coeff_b, 0))
        {
            *root1 = -coeff_c / coeff_b;
            *root2 = *root1;
            return one;
        }
    }

    float discriminant = (coeff_b * coeff_b - 4 * coeff_a * coeff_c);
    if (!ravenstvo(coeff_a, 0))
    {
        if (ravenstvo(discriminant, 0))
        {
            *root1 = -coeff_b / (2 * coeff_a);
            *root2 = *root1;
            return one;
        }
        else if (discriminant > 0)
        {
            float sqrt_of_discriminant = sqrtf(discriminant);
            *root1 = (-coeff_b - sqrt_of_discriminant)/(2 * coeff_a);
            *root2 = (-coeff_b + sqrt_of_discriminant)/(2 * coeff_a);
            return two;
        }
        else if (discriminant < 0)
        {
            return zero;
        }
    }
}
void output(float root1, float root2, enum number_of_roots roots)
{
    switch(roots)
    {
        case inf:
            printf("An infinite number of solutions");
            break;
        case zero:
            printf("There are no solution");
            break;
        case one:
            printf("root = %.2f", root1);
            break;
        case two:
            printf("root1 = %.2f root2 = %.2f", root1, root2);
            break;
        default:
            printf("Something was wrong");
    }
}   

bool ravenstvo(float a, float b)
{
    double eps = 1e-7;
    return fabs(a-b) < eps;
}