// ls.c
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

static void print_long(const char *path, const char *name) {
    struct stat st;
    char fullpath[PATH_MAX];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, name);

    if (lstat(fullpath, &st) < 0) return;

    char mode[11];
    mode[0] = S_ISDIR(st.st_mode) ? 'd' : S_ISLNK(st.st_mode) ? 'l' : '-';
    mode[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
    mode[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
    mode[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';
    mode[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
    mode[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
    mode[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';
    mode[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
    mode[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
    mode[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';
    mode[10] = '\0';

    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);
    char timebuf[64];
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&st.st_mtime));

    printf("%s %3ld %s %s %6ld %s %s\n",
           mode, (long)st.st_nlink,
           pw ? pw->pw_name : "???",
           gr ? gr->gr_name : "???",
           (long)st.st_size, timebuf, name);
}

int main(int argc, char **argv) {
    int long_format = 0;
    const char *path = ".";
    int i = 1;

    if (argc > 1 && strcmp(argv[1], "-l") == 0) {
        long_format = 1;
        i = 2;
    }
    if (argc > i) path = argv[i];

    DIR *d = opendir(path);
    if (!d) { perror("ls"); return 1; }

    struct dirent *e;
    while ((e = readdir(d))) {
        if (e->d_name[0] == '.') continue;
        if (long_format) {
            print_long(path, e->d_name);
        } else {
            puts(e->d_name);
        }
    }
    closedir(d);
    return 0;
}
