
#include <stdio.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file> <string>\n", argv[0]);
        openlog("writer", LOG_PID, LOG_USER);
        syslog(LOG_ERR, "Invalid number of arguments: %d", argc - 1);
        closelog();
        return 1;
    }

    const char *file_path = argv[1];
    const char *write_str = argv[2];

    FILE *fp = fopen(file_path, "w");
    openlog("writer", LOG_PID, LOG_USER);
    if (!fp) {
        syslog(LOG_ERR, "Failed to open file: %s", file_path);
        closelog();
        return 1;
    }

    if (fputs(write_str, fp) == EOF) {
        syslog(LOG_ERR, "Failed to write to file: %s", file_path);
        fclose(fp);
        closelog();
        return 1;
    }

    syslog(LOG_DEBUG, "Writing %s to %s", write_str, file_path);
    fclose(fp);
    closelog();
    return 0;
}



