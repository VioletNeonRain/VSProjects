#include<iostream>
#include<map>
#include<time.h>
#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<Windows.h>
using namespace std;

#define clientNum 100

SOCKET serverSocket, clientSocket[clientNum];
map<int, int> mapGroup;  //��¼ÿ���ͻ���ID�������ڵ�����Ⱥ���������ID

bool initSocket(const char* addr, int port);
UINT recvMsg(LPVOID lpvoid);
void sendMsg(char* msg);
void msgFromClients(int t);
char* int_to_char(int a);

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2)
	{
		cout << "ȷ��Э��汾ʧ�ܣ�" << GetLastError() << endl;
		return -1;
	}
	cout << "ȷ��Э��汾�ɹ���" << endl;

	for (int x = 0; x < 10; x++)
	{
		mapGroup[x] = x / 2;
	}

	if (initSocket("10.139.213.68", 7611) == 0)
	{
		cout << "��ʼ��ʧ�ܣ�" << endl;
		return -1;
	}
	cout << "��ʼ���ɹ���" << endl;
	cout << "���ڼ���..." << endl;
	char buff[1024] = { 0 };
	while (1)
	{
		cin >> buff;
		sendMsg(buff);
	}
	closesocket(serverSocket);
	WSACleanup();
	return 0;
}
bool initSocket(const char* addr, int port)
{
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recvMsg, NULL, NULL, NULL);
	return 1;
}

UINT recvMsg(LPVOID lpvoid)
{
	sockaddr_in clientAddr = { 0 };
	int len = sizeof(clientAddr);
	for (int i = 0; i < 100; i++)
	{
		clientSocket[i] = accept(serverSocket, (sockaddr*)&clientAddr, &len);
		if (clientSocket[i] == SOCKET_ERROR)
		{
			cout << "δ��ͻ������ӣ�" << GetLastError() << endl;
			closesocket(serverSocket);
			WSACleanup();
			return 0;
		}
		cout << "���ӿͻ���" << i + 1 << "�ɹ���" << endl;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)msgFromClients, (LPVOID)i, NULL, NULL);
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
	for (int j = 0; j < 100; j++)
	{
		send(clientSocket[j], msg, 1024, 0);
	}
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
			i++;
			cout << "�ң�";
		}
	}
	cout << endl << endl;
}
void msgFromClients(int t)
{
	while (1)
	{
		char msgBuff[1024] = { 0 };  //�洢�ͻ��˵���Ϣ
		char sendBuff[1024] = { 0 };  //�洢���͸������ͻ��˵���Ϣ
		char clientStr[10] = { 0 };  //������ŵ��ַ�����ʽ
		if (recv(clientSocket[t], msgBuff, 1024, 0) <= 0)  //��ÿͻ�����Ϣ
		{
			cout << "�ͻ���" << t + 1 << "���˳�����" << endl;
			break;
		}
		int i = 0;
		int flag = 0;  //flag==2��ʾ��������2��'\n'
		cout << "ʱ�䣺";
		while (msgBuff[i] != '\0')  //���whileѭ��ʵ���˶Կͻ�����Ϣ�������
		{
			if (msgBuff[i] != '\n')
			{
				cout << msgBuff[i];
				i++;
			}
			else
			{
				if (flag == 0)
				{
					cout << endl;
					i = i + 1;
					cout << "�ͻ���" << t + 1 << "��";
				}
				if (flag == 1)
				{
					flag++;
					break;
				}
				flag++;
			}
		}
		cout << endl << endl;
		if (flag == 2)
		{
			int temp = i;
			i++;
			while (msgBuff[i] != '\0')
			{
				clientStr[i - temp - 1] = msgBuff[i];
				i++;
			}
			clientStr[i - temp] = '\0';
			int client_n = atoi(clientStr);  //����������ַ���ת��int����
			int z = 0;
			while (z < temp)
			{
				sendBuff[z] = msgBuff[z];  //ʱ�����Ϣ�ַ�������
				z++;
			}
			strcat(sendBuff, "\n");
			strcat(sendBuff, int_to_char(t + 1));  //���ͻ��˵���ż����ַ�����
			mapGroup[t] = client_n - 1;  //��������Ϣ�Ŀͻ��˼���÷�����ŵĿͻ��˵�����Ⱥ��
			map<int, int>::iterator it;
			for (it = mapGroup.begin(); it != mapGroup.end(); it++)  //��ÿһλ�ڸ÷�����ŵ�����Ⱥ�Ŀͻ��˷�����Ϣ
			{
				if (it->second == client_n - 1 && it->first != t)
				{
					send(clientSocket[it->first], sendBuff, 1024, 0);
				}
			}
		}
		else  //����ÿͻ��˱������ڸ�����Ⱥ�У����øı�����Ⱥ��������ֱ�ӷ�����Ϣ
		{
			strcat(sendBuff, msgBuff);
			strcat(sendBuff, "\n");
			strcat(sendBuff, int_to_char(t + 1));
			map<int, int>::iterator it;
			for (it = mapGroup.begin(); it != mapGroup.end(); it++)
			{
				if (it->second == mapGroup[t])
				{
					send(clientSocket[it->first], sendBuff, 1024, 0);
				}
			}
		}
	}
}
char* int_to_char(int a)  //int����תΪ�ַ���
{
	char* b;
	b = new char[10];
	sprintf(b, "%d", a);
	return b;
}