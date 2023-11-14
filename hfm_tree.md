# 哈夫曼树 哈夫曼编码

## 前言

哈夫曼树也有人称为 霍夫曼树 或 最优二叉树。

哈夫曼（David Huffman）是美国的一位数学家。他在 1952 年发明了哈夫曼编码（一种二进制编码），该编码中用到了一种特殊的二叉树，人们为了纪念他的成就，将所用到的特殊二叉树称为哈夫曼树。



## 基本术语

- 路径和路径长度

  在一棵树中，从一个结点往下可以达到的孩子或孙子结点之间的通路，称为路径。如根节点到a

  通路中分支的数目称为路径长度。若规定根结点的层数为1，则从根结点到第L层结点的路径长度为L-1。a为第二层

- 结点的权和结点的带权路径长度

  若将树中结点赋给一个有着某种含义的数值，则这个数值称为该结点的权。a的权为7

  结点的带权路径长度为：从根结点到该结点之间的路径长度与该结点的权的乘积。b的带权路径长度 5*2 = 10

- 树的带权结点长度（WPL）

  树的带权路径长度规定为所有叶子结点的带权路径长度之和
  $$
  WPL = 7*1 + 5*2+2*3+4*3
  $$

![](D:\软件\typora\Typora\image\hfm_tree\09563Tb0-0.png)

## 哈夫曼树的基本构造

对于给定的有各自权值的 n 个结点，构建哈夫曼树有一个行之有效的办法：

1. 在 n 个权值中选出两个最小的权值，对应的两个结点组成一个新的二叉树，且新二叉树的根结点的权值为左右孩子权值的和；
2. 在原有的 n 个权值中删除那两个最小的权值，同时将新的权值加入到 n–2 个权值的行列中，以此类推；
3. 重复 1 和 2 ，直到所以的结点构建成了一棵二叉树为止，这棵树就是哈夫曼树。														![](D:\软件\typora\Typora\image\hfm_tree\09563QS5-1-1699877296837-3.png) 
   

上图 中，（A）给定了四个结点a，b，c，d，权值分别为7，5，2，4；第一步如（B）所示，找出现有权值中最小的两个，2 和 4 ，相应的结点 c 和 d 构建一个新的二叉树，树根的权值为 2 + 4 = 6，同时将原有权值中的 2 和 4 删掉，将新的权值 6 加入；进入（C），重复之前的步骤。直到（D）中，所有的结点构建成了一个全新的二叉树，这就是哈夫曼树。

## 代码部分

### 哈夫曼树的结点

```c++
struct HFMTreeNode{
	string code;//哈夫曼编码
	char op;//编码对应的字符
	int weight; //权值
	int parent; //父亲（数组下标值）
	int lchild; //左孩子
	int rchild; //右孩子
};
```

### 哈夫曼树类

大纲

```c++
class HFMTree{
private:
	HFMTreeNode* m_data;//哈夫曼树储存数组
	map<char,string>code;//保存字符对应的二进制编码
	int m_length; //记录当前树有多少个节点【数组中多少个节点被使用了】
	
	void SelectTwoMinValue(int& rtnIdx1, int& rtnIdx2);//选择各节点中权值最小的两个
	void preOrderLeaf(int idx,char* op,int op_size);//先序遍历叶子结点，并输出对应的字符，出现次数，对应编码

	void ShowTree(int idx,map<char,int>count,char* op,int op_size,string way);//呈树形输出哈夫曼树
	
    //对编码进行解码
	string decode(int idx, const string& code);
	string::const_iterator decode(int idx, string::const_iterator codeBegin, string::const_iterator codeEnd, string& result);
	
public:
	~HFMTree(){ //析构函数
		delete[] m_data;
	}
	HFMTree(int nodecount, int* pweight);
	void CreateHFMTree();//构造哈夫曼树
	
	int GetLength(){//获取m_length
		return m_length;
	}
	
	void preOrderLeaf(char* op,int op_size){
		preOrderLeaf(this->GetLength()-1,op,op_size);
	}
	void ShowTree(map<char,int>count,char* op,int op_size){
		ShowTree(this->GetLength()-1,count,op,op_size,"");
	}
	//对字符串进行加密
	string encode(const string str){
        string coding = "";
        for (unsigned int i = 0; i < str.length(); i++)
            coding += this->code[str.at(i)];
        return coding;
    }
	string decode(const string& code){
		return decode(this->GetLength()-1,code);
	}
};
```

### 各函数具体实现

#### HFMTree()

