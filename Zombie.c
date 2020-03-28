#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    // 1.创建一个子进程
    pid_t pid = fork();

    if(pid > 0){
        // 2.父进程
        printf("this is a parent process\n");
        sleep(60);
        printf("parent exit\n");
    }
    else if(pid == 0){
        // 3.子进程
        printf("this is a child process exit\n");
        exit(0);
    }
    else{
        printf("fork error\n");
    }

    return 0;
}
