#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

static void sighandler(int sig) {
    if (sig == SIGINT) {
        int file = open("SIGINTSTOP", O_CREAT | O_WRONLY, 0644);
        char *msg = "This program exited due to a SIGINT\0";
        write(file, msg, strlen(msg));
        exit(0);
    }
    else if (sig == SIGUSR1) {
        printf("PPID: %d\n", getppid());
    }
}


int main() {
    umask(0);
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);
    while(1) {
        printf("PID: %d\n", getpid());
        sleep(1);
    }


    return 0;
}