参数解释：nodecount： pweight[]中的值的个数

​					pweight[]：构建哈夫曼树需要的结点的权值

先给m_data分配足够的空间（可以容纳下最初的结点和最终的哈夫曼树）。之后通过循环，将最初的结点分配进m_data中

~~~c++
HFMTree(int nodecount, int* pweight){
		code['0'] = "";
		m_length = nodecount; //节点个数
		int iMaxNodeCount = 2 * m_length - 1; //哈夫曼树的节点总数是2n-1（n代表哈夫曼树的叶子节点数量）
		m_data = new HFMTreeNode[iMaxNodeCount]; //2n-1个节点的哈夫曼数组
	
		for (int i = 0; i < iMaxNodeCount; ++i)
		{
			//-1标记未被使用
			m_data[i].code = "";
			m_data[i].op = '0';
			m_data[i].parent = -1;
			m_data[i].lchild = -1;
			m_data[i].rchild = -1;
		}
		for (int i = 0; i < m_length; ++i)
		{
			m_data[i].weight = pweight[i];
		}
	}
~~~

假设 `nodecount = 5` `pweight[] = {1，2，4}`，则，函数先用m_length储存nodecount的值，再给m_data分配 2*m_length-1的空间。给哈夫曼树每个结点都初始化。然后给叶子结点（初始结点）赋值，即将pweigth[]的值赋给相应的叶子结点

| 编号 | weight | parent | lchild | rchile |
| ---- | ------ | ------ | ------ | ------ |
| 0    | 1      | -1     | -1     | -1     |
| 1    | 2      | -1     | -1     | -1     |
| 2    | 4      | -1     | -1     | -1     |
| 3    |        | -1     | -1     | -1     |
| 4    |        | -1     | -1     | -1     |



#### SelectTwoMinValue()

参数解释：两个引用，用于传出最小两个权值所对应的数组下标

通过循环，找出数组中两个还未被使用的结点，分别传回最小和第二小的权对应的结点的下标

主要作用是在==CreatHFMTree()==函数中找出最小的两个结点，组成较小的二叉树

~~~c
void SelectTwoMinValue(int& rtnIdx1, int& rtnIdx2){
		int minval1 = INT_MAX;//INT_MAX是自带的int类最大值
		int minval2 = INT_MAX;
	
		//找最小值
		for (int i = 0; i < m_length; ++i)
		{
			if (m_data[i].parent == -1) //父标记未被使用
			{
				if (minval1 > m_data[i].weight)
				{
					minval1 = m_data[i].weight; //记录最小值
					rtnIdx1 = i; //记录下标
				}
			}
		} 
	
		//找第二个最小的值
		for (int i = 0; i < m_length; ++i)
		{
			if (m_data[i].parent == -1 && i != rtnIdx1) //注意&&后的条件，目的是把第一个找到的最小权值的节点排除
			{
				if (minval2 > m_data[i].weight)
				{
					minval2 = m_data[i].weight; //记录最小值
					rtnIdx2 = i; //记录下标
				}
			}
		}
		return;
	}
~~~

#### CreateHFMTree()

同哈夫曼树的基本构造，每次找最小的两个结点，结成一个新的二叉树，给新二叉树的更新结点，和更改m_length的值，增加SelectTwoMinValue()能访问的范围

~~~c++
void CreateHFMTree(){
		int idx1 = 0;
		int idx2 = 0;
		
		int iMaxNodeCount = 2 * m_length - 1; //2n-1是整个哈夫曼树的节点数量
		int initlength = m_length;
		for (int i = initlength; i < iMaxNodeCount; ++i)
		{
			SelectTwoMinValue(idx1, idx2);
			m_data[i].weight = m_data[idx1].weight + m_data[idx2].weight; //新节点的权值等于左右孩子
			m_data[i].lchild = idx1;
			m_data[i].rchild = idx2;
			m_data[i].op = '0';
			m_data[idx1].parent = i;
			m_data[idx2].parent = i;

			m_length++; //SelectTwoMinValue()函数要用到该值
		}
		return;
	}
~~~

| 编号 | weight | parent | lchild | rchile |
| ---- | ------ | ------ | ------ | ------ |
| 0    | 1      | 3      | -1     | -1     |
| 1    | 2      | 3      | -1     | -1     |
| 2    | 4      | 4      | -1     | -1     |
| 3    | 3      | 4      | 0      | 1      |
| 4    | 7      | -1     | 3      | 2      |

#### ShowTree()

