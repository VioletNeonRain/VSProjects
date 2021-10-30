#include<iostream>
#include<vector>
using namespace std;
vector<int> S;  //�ѱ������ĵ�ļ���
vector<int> V_S;  //δ�����ĵ�ļ���
int sum = 0;  //��С������Ȩ��֮��
void prim(int** G)
{
	int u, v;
	int minLen = 100;  //����minLen�����ȡֵ���Խ����޸ĴӶ��������÷�Χ
	for (int i = 0; i < S.size(); i++)
	{
		for (int j = 0; j < V_S.size(); j++)
		{
			if ((G[S[i] - 1][V_S[j] - 1] < minLen) && (G[S[i] - 1][V_S[j] - 1] > 0))
			{
				u = S[i];
				v = V_S[j];
				minLen = G[S[i] - 1][V_S[j] - 1];
			}
		}
	}
	S.push_back(v);
	for (auto it = V_S.begin(); it <= V_S.end(); it++)
	{
		if (*it == v)
		{
			V_S.erase(it);
			break;
		}
	}
	sum += G[u - 1][v - 1];
}
int main()
{
	int n, m;
	cin >> n >> m;
	int** graph = new int* [n];
	for (int i = 0; i < n; i++)
	{
		graph[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			graph[i][j] = 0;
		}
	}
	for (int i = 0; i < m; i++)
	{
		int v1, v2, len;
		cin >> v1 >> v2 >> len;
		graph[v1 - 1][v2 - 1] = len;
		graph[v2 - 1][v1 - 1] = len;
	}
	S.push_back(1);
	for (int i = 2; i <= n; i++)
		V_S.push_back(i);
	while (S.size() != n)
	{
		prim(graph);
	}
	cout << sum <<endl;
	return 0;
}