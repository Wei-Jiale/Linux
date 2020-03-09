#include <stdio.h>
#include <unistd.h>
int main()
{
    int i = 0;
    char bar[101] = {'\0'};
    const char *lable = "|-\\";
    for( ;i<=100;i++ )
    {
        printf("[%-100s][%d\%][%c]\r",bar,i,lable[i%4]);
        fflush(stdout);
        bar[i] = '#';
        usleep(100000);     
    }
    printf("\n");
    return 0;
}
