#include<iostream>
using namespace std;
#include"TCPsocket.hpp"
#define CHECK_RET(q) if((q) == false){return -1;}

int main(int argc, char* argv[]){
    if(argc != 3){
        cout << "Usage: ./TCPcli ip port" << endl;
        return -1;
    }

    string ip = argv[1];
    uint16_t port = stoi(argv[2]);

    TCPsocket sock;
    CHECK_RET(sock.Socket());
    CHECK_RET(sock.Connect(ip, port));

    while(1){
        string buf;
        cout << "client say: " << endl;
        cin >> buf;
        sock.Send(buf);

        buf.clear();

        sock.Recv(&buf);
        cout << "server say: " << buf << endl;

    }
    sock.Close();
    return 0;
}
