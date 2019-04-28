#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MSGMAX 1024
#define PORT 8090
#define IP_ADDRESS "127.0.0.1"

using namespace std;

int main()
{
    int clinetSock, n;
    char recvBuff[MSGMAX];
    char sendBuff[MSGMAX];
    sockaddr_in serverAddr;

    clinetSock = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_family = AF_INET;
    inet_aton(IP_ADDRESS, &serverAddr.sin_addr);
    serverAddr.sin_addr.s_addr = htonl(serverAddr.sin_addr.s_addr);

    while (fgets(sendBuff, MSGMAX, stdin) != NULL) {
        if (sendto(clinetSock, sendBuff, sizeof(sendBuff), 0, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            cout << "Send to server error !" << endl;
            exit(-1);
        }
        if ((n = recvfrom(clinetSock, recvBuff, MSGMAX, 0, NULL, NULL)) < 0) {
            cout << " recv from server error ! " << endl;
            exit(-1); 
        }
        recvBuff[n] = 0;
        cout << " client received message " << recvBuff << endl;
    }
    close(clinetSock);
    exit(0);
}