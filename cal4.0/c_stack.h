#include<iostream>
#include<fstream>
#include<sstream>
#include<ctime>
#include<vector>
#include<string>
#include<cmath>
#include<stdlib.h>
using namespace std;
const int maxn = 1000;

typedef struct num{
	double num;
	struct num* next;
}num;

typedef struct op{
	char op;
	struct op* next;
}op;

class num_stack{
private:
	int length;
	num* phead;
public:
	num_stack();
	~num_stack();
	void clear();
	num* BuyListNode(double x);
	void Push(double n);
	void Pop();
	bool Empty();
	int Length();
	void Print();
	double Top();
};

class str_stack{
private:
	int length;
	op* phead;
public:
	str_stack();
	~str_stack();
	void clear();
	op* BuyListNode(char ch);
	void Push(char ch);
	void Pop();
	bool Empty();
	int Length();
	void Print();
	char Top();
};
