#include<iostream>
#include<string>
using namespace std;

int* getNext(string s2)
{
	int* next = new int[s2.size()];
	next[0] = -1;
	next[1] = 0;
	int j = 2;
	while (j < s2.size())
	{
		if (next[j - 1] != 0 && s2.at(next[j - 1]) == s2.at(j - 1))
		{
			next[j] = next[j] + 1;
			j++;
		}
		else if (s2.at(0) == s2.at(j - 1))
		{
			next[j] = 1;
			j++;
		}
		else
		{
			next[j] = 0;
			j++;
		}
	}
	return next;
}

void KMP(string s1, string s2)
{
	int l1 = s1.size();
	int l2 = s2.size();
	if (l1 < l2)
		s1.swap(s2);
	l1 = s1.size();
	l2 = s2.size();
	int* next = getNext(s2);
	int i = 0, j = 0;
	while (i < l1 && j < l2)
	{
		if (j == -1 || s1.at(i) == s2.at(j))
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if (j >= l2)
		cout << "�ҵ��Ӵ�����ʼλ��Ϊ��" << i - j << endl;
	else
		cout << "δ�ҵ��Ӵ�" << endl;
}

int main()
{
	string s1, s2;
	cout << "�������ַ���S1��";
	getline(cin, s1);
	cout << "�������ַ���S2��";
	getline(cin, s2);
	KMP(s1, s2);
	return 0;
}