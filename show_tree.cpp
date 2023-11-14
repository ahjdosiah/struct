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
string up_right = "┌";
string down_right = "└";
string up_left = "┐";
string down_left = "┘";
string T_cross = "┤";
string line = "│";

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
void ShowTree(BSTNode *T, string way = "") // way表示达到该节点走过的路，从根开始，向右是'0'，向左是'1'
{
    if (T->right != NULL)
    {
        string right_way = way + RIGHT;
        ShowTree(T->right, right_way);
    }
    string pre;            // 打印节点前需要输出的前置数据
    if (way.length() == 0) // 根节点，不考虑前置输出，这里输出一个空格
        pre = " ";
    else
    {
        pre = "   ";  // 这三个空格来自根节点那一层
        for (unsigned int i = 1; i < way.length(); i++)
        {
            // 按照异或关系补全前置输出
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
        // 根据最后一次转弯方向选择数字前面的符号
        if (way.at(l - 1) == '0')
            pre += up_right;
        else
            pre += down_right;
    }
	
    cout << pre << setw(2) << T->key;
    // 根据左右子树情况为下一层留下分叉标志
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


