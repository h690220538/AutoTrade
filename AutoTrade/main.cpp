// AutoTrade.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AutoTrade.h"

using namespace std;

#pragma comment(lib, "ws2_32.lib")

#define PORT 4000
#define IP_ADDRESS "127.0.0.1"

int _tmain(int argc, _TCHAR* argv[])
{
	AutoTrade autoTrade;

	WSADATA  Ws;
    SOCKET ServerSocket, ClientSocket;
    struct sockaddr_in LocalAddr, ClientAddr;
    int Ret = 0;
    int AddrLen = 0;

	//Init Windows Socket
    if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
    {
        cout<<"Init Windows Socket Failed::"<<GetLastError()<<endl;
        return -1;
    }

	//Create Socket
    ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if ( ServerSocket == INVALID_SOCKET )
    {
        cout<<"Create Socket Failed::"<<GetLastError()<<endl;
        return -1;
    }

	LocalAddr.sin_family = AF_INET;
    LocalAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    LocalAddr.sin_port = htons(PORT);
    memset(LocalAddr.sin_zero, 0x00, 8);

	//Bind Socket
    Ret = bind(ServerSocket, (struct sockaddr*)&LocalAddr, sizeof(LocalAddr));
    if ( Ret != 0 )
    {
        cout<<"Bind Socket Failed::"<<GetLastError()<<endl;
        return -1;
    }
    //listen
    Ret = listen(ServerSocket, 10);
    if ( Ret != 0 )
    {
        cout<<"listen Socket Failed::"<<GetLastError()<<endl;
        return -1;
    }

	cout<<"服务端已经启动"<<endl;

	while ( true )
    {
        AddrLen = sizeof(ClientAddr);
        ClientSocket = accept(ServerSocket, (struct sockaddr*)&ClientAddr, &AddrLen);
        if ( ClientSocket == INVALID_SOCKET )
        {
            cout<<"Accept Failed::"<<GetLastError()<<endl;
            break;
        }

        cout<<"客户端连接::"<<inet_ntoa(ClientAddr.sin_addr)<<":"<<ClientAddr.sin_port<<endl;

		char RecvBuffer[MAX_PATH];
		while ( true )
		{
			memset(RecvBuffer, 0x00, sizeof(RecvBuffer));
			Ret = recv(ClientSocket, RecvBuffer, MAX_PATH, 0);
			if ( Ret == 0 || Ret == SOCKET_ERROR ) 
			{
				cout<<"客户端退出!"<<endl;
				break;
			}
			cout<<"接收到客户信息为:"<<RecvBuffer<<endl;
			string rb(RecvBuffer);
			autoTrade.parse(rb);
		}
    }

	closesocket(ServerSocket);
    closesocket(ClientSocket);
    WSACleanup();

	system("pause");
	return 0;
}

