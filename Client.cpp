#include<iostream>
#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<Windows.h>
using namespace std;

SOCKET clientSocket;
bool connection(const char* serverIP, int serverPort);
UINT recvMsg(LPVOID lpvoid);
void sendMsg(char* msg);

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2)
	{
		cout << "ȷ��Э��汾ʧ�ܣ�" << GetLastError() << endl;
		return 0;
	}
	cout << "ȷ��Э��汾�ɹ���" << endl;

	if (connection("10.139.213.68", 7611) == 0)
	{
		cout << "���ӷ�����ʧ�ܣ�" << endl;
		return -1;
	}
	cout << "���ӷ������ɹ���" << endl;
	char msgBuff[1024] = { 0 };
	while (1)
	{
		cin >> msgBuff;
		sendMsg(msgBuff);
	}
	closesocket(clientSocket);
	WSACleanup();
	return 0;
}
bool connection(const char* serverIP, int serverPort)
{
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == SOCKET_ERROR)
	{
		cout << "����socketʧ�ܣ�" << GetLastError() << endl;
		WSACleanup();
		return 0;
	}

	SOCKADDR_IN clientAddr = { 0 };
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_addr.S_un.S_addr = inet_addr(serverIP);   //IP��ַ
	clientAddr.sin_port = htons(serverPort);   //�˿�

	if (connect(clientSocket, (sockaddr*)&clientAddr, sizeof(clientAddr)) != 0)  //����������벻ͬ���ͻ�������connect()�������ӵ�������
	{
		return 0;
	}

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recvMsg, NULL, NULL, NULL);
	return 1;
}

UINT recvMsg(LPVOID lpvoid)
{
	char msgBuff[1024] = { 0 };
	while (1)
	{
		if (recv(clientSocket, msgBuff, 1024, 0) <= 0)  //����recv()�������յ����ַ�����Ϣ�������������
		{
			cout << "���������˳�����" << endl;
			break;
		}
		int i = 0;
		cout << "ʱ�䣺";
		while (msgBuff[i] != '\0')
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
	timebuff = ctime(&now);
	msg = strcat(timebuff, msg);
	send(clientSocket, msg, 1024, 0);
	int i = 0;
	cout << "ʱ�䣺";
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