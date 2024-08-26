#include <stdbool.h>
#include <math.h>
#include <assert.h>

enum number_of_roots {
    inf = -1, 
    zero, 
    one, 
    two
};

int square_solver(float coeff_a, float coeff_b, float coeff_c, float *root1, float *root2);
int linear(float coeff_b, float coeff_c, float* root1, float* root2);
bool ravenstvo(float a, float b);
int square(float coeff_a, float coeff_b, float coeff_c, float *root1, float *root2);

bool ravenstvo(float a, float b)
{
    double eps = 1e-7;
    return fabs(a-b) < eps;
}

int linear(float coeff_b, float coeff_c, float* root1, float* root2)
{
    assert(root1 != NULL);
    assert(root2 != NULL);
    assert(root1 != root2);

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

int square(float coeff_a, float coeff_b, float coeff_c, float *root1, float *root2)
{
    assert(root1 != NULL);
    assert(root2 != NULL);
    assert(root1 != root2);
    float discriminant = (coeff_b * coeff_b - 4 * coeff_a * coeff_c);
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


int square_solver(float coeff_a,  float coeff_b, float coeff_c, float *root1, float *root2)
{
    int number_of_roots = 0;
    if (ravenstvo(coeff_a, 0))
    {
        return (number_of_roots += linear(coeff_b, coeff_c, root1, root2));
    }
    else
    {
        return (number_of_roots += square(coeff_a, coeff_b, coeff_c, root1, root2));
    }
}


