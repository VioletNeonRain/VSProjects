#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <winsock.h>
#include <fstream>
#include <time.h>
#include <string>
using namespace std;

#define PORT 8585
const int MAXLEN = 509;//�������ڴ�����ݵ���󳤶�
char buffer[50000000];
const int MAX_WAIT_TIME = 500;  //���ȴ�ʱ��
const unsigned char ACK = 0x01;
const unsigned char NAK = 0x02;
const unsigned char SHAKE1 = 0x03;
const unsigned char SHAKE2 = 0x04;
const unsigned char SHAKE3 = 0x05;
const unsigned char LAST = 0x06;  //������һ�����ݰ�
const unsigned char NOTLAST = 0x16;  //��ǲ������һ�����ݰ�
const unsigned char WAVE1 = 0x07;
const unsigned char WAVE2 = 0x08;
SOCKET server;
SOCKADDR_IN server_Addr, client_Addr;

unsigned char checkSum(char* package, int len)  //����У���
{
	if (len == 0)
		return ~(0);
	unsigned int sum = 0;
	int i = 0;
	while (len)
	{
		sum += (unsigned char)package[i];
		i++;
		len--;
		if (sum & 0xFF00)
		{
			sum &= 0x00FF;
			sum++;
		}
	}
	return ~(sum & 0x00FF);
}

bool shakeHand()
{
	while (true)
	{
		char recv[2];
		int len_Addr = sizeof(client_Addr);
		while (recvfrom(server, recv, 2, 0, (sockaddr*)&client_Addr, &len_Addr) == SOCKET_ERROR);
		if (checkSum(recv, 2) != 0 || recv[1] != SHAKE1)  //��һ������
			continue;
		printf("��һ���������ݰ�    У��ͣ�0x%x    ���ȣ�2 Bytes    ״̬���ѽ���\n", (unsigned char)recv[0]);
		while (true)
		{
			recv[1] = SHAKE2;
			recv[0] = checkSum(recv + 1, 1);
			sendto(server, recv, 2, 0, (sockaddr*)&client_Addr, sizeof(client_Addr));  //���͵ڶ������ְ�
			printf("�ڶ����������ݰ�    У��ͣ�0x%x    ���ȣ�2 Bytes    ״̬���ѷ���\n", (unsigned char)recv[0]);
			while (recvfrom(server, recv, 2, 0, (sockaddr*)&client_Addr, &len_Addr) == SOCKET_ERROR);
			if (checkSum(recv, 2) == 0 && recv[1] == SHAKE1)
				continue;
			if (checkSum(recv, 2) == 0 && recv[1] == SHAKE3)  //���������ֳɹ�
			{
				printf("�������������ݰ�    У��ͣ�0x%x    ���ȣ�2 Bytes    ״̬���ѽ���\n", (unsigned char)recv[0]);
				break;
			}
			if (checkSum(recv, 2) != 0 || recv[1] != SHAKE3)
			{
				cout << "����ʧ�ܣ�" << endl;
				return false;
			}
		}
		break;
	}
	cout << "���ֳɹ���" << endl;
	return true;
}

void rcv(char* package, int& len_recv)
{
	len_recv = 0;
	char recv[MAXLEN + 4];
	int last_Recv = -1;
	int recv_Num = 0;
	int len_Addr = sizeof(client_Addr);
	while (true)
	{
		while (true)
		{
			memset(recv, 0, sizeof(recv));
			if (recvfrom(server, recv, MAXLEN + 4, 0, (sockaddr*)&client_Addr, &len_Addr) == SOCKET_ERROR)
				continue;
			if (recv[1] == LAST)
			{
				if (recv[3] == 0x0)  //���һ�����ݰ������ݶδ�С������255�ֽ�
					printf("Data���ݰ�    У��ͣ�0x%x    ���ݰ����ȣ�%d Bytes    ", (unsigned char)recv[0], (unsigned char)recv[4] + 5);
				else  //���һ�����ݰ������ݶδ�С����255�ֽ�
					printf("Data���ݰ�    У��ͣ�0x%x    ���ݰ����ȣ�%d Bytes    ", (unsigned char)recv[0], (unsigned char)recv[4] + 261);
			}
			else
			{
				printf("Data���ݰ�    У��ͣ�0x%x    ���ݰ����ȣ�512 Bytes    ", (unsigned char)recv[0]);
			}
			char send[3];
			if (checkSum(recv, MAXLEN + 4) == 0)
			{
				if ((unsigned char)recv[2] == unsigned char((last_Recv + 1) % ((int)UCHAR_MAX + 1)))
				{
					send[1] = ACK;
					send[2] = recv[2];
					send[0] = checkSum(send + 1, 2);
					sendto(server, send, 3, 0, (sockaddr*)&client_Addr, sizeof(client_Addr));
					cout << "���к�:" << recv_Num << "    ״̬���ѽ���" << endl;
					printf("ACK���ݰ�    У��ͣ�0x%x    ���ݰ����ȣ�%d Bytes    ���кţ�%d    ״̬���ѷ���    ��������һλ\n", (unsigned char)send[0], sizeof(send), recv_Num);
					recv_Num++;
					break;
				}
				else
				{
					cout << "���ݰ����к�δƥ�䣬�Ѷ������ݰ�..." << endl;
					send[1] = ACK;
					send[2] = recv[2];
					send[0] = checkSum(send + 1, 2);
					sendto(server, send, 3, 0, (sockaddr*)&client_Addr, sizeof(client_Addr));
					printf("ACK���ݰ�    У��ͣ�0x%x    ���ݰ����ȣ�%d Bytes    ���кţ�%d    ״̬���ѷ���\n", (unsigned char)send[0], sizeof(send), (unsigned char)recv[2]);
					continue;
				}
			}
			else
			{
				cout << "���ݰ����к�δƥ�䣬�Ѷ������ݰ�..." << endl;
				continue;
			}
		}
		last_Recv++;
		if (recv[1] == LAST)
		{
			unsigned int len_last_package = (unsigned char)recv[4];
			if (recv[3] == 0x0)
			{
				for (int i = 5; i < len_last_package + 5; i++)
				{
					package[len_recv] = recv[i];
					len_recv++;
				}
				break;
			}
			else
			{
				for (int i = 5; i < len_last_package + 261; i++)
				{
					package[len_recv] = recv[i];
					len_recv++;
				}
				break;
			}
		}
		else
		{
			for (int i = 3; i < MAXLEN + 3; i++)
			{
				package[len_recv] = recv[i];
				len_recv++;
			}
		}
	}
}

