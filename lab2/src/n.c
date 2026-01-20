#include <math.h>

#include "lab2_common.h"
#include "mylib.c"

double terms_sum_n(double x, int n) {
    const int p[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    double m = 1, sum = 1;

    for (int i = 1; i < n; ++i) {
        m = ((i % 2 == 0) + 1) * m * x / i;
        sum += m * p[i % 8];
    }

    return sum;
}

int main() {
    int n = 0;
    double x = 0, sum = 0, actual_value = 0;

    printf("Enter function parameter (X) and number of terms (N): ");
    int flag = ((get_double(&x) == EOF) || (get_int(&n) == EOF));

    if (flag) {
        printf("\nError: EOF!\n");
        return -1;
    }

    if (n < 0) {
        printf("Warning: You entered negative N. \
        Absolute value was taken.\n");
        n = ABS(n);
    }

    sum = terms_sum_n(x, n);
    actual_value = function_value(x);

    printf("Calculated value = %lf\n", sum);
    printf("Actual value = %lf\n", actual_value);

    return 0;
}
