#include <winsock2.h>
#include <stdio.h>
#define SERVPORT    5050
#pragma comment(lib,"ws2_32.lib")
void main(void)
{
 WSADATA              wsaData;
 SOCKET               sListen;  // ����socket
 SOCKET               sClient;  // ����socket
 SOCKADDR_IN          serverAddr;  // ������ַ��Ϣ
 SOCKADDR_IN          clientAddr;  // �ͻ��˵�ַ��Ϣ
 int              clientAddrLen; // ��ַ�ṹ�ĳ���
 int                  nResult;
 // ��ʼ��Windows Socket 2.2
 WSAStartup(MAKEWORD(2,2), &wsaData);
 // ����һ���µ�Socket����Ӧ�ͻ��˵���������
 sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 // ��д�������󶨵ĵ�ַ��Ϣ
 // �˿�Ϊ5050
 // IP��ַΪINADDR_ANY����Ӧÿ������ӿڵĿͻ����
 // ע��ʹ��htonl��IP��ַת��Ϊ�����ʽ
 serverAddr.sin_family = AF_INET;
 serverAddr.sin_port = htons(SERVPORT);    
 serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
 memset(&(serverAddr.sin_zero), 0, sizeof(serverAddr.sin_zero));   
 // �󶨼����˿�
 nResult = bind(sListen, (SOCKADDR *)&serverAddr, sizeof(SOCKADDR));
 if (nResult == SOCKET_ERROR)
 {
  printf("bind failed!\n");
  return;
 }
 // ��ʼ������ָ�������ܶ��г���5������������������
 listen(sListen, 5);
 // �����µ�����
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
   // ��ͻ��˷�����Ϣ
   nResult = send(sClient, "Connect success!", 16, 0);
   if (nResult == SOCKET_ERROR)
   {
    printf("send failed!");
   }
  }
  // ����ֱ�ӹر����ӣ�
  closesocket(sClient);
 } 

 // ���رռ���Socket��Ȼ���˳�Ӧ�ó���
 closesocket(sListen);
 // �ͷ�Windows Socket DLL�������Դ
 WSACleanup();
}