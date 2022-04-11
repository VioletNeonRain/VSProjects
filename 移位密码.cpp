#include<iostream>
#include<Windows.h>
using namespace std;
char alphabet1[27] = "abcdefghijklmnopqrstuvwxyz";
char alphabet2[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
class SingleTableReplaceAlgo
{
public:
	SingleTableReplaceAlgo() {};
	static void encryption(char* str, int n);
	static void decryption(char* str, int n);
	static void attack(char* str);
};
void SingleTableReplaceAlgo::attack(char* str)
{
	for (int j = 0; j < 26; j++)
	{
		int i = 0;
		while (str[i] != '\0')
		{
			if (str[i] == ' ')
			{
				cout << str[i];
				i++;
				continue;
			}
			if (str[i] <= 'Z' && str[i] >= 'A')
			{
				cout << alphabet2[(int(str[i]) - 65 + j) % 26];
				i++;
				continue;
			}
			cout << alphabet1[(int(str[i]) - 97 + j) % 26];
			i++;
		}
		cout << "    ��λ��СΪ" << (26 - j) % 26 << endl;
	}
}
void SingleTableReplaceAlgo::encryption(char* str, int n)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			cout << str[i];
			i++;
			continue;
		}
		if (str[i] <= 'Z' && str[i] >= 'A')
		{
			cout << alphabet2[(int(str[i]) - 65 + n) % 26];
			i++;
			continue;
		}
		cout << alphabet1[(int(str[i]) - 97 + n)%26];
		i++;
	}
	cout << endl;
}
void SingleTableReplaceAlgo::decryption(char* str, int n)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			cout << str[i];
			i++;
			continue;
		}
		if (str[i] <= 'Z' && str[i] >= 'A')
		{
			cout << alphabet2[(int(str[i]) - 65 - n + 26) % 26];
			i++;
			continue;
		}
		cout << alphabet1[(int(str[i]) - 97 - n + 26) % 26];
		i++;
	}
	cout << endl;
}
int main()
{
	int a;
	char* s1 = new char[1000];
	char* s2 = new char[1000];
	char* s3 = new char[1000];
	cout << "��������Ҫ���ܵ����ݣ�";
	cin.getline(s1, 1000);
	cout << "��������λ��С��";
	cin >> a;
	cout << "���ܽ��Ϊ��";
	SingleTableReplaceAlgo::encryption(s1, a);
	cin.ignore();
	cout << "��������Ҫ���ܵ����ݣ�";
	cin.getline(s2, 1000);
	cout << "���ܽ��Ϊ��";
	SingleTableReplaceAlgo::decryption(s2, a);
	cout << "���������뱩�����ܵ����ݣ�";
	cin.getline(s3, 1000);
	SingleTableReplaceAlgo::attack(s3);
	Sleep(10000);
	return 0;
}