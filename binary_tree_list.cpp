#include<iostream>
#include<string.h>
#include<time.h>
#include<cstddef>//引用nullptr 
#include<iomanip>
using namespace std;

//用于二叉树输出 
#define RIGHT '0'
#define LEFT '1'
string up_right = "┌";
string down_right = "└";
string up_left = "┐";
string down_left = "┘";
string T_cross = "┤";
string line = "│";

typedef struct treeNode{
	int data;
	treeNode* lchild;
	treeNode* rchild;
}treeNode;

class Btree{
public:
	Btree(){
		root = new treeNode;
		if(root == nullptr){
			cout<<"creat falled";
			exit(0);
		}
		root->data = -1;
		root->lchild = nullptr;
		root->rchild = nullptr;
	}
	treeNode* Root(){
		return this->root;
	}
	
	void printTree() {
        ShowTree(root,"");
    }
	void buildBtree(){
		buildBtree(root);
	}
	treeNode* insertNode(int key){
		if(root->data == -1){
			root->data = key;
            return nullptr;
        }
		else
			return insertNode(root,key);
	}
	
	void fontTravlBtree(){
		fontTravlBtree(root);
	}
	void midTravlBtree(){
		midTravlBtree(root);
	}
	void endTravlBtree(){
		endTravlBtree(root);
	}
	
	int depth(){
		return depth(root);
	}
	int countNode(){
		return countNode(root);
	}
	treeNode* parentNode(int x){
		return parentNode(root,x);
	}
	treeNode* findNode(int x){
		return findNode(root,x);
	}
	
private:
	treeNode* root;
	treeNode* creatNode(int x);
	void buildBtree(treeNode* &root);
	void fontTravlBtree(treeNode* root);
	void midTravlBtree(treeNode* root);
	void endTravlBtree(treeNode* root);
	int depth(treeNode* root);
	int countNode(treeNode* root);
	void ShowTree(treeNode *T, string way);
	treeNode* findNode(treeNode* node, int x);
	treeNode* insertNode(treeNode* &root, int val);
	treeNode* parentNode(treeNode* node,int x);
};

treeNode* Btree::creatNode(int x){
	treeNode* ye = new treeNode;
	if(ye == nullptr){
		cout<<"creat node falled";
		exit(0);
	}
	ye->data = x;
	ye->lchild = nullptr;
	ye->rchild = nullptr;
	return ye;
}
void Btree::buildBtree(treeNode* &root){
    int x;
    cin >> x;
    if (x == -1) {
        root = nullptr;
    } else {
        root = new treeNode;
        root->data = x;
        buildBtree(root->lchild);
        buildBtree(root->rchild);
    }
}
treeNode* Btree::insertNode(treeNode* &root, int val) {
    if (root == nullptr) {
        root = creatNode(val);
    } 
	else if (val < root->data) {
        root->lchild = insertNode(root->lchild, val);
    } 
	else if (val > root->data) {
        root->rchild = insertNode(root->rchild, val);
    }
    return root;
}

int Btree::depth(treeNode* root){
    if (root == nullptr) {
        return 0;
    } 
	else {
        int left_depth = depth(root->lchild);
        int right_depth = depth(root->rchild);
        return max(left_depth, right_depth) + 1;
    }
}
int Btree::countNode(treeNode* root){
	if (root == nullptr) {
        return 0;
    } 
	else {
        int left_node = countNode(root->lchild);
        int right_node = countNode(root->rchild);
        return 1+left_node + right_node;
    }
}

void Btree::fontTravlBtree(treeNode* root){
	if(root == nullptr)
		return;
	cout<<root->data<<" ";
	fontTravlBtree(root->lchild);
	fontTravlBtree(root->rchild);
}
void Btree::midTravlBtree(treeNode* root){
	if(root == nullptr)
		return;
	midTravlBtree(root->lchild);
	cout<<root->data<<" ";
	midTravlBtree(root->rchild);
}
void Btree::endTravlBtree(treeNode* root){
	if(root == nullptr)
		return;
	endTravlBtree(root->lchild);
	endTravlBtree(root->rchild);
	cout<<root->data<<" ";
}

treeNode* Btree::findNode(treeNode* node, int x) {
    if (node == nullptr || node->data == x) {
        return node;
    }

    treeNode* leftResult = findNode(node->lchild, x);
    if (leftResult != nullptr) {
        return leftResult;
    }

    treeNode* rightResult = findNode(node->rchild, x);
    if (rightResult != nullptr) {
        return rightResult;
    }

    return nullptr;
}
treeNode* Btree::parentNode(treeNode* node,int x){
	if (node == nullptr || (node->lchild != nullptr && node->lchild->data == x) || (node->rchild != nullptr && node->rchild->data == x)) {
        return node;
    }
	
    treeNode* leftResult = parentNode(node->lchild, x);
    if (leftResult != nullptr) {
        return leftResult;
    }

    treeNode* rightResult = parentNode(node->rchild, x);
    if (rightResult != nullptr) {
        return rightResult;
    }

    return nullptr;
}
void Btree::ShowTree(treeNode *T, string way){ //way表示达到该节点走过的路，从根开始，向右是'0'，向左是'1'
    if (T->rchild != NULL)
    {
        string right_way = way + RIGHT;
        ShowTree(T->rchild, right_way);
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

    cout << pre << setw(2) << T->data;
    // 根据左右子树情况为下一层留下分叉标志
    if (T->lchild != NULL && T->rchild != NULL)
        cout << T_cross;
    else if (T->lchild != NULL && T->rchild == NULL)
        cout << up_left;
    else if (T->lchild == NULL && T->rchild != NULL)
        cout << down_left;
    cout << endl;

    if (T->lchild != NULL)
    {
        string left_way = way + LEFT;
        ShowTree(T->lchild, left_way);
    }
}

int main(){
	srand(time(NULL));
	ios::sync_with_stdio(false);//用于将 C++ 的输入输出流与 C 标准 I/O 解绑
	// 将 cin 和 cout 的关联流（tied stream）设置为 nullptr，意味着在进行输入操作时不会自动刷新输出缓冲区	
    cin.tie(nullptr),cout.tie(nullptr);
	//以上两个用于 提高程序的性能
	int x;
	Btree tree;
	
//	tree.buildBtree();

	//自动生成二叉树 
	int num[20];
    num[0] = 50;
    for(int i=1;i<20;i++)
    	num[i] = rand()%90+10;
    for(int i=0;i<20;i++)
        tree.insertNode(num[i]);

	tree.printTree();
	cout<<"fonttravl:"; 
	tree.fontTravlBtree();
	cout<<endl<<"midtravl:";
	tree.midTravlBtree();
	cout<<endl<<"endtravl:";
	tree.endTravlBtree();
	cout<<endl<<"depth:"<<tree.depth()<<endl;
	cout<<"countNode"<<tree.countNode()<<endl;
	cout<<"find parent'node:"<<flush;
	cin >> x;
	cout << "parent is:" << tree.parentNode(x)->data << endl;	
	return 0;
}

/*                              _
 *  _._ _..._ .-',     _.._(`))
 * '-. `     '  /-._.-'    ',/
 *    )         \            '.
 *   / _    _    |             \
 *  |  a    a    /              |
 *  \   .-.                     ;
 *   '-('' ).-'       ,'       ;
 *      '-;           |      .'
 *         \           \    /       
 *         | 7  .__  _.-\   \      
 *         | |  |  ``/  /`  /      
 *        /,_|  |   /,_/   /       
 *           /,_/      '`-' 
 */
