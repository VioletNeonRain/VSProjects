#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<Windows.h>
using namespace std;
string alphabet1 = "abcdefghijklmnopqrstuvwxyz";  //Сд��ĸ��
string alphabet2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";  //��д��ĸ��
class SingleTableReplaceAlgo
{
public:
	SingleTableReplaceAlgo() {};
	static void buildTable(char* str);  //������Կ������ĸ��
	static void encryption(char* str);  //����
	static void decryption(char* str);  //����
	static void attack(ifstream& fin);  //���ÿ����ĸռ��ĸ�����İٷֱ�
};
void SingleTableReplaceAlgo::attack(ifstream& fin)
{
	char next;
	int totalNum = 0;  //��ĸ����
	int a[26];  //�洢ÿ����ĸ������int����
	for (int i = 0; i < 26; i++)
	{
		a[i] = 0;
	}
	while (fin.get(next))
	{
		if (next == ' ')  //���Կո�
		{
		}
		else
		{
			totalNum++;  //������ǿո���ĸ��������1
			a[int(next) - 65]++;  //��Ӧ��ĸ��������1
		}
	}
	cout << "����ĸ��Ϊ��" << totalNum << endl;
	for (int i = 0; i < 26; i++)
	{
		cout << char(i + 65) << "��" << fixed << setprecision(3) << double(double(a[i]) * 100 / double(totalNum)) << "%    ";  //���ÿ����ĸռ��ĸ�����İٷֱ�
	}
	cout << endl;
}
void SingleTableReplaceAlgo::buildTable(char* str)
{
	string temp;
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')  //���Կո�
		{
			i++;
			continue;
		}
		int j = 0;
		while (j < temp.length())
		{
			if (temp[j] == str[i])
			{
				break;
			}
			j++;
		}
		if (j==temp.length())
		{
			temp.push_back(str[i]);  //���temp�ַ����в����ڸ���ĸ����Ѹ���ĸ����temp�ַ���
		}
		i++;
	}
	for (int l = 0; l < 26; l++)
	{
		int j = 0;
		while (j < temp.length())
		{
			if (temp[j] == alphabet2[l] || temp[j] == char(int(alphabet2[l]) + 32))
			{
				break;
			}
			j++;
		}
		if (j == temp.length())
		{
			temp.push_back(alphabet2[l]);  //����ĸ����δ����Կ�г��ֵ���ĸ������μ���temp�ַ��������temp�д洢�ļ�Ϊ��ĸ��
		}
	}
	for (int l = 0; l < temp.length(); l++)
	{
		if (temp[l] <= 'Z' && temp[l] >= 'A')
		{
			alphabet2[l] = temp[l];  //alphabet2�洢��Ϊ��д��ĸ��
		}
		else
		{
			alphabet2[l] = char(int(temp[l]) - 32);
		}
	}
	for (int l = 0; l < 26; l++)
	{
		alphabet1[l] = char(int(alphabet2[l]) + 32);  //alphabet1�洢��ΪСд��ĸ��
	}
}
void SingleTableReplaceAlgo::encryption(char* str)
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
			cout << alphabet2[int(str[i]) - 65];  //����ascii�����int��char���͵�ת������ѯ��д��ĸ��
			i++;
			continue;
		}
		cout << alphabet1[int(str[i]) - 97];  //����ascii�����int��char���͵�ת������ѯСд��ĸ��
		i++;
	}
	cout << endl;
}
void SingleTableReplaceAlgo::decryption(char* str)
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
			for (int j = 0; j < 26; j++)
			{
				if (str[i] == alphabet2[j])
				{
					cout << char(j + 65);
					i++;
					break;
				}
			}
		}
		for (int j = 0; j < 26; j++)
		{
			if (str[i] == alphabet1[j])
			{
				cout << char(j + 97);
				i++;
				break;
			}
		}
	}
	cout << endl;
}
int main()
{
	char* s0 = new char[1000];
	char* s1 = new char[1000];
	char* s2 = new char[1000];
	char* s3 = new char[1000];
	cout << "��������Կ��";
	cin.getline(s0, 1000);
	SingleTableReplaceAlgo::buildTable(s0);
	cout << "��������Ҫ���ܵ����ݣ�";
	cin.getline(s1, 1000);
	cout << "���ܽ��Ϊ��";
	SingleTableReplaceAlgo::encryption(s1);
	cout << "��������Ҫ���ܵ����ݣ�";
	cin.getline(s2, 1000);
	cout << "���ܽ��Ϊ��";
	SingleTableReplaceAlgo::decryption(s2);
	cout << "���������ı���ͳ����ĸռ�ȣ�";

	ifstream fin;
	fin.open("G:\\�����ҵ�\\����ѧ\\ʵ��һ\\����.txt");
	while (fin.fail())
	{
		cout << "�ļ��򿪴���" << endl;
		exit(1);
	}
	SingleTableReplaceAlgo::attack(fin);
	fin.close();
	Sleep(10000);
	return 0;
}