void waveHand()
{
	while (true)
	{
		char recv[2];
		int len_Addr = sizeof(client_Addr);
		while (recvfrom(server, recv, 2, 0, (sockaddr*)&client_Addr, &len_Addr) == SOCKET_ERROR);
		if (checkSum(recv, 2) != 0 || recv[1] != (char)WAVE1)  //��һ�λ���
			continue;
		printf("��һ�λ������ݰ�    У��ͣ�0x%x    ���ȣ�2 Bytes    ״̬���ѽ���\n", (unsigned char)recv[0]);
		recv[1] = WAVE2;
		recv[0] = checkSum(recv + 1, 1);
		sendto(server, recv, 2, 0, (sockaddr*)&client_Addr, sizeof(client_Addr));  //���͵ڶ��λ��ְ�
		printf("�ڶ��λ������ݰ�    У��ͣ�0x%x    ���ȣ�2 Bytes    ״̬���ѷ���\n", (unsigned char)recv[0]);
		break;
	}
	cout << "���ֳɹ���" << endl;
}
int main() {
	clock_t start, end;
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata))
	{
		cout << "WSA��ʼ��ʧ�ܣ�" << endl;
		return 0;
	}
	server_Addr.sin_family = AF_INET;
	server_Addr.sin_port = htons(PORT);
	server_Addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server = socket(AF_INET, SOCK_DGRAM, 0);
	setsockopt(server, SOL_SOCKET, SO_RCVTIMEO, (char*)&MAX_WAIT_TIME, sizeof(MAX_WAIT_TIME));
	if (server == INVALID_SOCKET)
	{
		cout << "����������Socketʧ�ܣ�" << endl;
		closesocket(server);
		return 0;
	}
	if (bind(server, (sockaddr*)(&server_Addr), sizeof(server_Addr)) == SOCKET_ERROR)
	{
		cout << "��ʧ�ܣ�" << endl;
		closesocket(server);
		WSACleanup();
		return 0;
	}
	cout << "������..." << endl;
	if (!shakeHand())
	{
		cout << "����ʧ�ܣ��˳�����" << endl;
		return 0;
	}
	cout << "���ӳɹ���" << endl;
	int len = 0;
	rcv(buffer, len);  //�����ļ���
	buffer[len] = 0;
	string file_Name(buffer);
	cout << "�ļ���Ϊ��" << file_Name << endl;
	memset(buffer, 0, file_Name.length());
	start = clock();  //��ʼ��ʱ
	/*Sleep(2000);*/
	rcv(buffer, len);  //�����ļ�����
	end = clock();  //ֹͣ��ʱ
	ofstream out(file_Name.c_str(), ofstream::binary);
	for (int i = 0; i < len; i++)
		out << buffer[i];
	out.close();
	cout << "�ɹ��յ��ļ�: " << file_Name.c_str() << endl;
	double total_Time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "�ļ����ȣ�" << len << endl;
	cout << "�ļ�����ʱ�䣺" << total_Time << "��" << endl;
	cout << "ƽ�������ʣ�" << len / total_Time << "�ֽ�/��" << endl;
	waveHand();
	closesocket(server);
	WSACleanup();
	cout << "�����Զ��˳�..." << endl;
	Sleep(4000);
	return 0;
}