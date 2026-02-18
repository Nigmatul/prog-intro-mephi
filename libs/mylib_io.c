#include <stdio.h>

#include "iolib.h"

int get_double(double *x) {
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

int get_int(int *x) {
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