这个函数有两个重载函数，分别是公有的==ShowTree(map<char,int>count,char* op,int op_size)==和私有的==ShowTree(int idx,map<char,int>count,char* op,int op_size,string way)==。

公有的函数体只有一行，用于调用私有的ShowTree()函数，在主函数中不需要复杂的传参。

~~~c++
void ShowTree(map<char,int>count,char* op,int op_size){
		ShowTree(this->GetLength()-1,count,op,op_size,"");
	}
~~~

私有的函数是这个函数的主要实现。主要有两个功能，**输出哈夫曼树**，**对结点的code和op进行更新**。

输出需要借助这几个全局变量和宏定义

~~~c++
#define RIGHT '0'
#define LEFT '1'
string up_right = "┌";
string down_right = "└";
string up_left = "┐";
string down_left = "┘";
string T_cross = "┤";
string line = "│";
~~~

参数解释：idx：需要输出结点的下标

​					count：在主函数中是计算在字符串中每个字符出现的次数，这里用于匹配结点的权值对应哪个字符出现的次数

​					op[]：记录主函数中字符串中出现过的字符

​					op_size：op的长度

​					way：表示达到该节点走过的路，从根开始，向右是'0'，向左是'1'，并更新至对应的叶子结点

该函数先判断结点是否有右孩子，如果有，就更新way并展示右孩子。没有则继续，对应结点的code更新为way。然后输出该结点。输出完权值后，判断是否为叶子结点，如果是，更新其op。最后，如果有左孩子，则更新way，展示左孩子

~~~c++
void ShowTree(int idx,map<char,int>count,char* op,int op_size,string way){ 
    // way表示达到该节点走过的路，从根开始，向右是'0'，向左是'1'
		if (m_data[idx].rchild != -1)
		{
			string right_way = way + RIGHT;
			ShowTree(m_data[idx].rchild,count,op,op_size, right_way);
		}
		this->m_data[idx].code = way;
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
		
		cout << pre << setw(2) << m_data[idx].weight;
		// 根据左右子树情况为下一层留下分叉标志
		if (m_data[idx].lchild != -1 && m_data[idx].rchild != -1)
			cout << T_cross;
		else if (m_data[idx].lchild != -1 && m_data[idx].rchild == -1)
			cout << up_left;
		else if (m_data[idx].lchild == -1 && m_data[idx].rchild != -1)
			cout << down_left;
		else{
			for(int i = 0; i < op_size ; i++){
				if(m_data[idx].weight == count[op[i]]){
					m_data[idx].op = op[i];
					op[i] = '0';
					break;
				}
			}
			if(m_data[idx].op == ' ')
				cout << " " << "space";
			else
				cout << " " << m_data[idx].op;
		}
			 
		cout << endl;
		
		if (m_data[idx].lchild != -1)
		{
			string left_way = way + LEFT;
			ShowTree(m_data[idx].lchild,count,op,op_size, left_way);
		}
	}
~~~

假设主函数中的字符串为`abbcccc`,则`count[a]=1 count[b]=2 count[c]=4`,`op[0]=a op[1]=b op[2]=3``op_size=3`。

| 编号 | weight | parent | lchild | rchile | op   | code |
| ---- | ------ | ------ | ------ | ------ | ---- | ---- |
| 0    | 1      | 3      | -1     | -1     | a    | 11   |
| 1    | 2      | 3      | -1     | -1     | b    | 10   |
| 2    | 4      | 4      | -1     | -1     | c    | 0    |
| 3    | 3      | 4      | 0      | 1      | 0    |      |
| 4    | 7      | -1     | 3      | 2      | 0    |      |

#### preOrderLeaf()

这个函数也有两个重载，下面介绍主要功能实现的函数

参数同==ShowTree()==的意思

这个函数是输出叶子结点对应的权值，op和code。其中的code是HFMTree类中的一个私有成员

**map<char,string>code**：储存对应字符对应的二进制编码，用于==encode()==函数，对字符串进行编码

~~~c++
void preOrderLeaf(int idx,char* op,int op_size){
		if (idx != -1 )
		{
			if(m_data[idx].lchild == -1 && m_data[idx].rchild == -1){
				for(int i = 0;i < op_size;i++){
					if(m_data[idx].op == op[i]){
						code[op[i]] = m_data[idx].code;
						if(op[i] != ' ')
							cout << left << setw(7) << op[i];
						else
							cout << setw(7) << "space";
						cout << setw(4) << m_data[idx].weight << m_data[idx].code <<endl;
						op[i] = '0';
						break;
					}
				}
			}
				
			preOrderLeaf(m_data[idx].lchild,op,op_size);
			preOrderLeaf(m_data[idx].rchild,op,op_size);
		}
	}
