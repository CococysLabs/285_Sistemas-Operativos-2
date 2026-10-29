#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/syscall.h>

int main(void) {
    printf("padre PID=%d (syscall directa=%ld)\n", getpid(), syscall(SYS_getpid));
    pid_t pid = fork();

    if (pid == 0) {
        printf("hijo PID=%d PPID=%d\n", getpid(), getppid());
        execlp("ls", "ls", "-l", NULL);
        _exit(127);
    }

    int st;
    waitpid(pid, &st, 0);
    printf("hijo %d termino con %d\n", pid, WEXITSTATUS(st));

    return 0;
}