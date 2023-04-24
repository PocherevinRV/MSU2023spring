#include <stdio.h>
#include <math.h>

//double EPS = 1.e-12;
double X_EPS = 1.e-17;
double STEP = 1.e-6;

double integral(double (*func)(double), double left, double right);
double func(double x);

double func(double x)
{
    return x * sin (x * x) +  pow(2, log(x));
}

double integral(double (*func)(double), double left, double right)
{
    double integral_sum = 0.;
    for (double intermediate_point = left + STEP; right - intermediate_point > -X_EPS; left += STEP, intermediate_point += STEP)
        integral_sum += func((left + intermediate_point) / 2) * STEP;
    integral_sum += func((left + right) / 2) * (right - left);
    return integral_sum;    
}

int main(void)
{
    int left, right;
    printf("Enter two numbers: ");
    scanf("%d %d", &left, &right);
    if (left > right)
    {
        printf("\nWrong order of points");
        return 0;
    }
    printf("\nAnswer: %.12lf\n", integral(func, left, right));
}