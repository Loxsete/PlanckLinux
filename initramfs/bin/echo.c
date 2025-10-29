// echo.c
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int no_newline = 0;
    int i = 1;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        no_newline = 1;
        i = 2;
    }

    for (; i < argc; i++) {
        if (i > (no_newline ? 2 : 1)) putchar(' ');
        fputs(argv[i], stdout);
    }

    if (!no_newline) putchar('\n');
    return 0;
}
