#include <iostream>
#include <stack>
#include<limits.h>    //��Ҫʹ��INT_MAX
#include <queue>
#include<vector>
using namespace std;

struct edge
{
	int u;  //�ߵ����
	int v;  //�ߵ��յ�
	int w;  //Ȩֵ
};

int vertex_num;  //�ڵ���
int edge_num;  //����
int source;  //Դ��
vector<edge> edges[1000];  //vector���飬������¼�˱ߵ���Ϣ���������vector���Ԫ��������¼�ڽӵ�
int dis[1000];  //Դ�㵽�ڵ�i����̾���
int path[1000];  //��¼���·�������Ľڵ�
bool in_queue[1000];
int in_count[1000];
queue<int> q;

bool BFImproved()  //Bellman_Ford�㷨�Ľ���
{
	bool flag = true;  //����Ƿ��и�Ȩ��
	for (int i = 1; i <= vertex_num; i++)
	{
		if (i == source)
			dis[i] = 0;
		else
			dis[i] = INT_MAX;   //��ʼ��dis[]����Ԫ�ش�СΪint�������ܱ�ʾ�����ֵ
		in_queue[i] = false;  //���нڵ㶼���ڶ�����
		in_count[i] = 0;  //���нڵ���Ӵ���Ϊ0
	}
	q.push(source);
	in_queue[source] = true;
	in_count[source] = 1;
	while (!q.empty())
	{
		int temp = q.front();
		q.pop();
		in_queue[temp] = false;
		int adjoin_num = edges[temp].size();  //ͳ��temp���ڽӵ�ĸ���
		for (int i = 0; i < adjoin_num; i++)  //��temp���ÿ���ڽӵ������ӳ��Ӳ�������Ӧ�ģ��Ա߽����ɳڲ���
		{
			edge* edges_adjoin = &edges[temp][i];
			if (dis[(*edges_adjoin).v] > dis[temp] + (*edges_adjoin).w)
			{
				dis[(*edges_adjoin).v] = dis[temp] + (*edges_adjoin).w;
				path[(*edges_adjoin).v] = temp;
				if (!in_queue[(*edges_adjoin).v])
				{
					q.push((*edges_adjoin).v);
					in_queue[(*edges_adjoin).v] = true;
					in_count[(*edges_adjoin).v] ++;
					if (in_count[(*edges_adjoin).v] > vertex_num)  //���ĳ������Ӵ��������ڵ�������ô��Ȼ���ڸ�Ȩ��
					{
						while (!q.empty()) 
						{
							q.pop();  //���տռ�
						}
						flag = false;
						break;
					}
				}
			}
		}
	}
	return flag;
}

void print()
{
	for (int i = 1; i <= vertex_num; i++)
	{
		if (i != source)
		{
			int temp = i;
			stack<int> s;
			cout << "�ڵ�" << source << "���ڵ�" << temp << "�����·��Ϊ��";
			while (source != temp)  //·��˳��������洢�ģ����Կ���ʹ��ջ
			{
				s.push(temp);
				temp = path[temp];
			}
			cout << source;
			while(!s.empty()) {  //��ջ�����ε�����������·��
				cout << "-->" << s.top();  
				s.pop();
			}
			cout << "�����·������Ϊ��" << dis[i] << endl;
		}
	}
}

int main()
{
	cout << "����������ڵ�����������Դ�㣺" << endl;
	cin >> vertex_num >> edge_num >> source;
	cout << "�밴˳������" << edge_num << "���ߵ���㡢�յ㡢Ȩֵ��" << endl;
	int u, v, w;
	edge temp;
	for (int i = 0; i < edge_num; i++)
	{
		cin >> u >> v >> w;
		temp.v = v;
		temp.w = w;
		edges[u].push_back(temp);
	}
	if (BFImproved())
		print();
	else
		cout << "ͼ�д��ڸ�Ȩ��������������·����" << endl;
	return 0;
}