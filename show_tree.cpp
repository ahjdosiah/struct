#include<iostream>
#include<string.h>
#include<iomanip>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
using namespace std; 

int randomInt(int min, int max) {
	int num = rand()%(max-min)+min+1;
	return num;
}

#define RIGHT '0'
#define LEFT '1'
string up_right = "��";
string down_right = "��";
string up_left = "��";
string down_left = "��";
string T_cross = "��";
string line = "��";

typedef struct BSTNode
{
    int key;
    struct BSTNode *left, *right;
} BSTNode;

BSTNode *Insert(BSTNode *T, int key)
{
    if (T == NULL)
    {
        T = new BSTNode();
        T->key = key;
        T->left = NULL;
        T->right = NULL;
        return T;
    }
    else if (T->key == key)
        return T;
    else if (T->key > key)
        T->left = Insert(T->left, key);
    else if (T->key < key)
        T->right = Insert(T->right, key);

    return T;
}
void ShowTree(BSTNode *T, string way = "") // way��ʾ�ﵽ�ýڵ��߹���·���Ӹ���ʼ��������'0'��������'1'
{
    if (T->right != NULL)
    {
        string right_way = way + RIGHT;
        ShowTree(T->right, right_way);
    }
    string pre;            // ��ӡ�ڵ�ǰ��Ҫ�����ǰ������
    if (way.length() == 0) // ���ڵ㣬������ǰ��������������һ���ո�
        pre = " ";
    else
    {
        pre = "   ";  // �������ո����Ը��ڵ���һ��
        for (unsigned int i = 1; i < way.length(); i++)
        {
            // ��������ϵ��ȫǰ�����
            if (way.at(i) != way.at(i - 1))
            {
                pre += line;
                pre += "  ";
            }
            else
            {
                pre += "   ";
            }
        }
        int l = way.length();
        // �������һ��ת�䷽��ѡ������ǰ��ķ���
        if (way.at(l - 1) == '0')
            pre += up_right;
        else
            pre += down_right;
    }
	
    cout << pre << setw(2) << T->key;
    // ���������������Ϊ��һ�����·ֲ��־
    if (T->left != NULL && T->right != NULL)
        cout << T_cross;
    else if (T->left != NULL && T->right == NULL)
        cout << up_left;
    else if (T->left == NULL && T->right != NULL)
        cout << down_left;
    cout << endl;

    if (T->left != NULL)
    {
        string left_way = way + LEFT;
        ShowTree(T->left, left_way);
    }
}

int main()
{
	srand(time(NULL));
    int nums[21] = {50, 75, 25, 90, 60, 40, 15, 100, 86, 80, 88, 69, 58, 52, 46, 39, 18, 12, 20, 16,49};
    int num2[20];
    num2[0] = 50;
    for(int i=1;i<20;i++){
    	num2[i] = randomInt(10,99);
	}
    BSTNode *T = NULL;
    for (int i = 0; i < 21; i++)
        T = Insert(T, num2[i]);
    ShowTree(T);
    return 0;
}


