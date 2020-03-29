#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<errno.h>
#include<signal.h>

static void sig_child(int signo);

static void sig_child(int signo){
    pid_t pid;
    int status;
    //处理僵尸进程
    while((pid = waitpid(-1,&status,WNOHANG)) > 0){
        printf("child %d terminated.\n", pid);
    }
}

int main(){
    pid_t pid;
    //创建捕捉子进程信号的机制
    signal(SIGCHLD,sig_child);
    pid = fork();
    if(pid < 0){
        perror("fork error");
        exit(1);
    }
    else if(pid ==  0){
       printf("I am child process,pid id %d.I am exiting.\n",getpid());
       exit(0);
    }
    else{
        printf("I am father process.I will sleep two seconds\n");
        sleep(2);
        printf("father process is exiting.\n");
    }
    return 0;
}