~~~

#### encode()

参数解释：需要编码的字符串

~~~c++
string encode(const string str){
        string coding = "";
        for (unsigned int i = 0; i < str.length(); i++)
            coding += this->code[str.at(i)];
        return coding;
    }
~~~

#### decode()

这个函数有三个重载

**decode(const string& code)**

需要解码的二进制编码，返回string类型

~~~c++
string decode(const string& code){
		return decode(this->GetLength()-1,code);
	}
~~~

**decode(int idx, const string& code)**

idx：结点对应的下标，用于判断是否为叶子结点

返会string类型

~~~c++
string decode(int idx, const string& code) {
		string result;
		//因为引用的是const string类型，所以迭代器要使用con_iterator
		string::const_iterator codeBegin = code.begin();
		string::const_iterator codeEnd = code.end();
		//判断是否解码完毕，从头部解到尾部
		while (codeBegin != codeEnd) {
			codeBegin = decode(idx, codeBegin, codeEnd, result);
		}
		
		return result;
	}
~~~

**decode(int idx, string::const_iterator codeBegin, string::const_iterator codeEnd, string& result)**

result储存解码结果

返回const_iterator类型迭代器

~~~c++
string::const_iterator decode(int idx, string::const_iterator codeBegin, string::const_iterator codeEnd, string& result) {
		if (m_data[idx].lchild == -1 && m_data[idx].rchild == -1) {
			result += m_data[idx].op; //找到对应下标，就加上其对应的op
			return codeBegin;
		} else {//不是对应下标，就移动codeBegin迭代器继续查找
			if (codeBegin != codeEnd) {
				if (*codeBegin == '1') {
					return decode(m_data[idx].lchild, next(codeBegin), codeEnd, result);
				} else if (*codeBegin == '0') {
					return decode(m_data[idx].rchild, next(codeBegin), codeEnd, result);
				}
			}
		}
		return codeBegin;
	}
~~~

### 主函数

~~~c++
int main()
{
	string str;
	string coding = "";

	cout << "please input the str(-1 mean default):";
	getline(cin,str);//获取输入的空格，只有换行才会结束输入
	if(str == "-1")
		str = "The early bird catches the worm, but the second mouse gets the cheese";
	cout << '\n' << str << endl;

	map<char,int>count;
	int sum = 0;

	count['0'] = 0;
	
	char op[str.length()];

	for(unsigned int i = 0; i < str.length() ; i++){
		count[str.at(i)]++;
		if(count[str.at(i)] == 1){
			op[sum] = str.at(i);
			sum++;
		}
	}

	int freq[sum];
	for(int i = 0;i < sum; i++){
		freq[i] = count[op[i]];
	}

	HFMTree hfmt(sum,freq);
	hfmt.CreateHFMTree(); //创建哈夫曼树
	char op1[sum];
	strcpy(op1,op);
	hfmt.ShowTree(count,op1,sum);
	cout << endl;
	strcpy(op1,op);
	hfmt.preOrderLeaf(op1,sum); //遍历哈夫曼树，参数其实就是根节点的下标（数组最后一个有效位置的下标）
	coding = hfmt.encode(str);
	cout << endl <<coding << endl;
	cout << endl << hfmt.decode(coding) << endl;
    cout << "\nthe str has " << str.length() - count[' '] << " letters" << endl;
	return 0;
}
~~~

### 实现结果

![image-20231113235248516](D:\软件\typora\Typora\image\hfm_tree\image-20231113235248516.png)

![image-20231113235305098](D:\软件\typora\Typora\image\hfm_tree\image-20231113235305098.png)

## 结语

总结就是，对于树这种结构，递归可以解决其大部分问题，还是得多学习大佬们的卷王精神，还是不够卷。加油吧😤

这个写了一天，现在已经半夜了。这个是最近的学习成果，希望以后还会写吧。

## 附录

~~~c++
#include<iostream>
#include<string.h>
#include<iomanip>
#include<stdlib.h>
#include<map>
using namespace std; 

#define RIGHT '0'
#define LEFT '1'
string up_right = "┌";
string down_right = "└";
string up_left = "┐";
string down_left = "┘";
string T_cross = "┤";
string line = "│";

