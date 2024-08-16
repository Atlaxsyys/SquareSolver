
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
void square_solver(float a, float b, float c, float *x1, float *x2, int *flag);
void output(float x1, float x2, int flag);
bool ravenstvo(float a, float b); 

int main(void)
{
    float a = 0.0;
    float b = 0.0;
    float c = 0.0;
    float x1 = 0.0;
    float x2 = 0.0;
    int flag = -1; // if flag = 0 - There are no solutions; flag = 1 - x ∊ R

    if (scanf("%f %f %f", &a, &b, &c) == 3)
    {
        square_solver(a, b, c, &x1, &x2, &flag);
        output(x1, x2, flag);
    }
    else
    {
        printf("Error: All coefficients are not entered");
    }
    return 0;
}

void square_solver(float a, float b, float c, float *x1, float *x2, int *flag)
{ 
    float discriminant = 0;
    discriminant = (b*b - 4.0*a*c);
    if (a != 0)
    {
        if ((ravenstvo(discriminant, 0)))
        {
            *x1 = *x2 = -b / 2.0*a;
        }
        else if (discriminant > 0)
        {
            *x1 =(-b - sqrt(discriminant))/(2.0 * a);
            *x2 = (-b + sqrt(discriminant))/(2.0 * a);
        }
        else if (discriminant < 0)
        {
            *flag = 0;
        }
    }
    else if (a == 0 && b == 0 && c != 0) // There are no solutions
    {
        *flag = 0;
    }
    else if (a == 0 && b != 0) // Linear equation - 1 solution
    {
        *x1 = *x2 = -c / b;
    }
    else if (a == 0 && b == 0 && c == 0) // x ∈ R
    {
        *flag = 1;
    }
}

void output(float x1, float x2, int flag)
{
    if (x1 == x2 && flag != 0 && flag != 1)
    {
        printf("%.2f", x1);
    }
    else if (x1 != x2 && flag != 0 && flag !=1)
    {
        printf("%.2f %.2f", x1, x2);
    }
    else if (flag == 0)
    {
        printf("Нет решений");
    }
    else if (flag == 1)
    {
        printf("x ∈ R");
    }
}   

bool ravenstvo(float a, float b)
{
    double eps = 1e-7;
    return (fabs(a-b) < eps);
}