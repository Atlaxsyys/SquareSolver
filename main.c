
#include <stdio.h>
double st(double base, int power);

int main()
{
    double base = 0;
    int power = 0;
    
    scanf("%lf %d", &base, &power);
    printf("%f", st(base, power));
}

double st(double base, int power)
{
    if (power == 0)
    {
        return 1;
    }
    else if (power % 2 == 1)
    {
        return base * st(base, power - 1);
    }
    else
    {
        return st(base*base, power/2);
    }
}
