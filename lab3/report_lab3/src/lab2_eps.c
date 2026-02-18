#include "mylib.c"

int 
main() {
    int n = 0;
    double x = 0, eps = 0, sum = 0, actual_value = 0;

    printf("Enter function parameter (X) and precision (EPS): ");
    int flag = ((get_double(&x) == EOF) || (get_double(&eps) == EOF));

    if (flag) {
        printf("\nError: EOF!\n");
        return -1;
    }

    if (myabs(eps) >= 1) {
        printf("Error: EPS is greater than 1!\n");
        return -1;
    }

    if (eps < 0) {
        printf("Warning: You entered negative EPS. \
        Absolute value was taken.\n");
        eps = myabs(eps);
    }

    sum = terms_sum_eps(x, eps, &n);
    actual_value = function_value(x);

    printf("Calculated value = %lf\n", sum);
    printf("Terms summed = %d\n", n);
    printf("Actual value = %lf\n", actual_value);

    return 0;
}