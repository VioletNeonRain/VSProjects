#include<iostream>
#include<fstream>
#include<Windows.h>
using namespace std;
char alphabet1[27] = "NHGDCFEIJKLAQBMXUPRSZTVWYO";
class SingleTableReplaceAlgo
{
public:
	SingleTableReplaceAlgo() {};
	static void attack(ifstream& fin);
};
void SingleTableReplaceAlgo::attack(ifstream& fin)
{
	char next;
	while (fin.get(next))
	{
		if (next == ' ')  //���Կո�
		{
			cout << " ";
			continue;
		}
		else
		{
			for (int j = 0; j < 26; j++)
			{
				if (next == alphabet1[j])
				{
					cout << char(j + 97);
					break;
				}
			}
		}
	}
	cout << endl;
}
int main()
{
	ifstream fin;
	fin.open("G:\\�����ҵ�\\����ѧ\\ʵ��һ\\����.txt");
	while (fin.fail())
	{
		cout << "�ļ��򿪴���" << endl;
		exit(1);
	}
	cout << "���ܵõ�������Ϊ��";
	SingleTableReplaceAlgo::attack(fin);
	fin.close();
	Sleep(10000);
	return 0;
}