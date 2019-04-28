
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

#define PORT 8090
#define MAXMSG 1024

int main()
{
    int serverSock;
    socklen_t size;
    ssize_t nbytes;
    sockaddr_in serverAddr;

    char message[MAXMSG];

    serverSock = socket(PF_INET, SOCK_DGRAM, 0);
    if (serverSock < 0) {
        cout << "serverSock create error !" << endl;
        exit(-1);
    }

    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_family = AF_INET;

    int err;
    err = bind(serverSock, (sockaddr*)(&serverAddr), sizeof(serverAddr));
    if (err < 0) {
        cout << "bind error ! " << endl;
        exit(-1);
    }

    while (1) {
        size = sizeof(serverAddr);
        nbytes = recvfrom(serverSock, message, MAXMSG, 0, (sockaddr*)&serverAddr, &size);
        if (nbytes < 0) {
            cout << "recvfrom error ! " << endl;
            exit(-1);
        }
        cout << "server got message : " << message;
        nbytes = sendto(serverSock, message, nbytes, 0, (sockaddr*)&serverAddr, size);
        if (nbytes < 0) {
            cout << "send to error ! " << endl;
            exit(-1);
        }

    }
}
