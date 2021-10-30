#include<iostream>
using namespace std;
int s = 0;
void move(char A, char C)
{
	cout << A<<"=>"<<C << endl;
}
void hanoi(int n, char A, char B, char C)
{
	if (n == 1)
		move(A, C);
	else
	{
		hanoi(n - 1, A, C, B);
		move(A, C);
		s++;
		hanoi(n - 1, B, A, C);
	}
}
int main()
{
	int n;
	cout << "�����������ƶ���Բ����(n>0)��" << endl;
	cin >> n;
	cout << "�ƶ��Ĳ������£�" << endl;
	hanoi(n, 'A', 'B', 'C');
	cout << "�ƶ����ܲ�����" << s << endl;
	return 0;
}