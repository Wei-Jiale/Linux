//fork创建子进程

#include<stdio.h>
#include<unistd.h>

int main(){
    printf("---Create child process start---%d\n",getpid());
    pid_t pid;
    pid = fork();

    if(pid < 0){
        //创建失败
        printf("fork error\n");
    }
    else if(pid == 0){
        //子进程创建成功
        printf("This is child：%d---rpid：%d\n",getpid(),pid);
    }
    else{
        //父进程
        printf("This is parents：%d---rpid：%d\n",getpid(),pid);
    }

    printf("---Create child process end---%d\n",getpid());
    return 0;
}


