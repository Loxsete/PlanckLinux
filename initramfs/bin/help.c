// help.c
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main(void) {
    puts("bsh-mini v1.0 - enhanced shell");
    puts("\nBuilt-in commands:");
    puts("  cd [dir]      - change directory (~, -, supported)");
    puts("  exit [code]   - exit shell");
    puts("  pwd           - print working directory");
    puts("  echo [args]   - echo arguments (-n supported)");
    puts("  alias [n=v]   - set/show aliases");
    puts("  unalias name  - remove alias");
    puts("  export VAR=val- set environment variable");
    puts("  unset VAR     - unset variable");
    puts("  history       - show command history");
    puts("  ls [dir]      - list directory");
    puts("  help          - this help");
    puts("  version       - show version");

    puts("\nFeatures:");
    puts("  • Background jobs (&)");
    puts("  • Redirection: < > >>");
    puts("  • Wildcards: * ? [...]");
    puts("  • Aliases");
    puts("  • History");
    puts("  • Tab-like prompt with user@host");

    puts("\nExternal commands in ./cmds/:");
    DIR *d = opendir("./cmds");
    if (!d) {
        perror("opendir");
        return 1;
    }

    struct dirent *e;
    while ((e = readdir(d))) {
        if (e->d_name[0] == '.') continue;

        char path[PATH_MAX];
        snprintf(path, sizeof(path), "./cmds/%s", e->d_name);
        struct stat st;
        if (stat(path, &st) == 0 && (st.st_mode & S_IXUSR)) {
            printf("  %s\n", e->d_name);
        }
    }
    closedir(d);
    return 0;
}
