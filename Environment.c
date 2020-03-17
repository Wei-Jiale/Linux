//在代码中访问环境变量
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

// 程序运行参数可以通过main函数的参数传入
// argc：表示参数个数 *argv存储参数信息 *env：保存环境变量
int main(int argc, char *argv[], char *env[]){
    int i = 0;
    for(i = 0; i < argc; i++){
        printf("argv[%d] = [%s]\n",i,argv[i]);
    }
    // 1.main中第三个参数保存环境变量
    for(i = 0; env[i] != NULL; i++){
        printf("env[%d] = [%s]\n",i,env[i]);
    }
    
    // 2.声明全局变量
    //extern char **environ;
    //for(i = 0; environ[i] != NULL; i++){
    //    printf("environ[%d] = [%s]\n",i,environ[i]);
    //}
    
    // 3.通过环境变量的名称获取指定环境变量的数据
    // char *ptr = getenv("name");
    // if(ptr != NULL){
    //      printf("%s\n",ptr);
    // }
    // else{
    //     printf("not found");
    // }
    
    return 0;
}
