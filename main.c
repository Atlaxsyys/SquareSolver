
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "solver_sq.h"

struct tests
{
    int number_test;
    float coeff_a, coeff_b, coeff_c;
    float root1_exp, root2_exp;
    int nroots_expected;
};

void swap_if(float* a, float* b);
void all_test(void);
void swap(float* a, float* b);
int testing(struct tests data);
void clean_buffer(void);
void output(float root1, float root2, enum number_of_roots roots); 
void input(float *coeff_a, float *coeff_b, float *coeff_c);


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
    assert(coeff_a != NULL);
    assert(coeff_b != NULL);
    assert(coeff_c != NULL); 
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

int testing(struct tests data)
{
    float root1 = 0;
    float root2 = 0;
    int nRoots = square_solver(data.coeff_a, data.coeff_b, data.coeff_c, &root1, &root2);

    swap_if(&root1, &root2);
    swap_if(&data.root1_exp, &data.root2_exp);
    if (ravenstvo(root1, root2))
    {
        root1 = root2;
        double rootexpected = data.root1_exp;
        if (!ravenstvo(nRoots, data.nroots_expected) || !ravenstvo(root1, rootexpected))
        {
            printf("Error test %d: a = %f, b = %f, c = %f, root = %f nRoots = %d\n"
            "Expected: root = %f nRoots = %d\n",
            data.number_test, data.coeff_a, data.coeff_b, data.coeff_c, root1, nRoots,
            rootexpected, data.nroots_expected);
            return 1;
        }
    }
    else if (nRoots != data.nroots_expected || !ravenstvo(root1, data.root1_exp) || !ravenstvo(root2, data.root2_exp))
    {
        printf("Error test: %d: a = %f, b = %f, c = %f, root1 = %f, root2 = %f, nRoots = %f"
        "Expected: root1 = %f, root2 = %f nRoots = %d",
        data.coeff_a, data.coeff_b, data.coeff_c, root1, root2, nRoots,
        data.root1_exp, data.root2_exp, data.nroots_expected);
        return 1;
    }
    else
    {
        return 0;
    }
}

void swap(float* a, float* b)
{   
    float temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;

}

void swap_if(float* a, float* b)
{
    if (*a > *b)
    {
        swap(a, b);
    }
}

int all_tests(void)
{
    struct tests test[6] = {
        {.number_test = 1,
        .coeff_a = 1, .coeff_b = 7, .coeff_c = 6,
        .root1_exp = -6, .root2_exp = -1, .nroots_expected = 2
    },
        {.number_test = 2,
        .coeff_a = 1, .coeff_b = 2, .coeff_c = 1,
        .root1_exp = -1, .root2_exp = -1, .nroots_expected = 1
    },
        {.number_test = 3,
        .coeff_a = 0, .coeff_b = 1, .coeff_c = 1,
        .root1_exp = -1, .root2_exp = -1, .nroots_expected = 1
    },
        {.number_test = 4,
        .coeff_a = 0, .coeff_b = 0, .coeff_c = 0,
        .root1_exp = 0, .root2_exp = 0, .nroots_expected = -1
    },
        {.number_test = 5,
        .coeff_a = 0, .coeff_b = 0, .coeff_c = 5,
        .root1_exp = 0, .root2_exp = 0, .nroots_expected = 0
    },
        {.number_test = 6,
        .coeff_a = 1, .coeff_b = 2, .coeff_c = 3,
        .root1_exp = 0, .root2_exp = 0, .nroots_expected = 0
    }
    };

    int failed = 0;
    int number_of_elements = sizeof(test) / sizeof(test[0]);
    for (int i = 0; number_of_elements > i; i++)
    {
    failed += testing(test[i]);
    }
    return failed;
}