//守护进程的实现
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>

void mydeamon(){
    // 1.重设文件权限 守护进程创建最高的文件权限
    umask(0);

    // 创建子进程 退出父进程 使子进程成为孤儿进程
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(1);
    }

    if(pid > 0){
        // 2.父进程退出 子进程成为孤儿进程
        // 2.让出shell执行其它命令 保证子进程不是组长进程
        exit(0);
    }

    // 3.子进程创建一个新的会话 脱离终端控制
    pid_t sid = setsid();
    if(sid < 0){
        perror("setsid");
        exit(2);
    }

    // 4.改变根目录
    chdir("/");

    // 5.关闭文件描述符
    close(0);
    close(1);
    close(2);

    // 6.捕捉SIGCHLD信号 守护进程创建子进程 子进程退出得回收资源
    signal(SIGCHLD,SIG_IGN);
}

int main(){
    mydeamon();
    // 方便查看守护进程被创建
    while(1);

    return 0;
}
