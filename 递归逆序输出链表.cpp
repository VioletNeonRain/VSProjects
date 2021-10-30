#include<iostream>
using namespace std;
static int i = 0;
class Node
{
    int num;
    Node* next;
public:
    Node(int n)
    {
        num = n;
        next = NULL;
    }
    void setNext(Node* p)
    {
        next = p;
    }
    int getNum()
    {
        return num;
    }
    Node* getNext()
    {
        return next;
    }
};
class list
{
    Node* head;
public:
    Node* gethead()
    {
        return head;
    }
    list(int n)
    {
        head = new Node(n);
    }
    void addNode(int n);
    void visitAllNode();
    void visitAllNode_reverse(Node* node);
    void visitAllNode_reverse_K(Node* node,int j,int k);
};
void list::addNode(int n)
{
    Node* p = head;
    if (head == NULL)
    {
        head = new Node(n);
    }
    else
    {
        while (p->getNext() != NULL)
        {
            p = p->getNext();
        }
        p->setNext(new Node(n));
        i++;
        cout << "�Ѵ�����" << i << "���ڵ�!" << endl;
    }
}
void list::visitAllNode()
{
    Node* p;
    p = head;
    if (p == NULL)
    {
        cout << "������!" << endl;
    }
    else
    {
        cout << "˳���������ͷ  ";
        while (p->getNext() != NULL)
        {
            cout << p->getNum() << "   ";
            p = p->getNext();
        }
        cout << p->getNum() << "   ��β" << endl;
    }
}
void list::visitAllNode_reverse(Node* node)
{
    if (node != NULL)
    {
        if (node->getNext() != NULL)
        {
            visitAllNode_reverse(node->getNext());
        }
        cout << node->getNum()<<"   ";
    }
    else
    {
        cout << "������!" << endl;
    }
}
void list::visitAllNode_reverse_K(Node* node,int j,int k)
{
    if (node != NULL)
    {
        if (node->getNext() != NULL)
        {
            visitAllNode_reverse_K(node->getNext(), --j, k);
            if (j == i - k - 1)
                cout << node->getNum() << "   ";
        }
        else
        {
            if(j==i-k)
                cout<< node->getNum() << "   ";
        }
    }
    else
    {
        cout << "������!" << endl;
    }
}
int main()
{
    list* p1;
    int m,n,k;
    cout << "���������봴���Ľڵ�����";
    cin >> m;
    if (m > 0)
    {
        cout << "�������һ���ڵ�ֵ�Ӷ�������һ���ڵ㣺";
        cin >> n;
        p1 = new list(n);
        i++;
        cout << "�Ѵ�����" << i << "���ڵ�!" << endl;
        while (i < m)
        {
            cout << "������ڵ�ֵ��";
            cin >> n;
            p1->addNode(n);
        }
        p1->visitAllNode();
        cout << "�����������β  ";
        p1->visitAllNode_reverse(p1->gethead());
        cout << "��ͷ" << endl;
        cout << "������k��ֵ��";
        cin >> k;
        int j = i;
        if (k >= 0 && k < i)
        {
            cout << "������k���ڵ�Ϊ��";
            p1->visitAllNode_reverse_K(p1->gethead(), j, k);
        }
        else
            cout << "�����������Ľڵ㣡" << endl;
        delete p1;
    }
    else
        cout << "�޷���������" << endl;
    return 0;
}