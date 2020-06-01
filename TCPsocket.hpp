#include<cstdio>
#include<string>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
using namespace std;
#define MAX_LISTEN 5
class TCPsocket{
public:
    // 构造函数
    TCPsocket()
        :_sockfd(-1)
    {}

    // 1.创建套接字
    bool Socket(){
        _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(_sockfd < 0){
            perror("socket error");
            return false;
        }
        return true;
    }

    // 2.为套接字绑定地址信息
    bool Bind(const string& ip, uint16_t port){
        // 组织地址结构IPV4
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        socklen_t len = sizeof(struct sockaddr_in);
        int ret = bind(_sockfd, (struct sockaddr*)&addr, len);
        if(ret < 0){
            perror("bind error");
            return false;
        }
        return true;
    }

    // 3.开始监听
    bool Listen(int backlog = MAX_LISTEN){
        int ret = listen(_sockfd, backlog);
        if(ret < 0){
            perror("listen error");
            return false;
        }
        return true;
    }

    // 4.获取新建连接
    bool Accept(TCPsocket* new_sock, string* ip = NULL, uint16_t* port = NULL){
        struct sockaddr_in addr;
        socklen_t len = sizeof(struct sockaddr_in);
        int new_fd = accept(_sockfd, (struct sockaddr*)&addr, &len);
        if(new_fd < 0){
            perror("accept error");
            return false;
        }
        new_sock->_sockfd = new_fd;
        if(ip != NULL){
            *ip = inet_ntoa(addr.sin_addr);
        }
        if(port != NULL){
            *port = ntohs(addr.sin_port);
        }
        return true;
    }

    // 5.接收数据
    bool Recv(string* buf){
        char tmp[4096] = {0};
        int ret = recv(_sockfd, tmp, 4096, 0);
        if(ret < 0){
            perror("recv error");
            return false;
        }
        else if(ret == 0){
            printf("disconnected\n");
            return false;
        }
        
        buf->assign(tmp, ret);
        return true;
    }

    // 6.发送数据
    bool Send(const string& data){
        int ret = send(_sockfd, data.c_str(), data.size(), 0);
        if(ret < 0){
            perror("send error");
            return false;
        }
        return true;
    }

    // 7.关闭套接字
    bool Close(){
        if(_sockfd > 0){
            close(_sockfd);
            _sockfd = -1;
        }
        return true;
    }

    // 8.发送连接请求
    bool Connect(const string& ip, uint16_t port){
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        socklen_t len = sizeof(struct sockaddr_in);
        int ret = connect(_sockfd, (struct sockaddr*)&addr, len);
        if(ret < 0){
            perror("connect error");
            return false;
        }
        return true;
    } 


    
private:
    int _sockfd;
};
