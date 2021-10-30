#include <iostream>
#include <stack>
#include<limits.h>   //��Ҫʹ��INT_MAX
using namespace std;

struct edge
{
    int u;  //�ߵ����
    int v;  //�ߵ��յ�
    int w;  //Ȩֵ
};

int  vertex_num;  //�ڵ���
int  edge_num;    //����
int  source;      //Դ��
edge edges[10000];  //��¼���бߣ��ݽ������С����Ϊ10000
int  dis[10000];  //Դ�㵽�ڵ�i����̾���
int  path[10000];   //��¼���·�������Ľڵ�

bool Bellman_Ford()
{
    bool flag = true;  //����Ƿ��и�Ȩ��
    for (int i = 1; i <= vertex_num; i++)  //��ʼ��dis[]����Ԫ�ش�СΪint�������ܱ�ʾ�����ֵ
    {
        if (i == source)
            dis[i] = 0;
        else
            dis[i] = INT_MAX;
    }
    for (int i = 1; i < vertex_num; i++)    //n-1��ѭ�������·��
    {
        for (int j = 0; j < edge_num; j++)
        {
            if (dis[edges[j].v] > dis[edges[j].u] + edges[j].w)
            {
                dis[edges[j].v] = dis[edges[j].u] + edges[j].w;
                path[edges[j].v] = edges[j].u;
            }
        }
    }
    for (int i = 0; i < edge_num; i++)  //��n��ѭ���ж��Ƿ���ڸ�Ȩ��
    {
        if (dis[edges[i].v] > dis[edges[i].u] + edges[i].w)
        {
            flag = false;
            break;
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
            while (!s.empty())  //��ջ�����ε�����������·��
            {
                cout << "-->" << s.top();
                s.pop();
            }
            cout << "�����·������Ϊ��" << dis[i] << endl;
        }
    }
}

int main()
{
    cout << "����������ڵ�����������Դ�㣺"<<endl;
    cin >> vertex_num >> edge_num >> source;
    cout << "�밴˳������" << edge_num << "���ߵ���㡢�յ㡢Ȩֵ��"<<endl;
    for (int i = 0; i < edge_num; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    if (Bellman_Ford())
        print();
    else
        cout << "ͼ�д��ڸ�Ȩ��������������·����" << endl;
    return 0;
}