/*ð�����򣬴�С����*/
#include<iostream>
using namespace std;
bool times =false;
int main()
{
	cout << "������10�����������������" << endl;
	int integers[10];
	for (int i = 0; i < 10; i++)
		cin >> integers[i];
	for (int i = 0; i < 10; i++)
	{
		for (int j = i+1; j < 10; j++)
		{
			if (integers[i] > integers[j])
			{
				int temp = integers[i];
				integers[i] = integers[j];
				integers[j] = temp;
				times =true;
			}
			if (!times)
				break;
		}
	}
	for (int i = 0; i < 10; i++)
		cout << integers[i] << "  ";
	return 0;
}