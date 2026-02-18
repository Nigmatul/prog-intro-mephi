#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int
get_size(size_t* x) {
    int assigned = 0;
    while (!assigned) {
        int input = scanf("%10u", x);
        scanf("%*[^ \t\n]");

        if (input == EOF) {
            return EOF;
        } else if (input == 1) {
            assigned = 1;
        } else if (input == 0) {
            printf("<Error> Incorrect input. Try again: ");
            scanf("%*[^\n]");
        }
    }

    return EXIT_SUCCESS;
}

int main()
{ 
	char *a;
	scanf("%s", a);
	printf("%s\n", a);

    return 0;
}
