#include<iostream>
#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<Windows.h>
using namespace std;

SOCKET clientSocket;
bool connection(const char* serverIP, int serverPort);
UINT recvMsg(LPVOID lpvoid);
void sendMsg(char* msg, int client_n);
char* int_to_char(int a);

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
	int client_n = 0;
	while (1)
	{
		cin >> msgBuff >> client_n;
		sendMsg(msgBuff, client_n);
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

	if (connect(clientSocket, (sockaddr*)&clientAddr, sizeof(clientAddr)) != 0)
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
		if (recv(clientSocket, msgBuff, 1024, 0) <= 0)  //��÷��������͵��ַ���
		{
			cout << "���������˳�����" << endl;
			break;
		}
		int i = 0;
		int j = 0;  //��¼��һ��'\n'���ڵ��±�
		int k = 0;  //��¼�ڶ���'\n'���ڵ��±�
		char a[1024] = { 0 };  //�洢���������͵��ַ�����ʱ��
		char b[1024] = { 0 };  //�洢���������͵��ַ�������Ϣ����
		while (msgBuff[i] != '\0')
		{
			if (msgBuff[i] != '\n')
			{
				i++;
			}
			else
			{
				if (j == 0)
				{
					j = i;
					i++;
				}
				else
				{
					k = i;
					i++;
					break;
				}
			}
		}
		for (int x = 0; x < j; x++)
		{
			a[x] = msgBuff[x];
		}
		a[j] = '\0';
		cout << "ʱ�䣺" << a << endl;  //���ʱ��
		for (int x = 0; x < k - j - 1; x++)
		{
			b[x] = msgBuff[x + j + 1];
		}
		b[k - j - 1] = '\0';
		cout << "�ͻ���";
		while (msgBuff[i] != '\0')
		{
			cout << msgBuff[i];  //����ͻ���ID
			i++;
		}
		cout << "��" << b << endl;  //�����Ϣ
		cout << endl;
	}
	return 0;
}

void sendMsg(char* msg, int client_n)
{
	struct tm* now_time;
	time_t now;
	now = time(NULL);
	now_time = gmtime(&now);
	char* timebuff = new char[1024];
	timebuff = ctime(&now);
	msg = strcat(timebuff, msg);
	strcat(msg, "\n");
	strcat(msg, int_to_char(client_n));
	send(clientSocket, msg, 1024, 0);
	int x = 0;
	int flag = 0;
	cout << "ʱ�䣺";
	while (msg[x] != '\0')
	{
		if (msg[x] != '\n')
		{
			cout << msg[x];
			x++;
		}
		else
		{
			if (flag == 0)
			{
				cout << endl;
				x = x + 1;
				cout << "�ң�";
			}
			if (flag == 1)
				break;
			flag++;
		}
	}
	cout << endl << endl;
}
char* int_to_char(int a)
{
	char* b;
	b = new char[10];
	sprintf(b, "%d", a);
	return b;
}