#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

void sigcb(int signo){
    printf("recv a signal:%d\n",signo);
}

int main(){
    // 信号的自定义回调
    signal(SIGINT, sigcb);
    signal(SIGRTMIN+4, sigcb);
    
    // 定义阻塞信号集合
    sigset_t set;
    sigemptyset(&set);
    sigfillset(&set);

    // 阻塞操作
    sigprocmask(SIG_BLOCK,&set,NULL);
    
    // 等待回车
    printf("press enter continue\n");
    getchar();

    // 解除阻塞
    sigprocmask(SIG_UNBLOCK,&set,NULL);

    // 处理信号
    while(1){
        sleep(1);
    }
    return 0;
}
