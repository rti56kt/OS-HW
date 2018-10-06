#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t pid;

    printf("Main process id : %d\n", getpid());

    pid = fork(); // fork 1

    if(pid == 0){
        printf("Fork1, I'm the child %d, my parent is %d\n", getpid(), getppid());

        pid = fork(); // fork 2

        if(pid == 0) printf("Fork2, I'm the child %d, my parent is %d\n", getpid(), getppid());
        else wait(NULL);
    }else wait(NULL);

    pid = fork(); // fork 3

    if(pid == 0) printf("Fork3, I'm the child %d, my parent is %d\n", getpid(), getppid());
    else wait(NULL);
    exit(0);
}