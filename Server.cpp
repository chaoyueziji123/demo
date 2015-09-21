#include <winsock2.h>
#include <stdio.h>
#define SERVPORT    5050
#pragma comment(lib,"ws2_32.lib")
void main(void)
{
 WSADATA              wsaData;
 SOCKET               sListen;  // 监听socket
 SOCKET               sClient;  // 连接socket
 SOCKADDR_IN          serverAddr;  // 本机地址信息
 SOCKADDR_IN          clientAddr;  // 客户端地址信息
 int              clientAddrLen; // 地址结构的长度
 int                  nResult;
 // 初始化Windows Socket 2.2
 WSAStartup(MAKEWORD(2,2), &wsaData);
 // 创建一个新的Socket来响应客户端的连接请求
 sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 // 填写服务器绑定的地址信息
 // 端口为5050
 // IP地址为INADDR_ANY，响应每个网络接口的客户机活动
 // 注意使用htonl将IP地址转换为网络格式
 serverAddr.sin_family = AF_INET;
 serverAddr.sin_port = htons(SERVPORT);    
 serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
 memset(&(serverAddr.sin_zero), 0, sizeof(serverAddr.sin_zero));   
 // 绑定监听端口
 nResult = bind(sListen, (SOCKADDR *)&serverAddr, sizeof(SOCKADDR));
 if (nResult == SOCKET_ERROR)
 {
  printf("bind failed!\n");
  return;
 }
 // 开始监听，指定最大接受队列长度5，不是连接数的上限
 listen(sListen, 5);
 // 接受新的连接
 while(1)
 { 
  clientAddrLen = sizeof (SOCKADDR);
  sClient = accept(sListen, (SOCKADDR *)&clientAddr, &clientAddrLen);
  if(sClient == INVALID_SOCKET)
  {
   printf("Accept failed!");
  }
  else
  {
   printf("Accepted client: %s : %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
   // 向客户端发送信息
   nResult = send(sClient, "Connect success!", 16, 0);
   if (nResult == SOCKET_ERROR)
   {
    printf("send failed!");
   }
  }
  // 我们直接关闭连接，
  closesocket(sClient);
 } 

 // 并关闭监听Socket，然后退出应用程序
 closesocket(sListen);
 // 释放Windows Socket DLL的相关资源
 WSACleanup();
}