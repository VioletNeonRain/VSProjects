#include<iostream>
#include<time.h>
#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<Windows.h>
using namespace std;

SOCKET serverSocket, clientSocket;  //���������ͻ���
bool initSocket(const char* addr, int port);  //��ʼ��socket
UINT recvMsg(LPVOID lpvoid);  //������Ϣ
void sendMsg(char* msg);  //������Ϣ

int main()
{
	WSADATA wsaData;  //����WSADATA���ݽṹ
	WSAStartup(MAKEWORD(2, 2), &wsaData);  //����WSAStartup����������Ϳ��Ե����������Socket���е�����Socket����
	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2)  //ʹ��2.2�汾��socket
	{
		cout << "ȷ��Э��汾ʧ�ܣ�" << GetLastError() << endl;
		return -1;
	}
	cout << "ȷ��Э��汾�ɹ���" << endl;
	if (initSocket("10.139.213.68", 7611) == 0)  //�ڳ�ʼ��socketʱ��һ������Ҫ�ǵø���Ϊ��ǰIP��ַ
	{
		cout << "��ʼ��ʧ�ܣ�" << endl;
		return -1;
	}
	cout << "��ʼ���ɹ���" << endl;
	cout << "���ڼ���..." << endl;
	char buff[1024] = { 0 };
	while (1)  //���ϻ�ȡ�û����벢������Ϣ
	{
		cin >> buff;
		sendMsg(buff);
	}
	closesocket(serverSocket);  //�ر�socket
	WSACleanup();  //����WSACleanup�����������Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ
	return 0;
}
bool initSocket(const char* addr, int port)
{
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  //socket����IPv4��ַ��TCPЭ��
	if (serverSocket == SOCKET_ERROR)
	{
		cout << "����socketʧ�ܣ�" << GetLastError() << endl;
		WSACleanup();
		return 0;
	}

	SOCKADDR_IN serveraddr = { 0 };
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.S_un.S_addr = inet_addr(addr);   //IP��ַ
	serveraddr.sin_port = htons(port);   //�˿�

	if (bind(serverSocket, (sockaddr*)&serveraddr, sizeof serveraddr) != 0)
	{
		cout << "��ʧ�ܣ�" << GetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	cout << "�󶨳ɹ���" << endl;

	if (listen(serverSocket, 100) != 0)
	{
		cout << "����ʧ�ܣ�" << GetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recvMsg, NULL, NULL, NULL);  //����������Ϣ���̣߳�ʹ�÷��ͺͽ�����Ϣ����
	return 1;
}

UINT recvMsg(LPVOID lpvoid)
{
	sockaddr_in clientAddr = { 0 };
	int len = sizeof(clientAddr);
	clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &len);
	if (clientSocket == SOCKET_ERROR)
	{
		cout << "δ��ͻ������ӣ�" << GetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	cout << "���ӿͻ��˳ɹ���" << inet_ntoa(clientAddr.sin_addr) << endl;  //����ͻ���IP��ַ
	char msgBuff[1024] = { 0 };
	while (1)
	{
		if (recv(clientSocket, msgBuff, 1024, 0) <= 0)
		{
			cout << "�ͻ������˳�����" << endl;
			break;
		}
		int i = 0;
		cout << "ʱ�䣺";
		while (msgBuff[i] != '\0')  //����recv()�������յ����ַ�����Ϣ�������������
		{
			if (msgBuff[i] != '\n')
			{
				cout << msgBuff[i];
				i++;
			}
			else
			{
				cout << endl;
				i = i + 1;
				cout << "�Է���";
			}
		}
		cout << endl << endl;
	}
	return 0;
}
void sendMsg(char* msg)
{
	struct tm* now_time;
	time_t now;
	now = time(NULL);
	now_time = gmtime(&now);
	char* timebuff = new char[1024];
	timebuff= ctime(&now);
	msg = strcat(timebuff, msg);
	send(clientSocket, msg, 1024, 0);  //������������ַ�����������ַ�����Ϣ
	int i = 0;
	cout << "ʱ�䣺";  //���ڱ�������Լ����͵���Ϣ
	while (msg[i] != '\0')
	{
		if (msg[i] != '\n')
		{
			cout << msg[i];
			i++;
		}
		else
		{
			cout << endl;
			i = i + 1;
			cout << "�ң�";
		}
	} 
	cout << endl << endl;
}