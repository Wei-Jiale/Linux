#include<iostream>
using namespace std;
#include"TCPsocket.hpp"
#define CHECK_RET(q) if((q) == false){return -1;}
int main(int argc, char* argv[]){
    if(argc != 3){
        cout << "Usage: ./TCPsrv ip port" << endl;
        return -1;
    }

    string ip = argv[1];
    uint16_t port = stoi(argv[2]);

    // 创建套接字
    TCPsocket listen_sock;
    CHECK_RET(listen_sock.Socket());

    // 绑定地址信息
    CHECK_RET(listen_sock.Bind(ip, port));

    // 开始监听
    CHECK_RET(listen_sock.Listen());

    while(1){
        TCPsocket new_sock;
        bool ret = listen_sock.Accept(&new_sock);
        if(ret == false){
            // 服务端不能因为获取一个新建套接字失败就退出
            continue;
        }
        string buf;
        new_sock.Recv(&buf);
        cout << "client say: " << buf << endl;

        buf.clear();

        cout << "server say: " << endl;
        cin >> buf;
        new_sock.Send(buf);
    }

    listen_sock.Close();
    return 0;
}
