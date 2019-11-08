// network.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <Winsock.h>
#include <iostream>

int main()
{
    WORD wVersionRequested;//WORD结构的版本号
    WSADATA wsa;
    int err;


    if (WSAStartup(MAKEWORD(1, 1), &wsa) != 0) {//加载Winsock库
        return;
    }

    SOCKET Listen_Sock = socket(AF_INET, SOCK_STREAM, 0);//构建监听socket 流式socket 服务端socket
    SOCKET Client_Sock = socket(AF_INET, SOCK_STREAM, 0);//构建通讯socket 流式socket 客户端socket

    SOCKADDR_IN serverAddr;//配置监听地址和端口
    ZeroMemory((char*)&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12001);//端口设置
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);//有IP
    bind(Listen_Sock, (struct sockaddr*) & serverAddr, sizeof(serverAddr));//服务端绑定监听socket

    int len = sizeof(SOCKADDR);
    SOCKET Command_Sock = accept(Listen_Sock, (SOCKADDR*)&serverAddr, &len);//还有这种类型转换?是因为只是求一个地址的地址吧 长度居然直接使用sizeof就可以求出来了


    WSACleanup();//释放Winsock库
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
