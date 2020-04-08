#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(){
    // 匿名管道只能用于具有亲缘关系的进程间通信
    // 通过子进程复制父进程的方式来获取管道的操作句柄
    // 创建管道一定要放到子进程之前
    int pipefd[2] = {-1};
    int ret = pipe(pipefd);
    if(ret < 0){
        perror("pipe error");
        return -1;
    }

    pid_t pid = fork();
    if(pid == 0){
        // 子进程从管道读取数据
        char buf[1024] = {0};
        read(pipefd[0], buf, 1023);
        printf("子进程读到的数据：%s", buf);
    }
    else if(pid > 0){
        // 父进程向管道写入数据
        char* ptr = "父进程写入\n";
        write(pipefd[1], ptr, strlen(ptr));
    }

    return 0;
}
