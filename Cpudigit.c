#include<stdio.h>
int main(){
    // 方法一：指针大小
    void* ptr = 0;
    printf("%d\n",sizeof(ptr));
    
    // 方法二：宏定义
    printf("size:%d \n", __WORDSIZE);

    // 方法三：编码方式
    #ifdef __x86_64__
        printf("__x86_64__\n");
    #elif __i386__    
        printf("__i386__\n");
    #endif

    return 0;
}
