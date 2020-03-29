#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(){
    pid_t pid = fork();

    if(pid < 0){
        perror("fork error");
        exit(1);
    }
    else if(pid == 0){
        printf("this is a child\n");
        sleep(5);
        printf("child exit\n");
        exit(0);
    }
    else{
        printf("this is a parent\n");
        sleep(20);
        //调用wait函数等待子进程退出
        //获取子进程退出返回值 释放子进程的资源
        wait(NULL);
        printf("parent exit\n");
        exit(0);
    }

    return 0;
}