//哈夫曼树的节点
struct HFMTreeNode{
	string code;
	char op;
	int weight; //权值
	int parent; //父亲（数组下标值）
	int lchild; //左孩子
	int rchild; //右孩子
};
//哈夫曼树
class HFMTree{
private:
	HFMTreeNode* m_data;
	map<char,string>code;
	int m_length; //记录当前树有多少个节点【数组中多少个节点被使用了】
	
	void SelectTwoMinValue(int& rtnIdx1, int& rtnIdx2){
		int minval1 = INT_MAX;
		int minval2 = INT_MAX;
	
		//找最小值
		for (int i = 0; i < m_length; ++i)
		{
			if (m_data[i].parent == -1) //父标记未被使用
			{
				if (minval1 > m_data[i].weight)
				{
					minval1 = m_data[i].weight; //记录最小值
					rtnIdx1 = i; //记录下标
				}
			}
		} 
	
		//找第二个最小的值
		for (int i = 0; i < m_length; ++i)
		{
			if (m_data[i].parent == -1 && i != rtnIdx1) //注意&&后的条件，目的是把第一个找到的最小权值的节点排除
			{
				if (minval2 > m_data[i].weight)
				{
					minval2 = m_data[i].weight; //记录最小值
					rtnIdx2 = i; //记录下标
				}
			}
		}
		return;
	}
	void preOrderLeaf(int idx,char* op,int op_size){
		if (idx != -1 )
		{
			if(m_data[idx].lchild == -1 && m_data[idx].rchild == -1){
				for(int i = 0;i < op_size;i++){
					if(m_data[idx].op == op[i]){
						code[op[i]] = m_data[idx].code;
						if(op[i] != ' ')
							cout << left << setw(7) << op[i];
						else
							cout << setw(7) << "space";
						cout << setw(4) << m_data[idx].weight << m_data[idx].code <<endl;
						op[i] = '0';
						break;
					}
				}
			}
				
			preOrderLeaf(m_data[idx].lchild,op,op_size);
			preOrderLeaf(m_data[idx].rchild,op,op_size);
		}
	}

	void ShowTree(int idx,map<char,int>count,char* op,int op_size,string way){ // way表示达到该节点走过的路，从根开始，向右是'0'，向左是'1'
		if (m_data[idx].rchild != -1)
		{
			string right_way = way + RIGHT;
			ShowTree(m_data[idx].rchild,count,op,op_size, right_way);
		}
		this->m_data[idx].code = way;
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
		
		cout << pre << setw(2) << m_data[idx].weight;
		// 根据左右子树情况为下一层留下分叉标志
		if (m_data[idx].lchild != -1 && m_data[idx].rchild != -1)
			cout << T_cross;
		else if (m_data[idx].lchild != -1 && m_data[idx].rchild == -1)
			cout << up_left;
		else if (m_data[idx].lchild == -1 && m_data[idx].rchild != -1)
			cout << down_left;
		else{
			for(int i = 0; i < op_size ; i++){
				if(m_data[idx].weight == count[op[i]]){
					m_data[idx].op = op[i];
					op[i] = '0';
					break;
				}
			}
			if(m_data[idx].op == ' ')
				cout << " " << "space";
			else
				cout << " " << m_data[idx].op;
		}
			 
		cout << endl;
		
		if (m_data[idx].lchild != -1)
		{
			string left_way = way + LEFT;
			ShowTree(m_data[idx].lchild,count,op,op_size, left_way);
		}
	}
	
