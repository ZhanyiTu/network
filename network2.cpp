//原作者代码
#include <stdio.h>
#include <Winsock2.h>
#include <sys/types.h>
#include <WS2TCPIP.H>
#pragma comment(lib, "Ws2_32.lib")

int main()
{

    WORD wVersionRequested;
    WSADATA wsaDATA;
    int err;

    wVersionRequested = MAKEWORD(1, 1);

    err = WSAStartup(wVersionRequested, &wsaDATA);
    if(err != 0) {
        return 0;
    }
    if (LOBYTE(wsaDATA.wVersion) != 1 || HIBYTE(wsaDATA.wVersion) != 1) {
        WSACleanup();
        return 0;//版本号不对就终止
    }

    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//流式socket 源socket

    SOCKADDR_IN addrSrv;//源socket的地址
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//#define INADDR_ANY              (ULONG)0x00000000 参数是Host地址 默认设置为0
    //inet_pton(AF_INET, "127.5.5.5", (void*)&addrSrv.sin_addr);
    /*
    u_long
WSAAPI
htonl(
    _In_ u_long hostlong
    ); 只看得到函数的参数将一个数转换为Ulong类型
    */
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(8080);
    memset(addrSrv.sin_zero, 0, 8);

    bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//将socket和地址绑定

    listen(sockSrv, 5);//开始监听, 最多监听5个端口

    SOCKADDR_IN addrClient;
    int len = sizeof(sockaddr);
    while (1) {
        SOCKET sockConn = accept(sockSrv, (struct sockaddr*)&addrClient, &len);//通过监听功能 接受请求 然后创建会话socket 用于通信
        if (sockConn == INVALID_SOCKET) {
            printf("%d\n", WSAGetLastError());
        }
        char sendBuf[50];
        char str[50];
        printf("say something");
        sprintf_s(sendBuf, 50, "Welcome addr %s to here!",inet_ntop(AF_INET, &addrClient.sin_addr, str, sizeof(str)));
        if (send(sockConn, sendBuf, strlen(sendBuf) + 1, 0) <= 0)//通过会话socket 发送数据sendbuf
            printf("%d\n", WSAGetLastError());
        char recvBuf[50];
        int sign2 = recv(sockConn, recvBuf, 50, 0);//通过会话socket 返回接受数据recvBuf
        WSAGetLastError();
        printf("%s\n", recvBuf);//在控制台打印recvBuf
        closesocket(sockConn);//关闭会话socket
    }
    return 0;

}