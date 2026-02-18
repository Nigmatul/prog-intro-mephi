#include <stdio.h>
#define abs(x) ((x) > 0 ? (x) : -(x))

int reverse(int x);
int getint(int *n);
int sum(int x, int *digits);

int main()
{
    int n = 0, r = 0, l = 0, sum_l = 0, sum_r = 0;

    printf("Warning: you can enter only 9-digit integers.\n"); 
    printf("Enter N, R and L to calculate sum of R low and L high \
    digits of the number N: \n"); 

    int flag = ((getint(&n) == EOF) || (getint(&r) == EOF) || (getint(&l) == EOF)); 
    
    if (flag)
    {
        printf("\nError: EOF\n"); return -1;
    }

    /* printf(”N = %d, R = %d L = %d\n”, n, r, l); */
    
    if (n < 0 || r < 0 || l < 0)
    {
        printf("Warning: You entered negative N, R or L. \
        Absolute value was taken.\n"); 
        n = abs(n); 
        r = abs(r); 
        l = abs(l);
    }

    sum_r = sum(n, &r); 
    n = reverse(n); 
    sum_l = sum(n, &l);

    if (r != 0)
    {
        printf("Warning: N has fewer digits than R. \
        Sum of all digits was calculated.\n");
    }

    if (l != 0)
    {
        printf("Warning: N has fewer digits than L. \
        Sum of all digits was calculated.\n");
    }

    printf("Sum of R digits is equal to: %d\n", sum_r); 
    printf("Sum of L digits is equal to: %d\n", sum_l);

    return 0;
}


int getint(int *n)
{
    int assigned = 0; 
    while (!assigned) {
        int input = scanf("%9d", n); 
        scanf("%*[^ \t\n]"); 

        if (input == EOF) {
            return EOF;
        } 
        else if (input == 1) {
            assigned = 1;
        } 
        else if (input == 0) {
            printf("Error: incorrect input. Try again: "); scanf("%*[^\n]");
        }
    }
    return 1;
}


int reverse(int x)
{
    int result = 0;

    while (x > 0)
    {
        result = result * 10 + x % 10; 
        x /= 10;
    }

    return result;
}


int sum(int x, int *digits) {
    int result = 0;

    while (x > 0 && (*digits) > 0) {
        result += x % 10; 
        x /= 10;
        (*digits) -= 1;
    }

    return result;
}