	string decode(int idx, const string& code) {
		string result;
		
		string::const_iterator codeBegin = code.begin();
		string::const_iterator codeEnd = code.end();
		
		while (codeBegin != codeEnd) {
			codeBegin = decode(idx, codeBegin, codeEnd, result);
		}
		
		return result;
	}
	string::const_iterator decode(int idx, string::const_iterator codeBegin, string::const_iterator codeEnd, string& result) {
		if (m_data[idx].lchild == -1 && m_data[idx].rchild == -1) {
			result += m_data[idx].op;
			return codeBegin;
		} else {
			if (codeBegin != codeEnd) {
				if (*codeBegin == '1') {
					return decode(m_data[idx].lchild, next(codeBegin), codeEnd, result);
				} else if (*codeBegin == '0') {
					return decode(m_data[idx].rchild, next(codeBegin), codeEnd, result);
				}
			}
		}
		
		return codeBegin;
	}
	
public:
	~HFMTree(){ //析构函数
		delete[] m_data;
	}
	HFMTree(int nodecount, int* pweight){
		code['0'] = "";
		m_length = nodecount; //节点个数
		int iMaxNodeCount = 2 * m_length - 1; //哈夫曼树的节点总数是2n-1（n代表哈夫曼树的叶子节点数量）
		m_data = new HFMTreeNode[iMaxNodeCount]; //2n-1个节点的哈夫曼数组
	
		for (int i = 0; i < iMaxNodeCount; ++i)
		{
			//-1标记未被使用
			m_data[i].code = "";
			m_data[i].op = '0';
			m_data[i].parent = -1;
			m_data[i].lchild = -1;
			m_data[i].rchild = -1;
		} 
		for (int i = 0; i < m_length; ++i)
		{
			m_data[i].weight = pweight[i];
		}
	}
	void CreateHFMTree(){
		int idx1 = 0;
		int idx2 = 0;
		
		int iMaxNodeCount = 2 * m_length - 1; //2n-1是整个哈夫曼树的节点数量
		int initlength = m_length;
		for (int i = initlength; i < iMaxNodeCount; ++i)
		{
			SelectTwoMinValue(idx1, idx2);
			m_data[i].weight = m_data[idx1].weight + m_data[idx2].weight; //新节点的权值等于左右孩子
			m_data[i].lchild = idx1;
			m_data[i].rchild = idx2;
			m_data[i].op = '0';
			m_data[idx1].parent = i;
			m_data[idx2].parent = i;

			m_length++; //SelectTwoMinValue()函数要用到该值
		}
		return;
	}
	
	int GetLength(){
		return m_length;
	}
	
	void preOrderLeaf(char* op,int op_size){
		preOrderLeaf(this->GetLength()-1,op,op_size);
	}
	void ShowTree(map<char,int>count,char* op,int op_size){
		ShowTree(this->GetLength()-1,count,op,op_size,"");
	}

	string encode(const string str){
        string coding = "";
        for (unsigned int i = 0; i < str.length(); i++)
            coding += this->code[str.at(i)];
        return coding;
    }
	string decode(const string& code){
		return decode(this->GetLength()-1,code);
	}
};



int main()
{
	string str;
	string coding = "";

	cout << "please input the str(-1 mean default):";
	getline(cin,str);
	if(str == "-1")
		str = "The early bird catches the worm, but the second mouse gets the cheese";
	cout << '\n' << str << endl;

	map<char,int>count;
	int sum = 0;

	count['0'] = 0;
	
	char op[str.length()];

	for(unsigned int i = 0; i < str.length() ; i++){
		count[str.at(i)]++;
		if(count[str.at(i)] == 1){
			op[sum] = str.at(i);
			sum++;
		}
	}

	int freq[sum];
	for(int i = 0;i < sum; i++){
		freq[i] = count[op[i]];
	}

	HFMTree hfmt(sum,freq);
	hfmt.CreateHFMTree(); //创建哈夫曼树
	char op1[sum];
	strcpy(op1,op);
	hfmt.ShowTree(count,op1,sum);
	cout << endl;
	strcpy(op1,op);
	hfmt.preOrderLeaf(op1,sum); //遍历哈夫曼树，参数其实就是根节点的下标（数组最后一个有效位置的下标）
	coding = hfmt.encode(str);
	cout << endl <<coding << endl;
	cout << endl << hfmt.decode(coding) << endl;
    cout << "\nthe str has " << str.length() - count[' '] << " letters" << endl;
	return 0;
}

/***
 * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
 * │Esc│   │ F1│ F2│ F3│ F4│ │ F5│ F6│ F7│ F8│ │ F9│F10│F11│F12│ │P/S│S L│P/B│  ┌┐    ┌┐    ┌┐
 * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘  └┘    └┘    └┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
 * │~ `│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│_ -│+ =│ BacSp │ │Ins│Hom│PUp│ │N L│ / │ * │ - │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤
 * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│} ]│ | \ │ │Del│End│PDn│ │ 7 │ 8 │ 9 │   │
 * ├─────┴┬┬──┴┬──┴┬──┴┬──┴┬──┴──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘ ├───┼───┼───┤ + │
 * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│ Enter  │               │ 4 │ 5 │ 6 │   │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐     ├───┼───┼───┼───┤
 * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│  Shift   │     │ ↑ │     │ 1 │ 2 │ 3 │   │
 * ├─────┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤ E││
 * │ Ctrl│    │Alt │         Space         │ Alt│    │    │Ctrl│ │ ← │ ↓ │ → │ │   0   │ . │←─┘│
 * └─────┴────┴────┴───────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘
 */
~~~

