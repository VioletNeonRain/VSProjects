#include<iostream>
using namespace std;
int get_middle(int* p, int left, int right)
{
	int pivot = p[left];
	while (left < right)
	{
		while (p[right] > pivot&& left < right)
			right--;
		p[left] = p[right];
		while (p[left] < pivot && left < right)
			left++;
		p[right] = p[left];
	}
	p[left] = pivot;
	return left;
}
void quicksort(int *p,int left,int right)
{
	if (left < right)
	{
		int middle = get_middle(p, left, right);
		quicksort(p, left, middle - 1);
		quicksort(p, middle + 1, right);
	}
};
int main()
{
	int n;
	cout << "请输入你想排序的整数个数：" << endl;
	cin >> n;
	int* p = new int[n];
	for (int i = 0; i < n; i++)
		cin >> p[i];
	quicksort(p, 0, n - 1);
	for (int i = 0; i < n; i++)
		cout << p[i]<<"  ";
	return 0;
}