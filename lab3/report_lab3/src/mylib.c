#include <stdio.h>
#include <math.h>


#define myabs(x) ((x) > 0 ? (x) : -(x))

double terms_sum_n(double x, int n);
double terms_sum_eps(double x, double eps, int* n);

double function_value(double x);
int get_double(double* x);
int get_int(int* x);


double 
terms_sum_n(double x, int n) {
    const int p[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    double m = 1, sum = 1;

    for (int i = 1; i < n; ++i) {
        m = ((i % 2 == 0) + 1) * m * x / i;
        sum += m * p[i % 8];
    }

    return sum;
}


double 
terms_sum_eps(double x, double eps, int* n) {
    const int p[8] = {1, 1, 0, -1, -1, -1, 0, 1};

    int flag = 1;
    double m = 1, next_m = x, sum = 1 + x;
    *n = 2;

    while (flag) {
        m = next_m;
        next_m = ((*n % 2 == 0) + 1) * next_m * x / *n;

        sum += next_m * p[(*n) % 8];
        flag = (myabs(m - next_m * p[(*n) % 8]) > eps);
        (*n)++;
    }
    
    return sum;
}


double 
function_value(double x) {
    return exp(x) * cos(x);
}


int
get_double(double* x) {
    int assigned = 0;
    while (!assigned) {
        int input = scanf("%15lf", x);
        scanf("%*[^ \t\n]");

        if (input == EOF) {
            return EOF;
        } else if (input == 1) {
            assigned = 1;
        } else if (input == 0) {
            printf("Error: incorrect input. Try again: ");
            scanf("%*[^\n]");
        }
    }
    return 1;
}


int
get_int(int* x) {
    int assigned = 0;
    while (!assigned) {
        int input = scanf("%9d", x);
        scanf("%*[^ \t\n]");

        if (input == EOF) {
            return EOF;
        } else if (input == 1) {
            assigned = 1;
        } else if (input == 0) {
            printf("Error: incorrect input. Try again: ");
            scanf("%*[^\n]");
        }
    }
    return 1;
}