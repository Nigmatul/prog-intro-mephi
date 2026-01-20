#include <math.h>

#include "lab1_common.h"
#include "mylib_io.h"

double terms_sum_eps(double x, double eps, int *n) {
    const int p[8] = {1, 1, 0, -1, -1, -1, 0, 1};

    int flag = 1;
    double m = 1, next_m = x, sum = 1 + x;
    *n = 2;

    while (flag) {
        m = next_m;
        next_m = ((*n % 2 == 0) + 1) * next_m * x / *n;

        sum += next_m * p[(*n) % 8];
        flag = (ABS(m - next_m * p[(*n) % 8]) > eps);
        (*n)++;
    }

    return sum;
}

int main() {
    int n = 0;
    double x = 0, eps = 0, sum = 0, actual_value = 0;

    printf("Enter function parameter (X) and precision (EPS): ");
    int flag = ((get_double(&x) == EOF) || (get_double(&eps) == EOF));

    if (flag) {
        printf("\nError: EOF!\n");
        return -1;
    }

    if (ABS(eps) >= 1) {
        printf("Error: EPS is greater than 1!\n");
        return -1;
    }

    if (eps < 0) {
        printf("Warning: You entered negative EPS. \
        Absolute value was taken.\n");
        eps = ABS(eps);
    }

    sum = terms_sum_eps(x, eps, &n);
    actual_value = function_value(x);

    printf("Calculated value = %lf\n", sum);
    printf("Terms summed = %d\n", n);
    printf("Actual value = %lf\n", actual_value);

    return 0;
}
