#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/statvfs.h>
#include <time.h>

#ifdef __linux__
    #include <sys/sysinfo.h>
#elif defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__)
    #include <sys/sysctl.h>
    #include <sys/vfs.h>
#else
    #include <sys/param.h>
    #include <sys/mount.h>
#endif

static void human_size(unsigned long long bytes, char *out, size_t out_size) {
    if (bytes >= 1073741824ULL)
        snprintf(out, out_size, "%.2f GB", (double)bytes / 1073741824.0);
    else if (bytes >= 1048576ULL)
        snprintf(out, out_size, "%.2f MB", (double)bytes / 1048576.0);
    else if (bytes >= 1024ULL)
        snprintf(out, out_size, "%.2f KB", (double)bytes / 1024.0);
    else
        snprintf(out, out_size, "%llu B", bytes);
}

static void get_cpu_model(char *buf, size_t size) {
    FILE *f = fopen("/proc/cpuinfo", "r");
    if (!f) { strncpy(buf, "Unknown", size); return; }

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "model name", 10) == 0) {
            char *colon = strchr(line, ':');
            if (colon) {
                strncpy(buf, colon + 2, size);
                buf[strcspn(buf, "\n")] = '\0';
                fclose(f);
                return;
            }
        }
    }
    fclose(f);
    strncpy(buf, "Unknown", size);
}

static void get_memory(unsigned long long *total, unsigned long long *used) {
    *total = *used = 0;

#ifdef __linux__
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        *total = info.totalram;
        *used  = info.totalram - info.freeram;
        *total *= info.mem_unit;
        *used  *= info.mem_unit;
    }
#elif defined(__FreeBSD__)
    unsigned long long page_size = sysconf(_SC_PAGESIZE);
    int mib[2] = { CTL_HW, HW_PHYSMEM };
    size_t len = sizeof(*total);
    if (sysctl(mib, 2, total, &len, NULL, 0) == 0) {
        *total = page_size * (*total / page_size);
        *used = *total * 0.7;
    }
#else
    *total = 8ULL * 1024 * 1024 * 1024;
    *used  = 4ULL * 1024 * 1024 * 1024;
#endif
}

static void format_uptime(char *buf, size_t size) {
    double uptime_sec = 0;
    FILE *f = fopen("/proc/uptime", "r");
    if (f) {
        fscanf(f, "%lf", &uptime_sec);
        fclose(f);
    }

    int days = (int)(uptime_sec / 86400);
    int hours = ((int)uptime_sec % 86400) / 3600;
    int mins = ((int)uptime_sec % 3600) / 60;

    if (days > 0)
        snprintf(buf, size, "%dd %dh %dm", days, hours, mins);
    else if (hours > 0)
        snprintf(buf, size, "%dh %dm", hours, mins);
    else
        snprintf(buf, size, "%dm", mins);
}

static const char* get_wm() {
    const char *wm = getenv("XDG_CURRENT_DESKTOP");
    if (!wm) wm = getenv("DESKTOP_SESSION");
    if (!wm) wm = "Unknown";
    return wm;
}

static const char* get_terminal() {
    const char *term = getenv("TERM");
    if (!term || strcmp(term, "linux") == 0) {
        term = strrchr(getenv("SSH_TTY"), '/');
        term = term ? term + 1 : "Unknown";
    }
    return term ? term : "Unknown";
}

int main(void) {
    struct utsname uts;
    uname(&uts);

    const char *user = getlogin();
    if (!user) user = getenv("USER");
    if (!user) user = "unknown";

    const char *home = getenv("HOME");
    if (!home) home = "/";

    const char *shell = getenv("SHELL");
    if (!shell) shell = "bsh";

    long cores = sysconf(_SC_NPROCESSORS_ONLN);
    if (cores < 1) cores = 1;

    struct statvfs vfs;
    unsigned long long disk_total = 0, disk_used = 0;
    if (statvfs("/", &vfs) == 0) {
        disk_total = vfs.f_blocks * vfs.f_frsize;
        disk_used  = (vfs.f_blocks - vfs.f_bfree) * vfs.f_frsize;
    }

    unsigned long long mem_total = 0, mem_used = 0;
    get_memory(&mem_total, &mem_used);

    char cpu_model[128] = {0};
    get_cpu_model(cpu_model, sizeof(cpu_model));

    char uptime_str[64] = {0};
    format_uptime(uptime_str, sizeof(uptime_str));

    char disk_used_str[32], disk_total_str[32];
    char mem_used_str[32], mem_total_str[32];
    human_size(disk_used, disk_used_str, sizeof(disk_used_str));
    human_size(disk_total, disk_total_str, sizeof(disk_total_str));
    human_size(mem_used, mem_used_str, sizeof(mem_used_str));
    human_size(mem_total, mem_total_str, sizeof(mem_total_str));

    const char *logo[] = {
        "  ____    _____   _    _ ",
        " | __ )  / ____| | |  | |",
        " |  _ \\ | (___   | |__| |",
        " | |_) | \\___ \\  |  __  |",
        " |____/  |_____/ |_|  |_|",
        NULL
    };

    
    const char *colors[] = {
        "\033[1;31m",
        "\033[1;33m",
        "\033[1;32m",
        "\033[1;36m",
        "\033[1;34m",
        "\033[1;35m",
        "\033[1;37m",
    };

    printf("\033[1;36m");
    for (int i = 0; logo[i]; ++i) {
        printf("%s", logo[i]);

        switch (i) {
            case 0: printf("  \033[0m%s@%s\033[0m\n", user, uts.nodename); break;
            case 1: printf("  \033[0mOS: \033[1;37m%s %s\033[0m\n", uts.sysname, uts.release); break;
            case 2: printf("  \033[0mKernel: \033[1;37m%s\033[0m\n", uts.release); break;
            case 3: printf("  \033[0mCPU: \033[1;37m%s (%ld cores)\033[0m\n", cpu_model[0] ? cpu_model : "Unknown", cores); break;
            case 4: printf("  \033[0mMemory: \033[1;37m%s / %s\033[0m\n", mem_used_str, mem_total_str); break;
            case 5: printf("  \033[0mDisk (/): \033[1;37m%s / %s\033[0m\n", disk_used_str, disk_total_str); break;
            default: printf("\n"); break;
        }
    }
    printf("\033[0m");

    printf("  \033[1;34mUptime:\033[0m %s\n", uptime_str);
    printf("  \033[1;35mShell:\033[0m %s\n", shell);
    printf("  \033[1;32mHome:\033[0m %s\n", home);
    printf("  \033[1;33mWM:\033[0m %s\n", get_wm());
    printf("  \033[1;36mTerminal:\033[0m %s\n", get_terminal());

    printf("\n  ");
    for (int i = 0; i < 7; ++i) {
        printf("%s███", colors[i]);
    }
    printf("\033[0m\n\n");

    return 0;
}
