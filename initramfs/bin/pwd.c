// pwd.c
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main(void) {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd))) {
        puts(cwd);
    } else {
        perror("pwd");
        return 1;
    }
    return 0;
}
