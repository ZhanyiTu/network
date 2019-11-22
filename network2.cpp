//ԭ���ߴ���
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
        return 0;//�汾�Ų��Ծ���ֹ
    }

    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//��ʽsocket Դsocket

    SOCKADDR_IN addrSrv;//Դsocket�ĵ�ַ
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//#define INADDR_ANY              (ULONG)0x00000000 ������Host��ַ Ĭ������Ϊ0
    //inet_pton(AF_INET, "127.5.5.5", (void*)&addrSrv.sin_addr);
    /*
    u_long
WSAAPI
htonl(
    _In_ u_long hostlong
    ); ֻ���õ������Ĳ�����һ����ת��ΪUlong����
    */
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(8080);
    memset(addrSrv.sin_zero, 0, 8);

    bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//��socket�͵�ַ��

    listen(sockSrv, 5);//��ʼ����, ������5���˿�

    SOCKADDR_IN addrClient;
    int len = sizeof(sockaddr);
    while (1) {
        SOCKET sockConn = accept(sockSrv, (struct sockaddr*)&addrClient, &len);//ͨ���������� �������� Ȼ�󴴽��Ựsocket ����ͨ��
        if (sockConn == INVALID_SOCKET) {
            printf("%d\n", WSAGetLastError());
        }
        char sendBuf[50];
        char str[50];
        printf("say something");
        sprintf_s(sendBuf, 50, "Welcome addr %s to here!",inet_ntop(AF_INET, &addrClient.sin_addr, str, sizeof(str)));
        if (send(sockConn, sendBuf, strlen(sendBuf) + 1, 0) <= 0)//ͨ���Ựsocket ��������sendbuf
            printf("%d\n", WSAGetLastError());
        char recvBuf[50];
        int sign2 = recv(sockConn, recvBuf, 50, 0);//ͨ���Ựsocket ���ؽ�������recvBuf
        WSAGetLastError();
        printf("%s\n", recvBuf);//�ڿ���̨��ӡrecvBuf
        closesocket(sockConn);//�رջỰsocket
    }
    return 0;

}