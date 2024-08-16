
#include <stdio.h>
#include <math.h>
void korny(float a, float b, float c);

int main(void)
{
    float a = 0.0;
    float b = 0.0;
    float c = 0.0;

    if (scanf("%f %f %f", &a, &b, &c) == 3)
    {
        korny(a, b, c);
    }
    else
    {
        printf("Ошибка: Не введены все коэффициенты");
    }
    return 0;
}

void korny(float a, float b, float c)
{ 
    float D = 0;
    D = (pow(b, 2) - 4.0*a*c);
    if (a != 0)
    {
        if (D == 0)
        {
            printf("x = %.2f", -b/(2.0*a));
        }
        else if (D > 0)
        {
            printf("x1 = %.2f, x2 = %.2f", (-b + sqrt(D))/(2.0 * a), (-b - sqrt(D))/(2.0 * a));
        }
        else if (D < 0 || b == 0)
        {
            printf("Решений нет");
        }
    }
    else if (a == 0 && b == 0 && c == 0)
    {
        printf("x ∈ R");
    }
    else
    {
        printf("x = %.2f", -c / b);
    }
}
