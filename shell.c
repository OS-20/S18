#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

void listFiles(char *dirname) {
    DIR *d = opendir(dirname);
    if (!d) { perror("Cannot open directory"); return; }
    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(d);
}

int main() {
    char input[100], *arg[5];

    while (1) {
        printf("myshell$ ");
        if (!fgets(input, sizeof(input), stdin)) break;

        int i = 0;
        arg[i] = strtok(input, " \t\n");
        if (!arg[i]) continue;
        while ((arg[++i] = strtok(NULL, " \t\n")));

        if (!strcmp(arg[0], "exit")) break;
        else if (!strcmp(arg[0], "list") && arg[1] && arg[2] && arg[1][0]=='f')
            listFiles(arg[2]);
        else {
            if (fork() == 0) {
                execvp(arg[0], arg);
                perror("Command failed");
                exit(1);
            } else wait(NULL);
        }
    }
    return 0;
}
