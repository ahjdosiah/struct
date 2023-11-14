#include"c_stack.h"
//num_stack function
num* num_stack::BuyListNode(double x){
	num* newnode = new num;
	//static SLTNode newnode£»
	if (newnode == NULL)
	{
		perror("malloc:");
		exit(0);
	}
	newnode->num = x;
	newnode->next = NULL;
	return newnode;
}

num_stack::num_stack(){
	length = 0;
	this->phead = NULL;
}

num_stack::~num_stack(){
//	length = 0;
//	delete this->phead;
//	phead = NULL;
}
//empty return true
bool num_stack::Empty(){
	if(length == 0)
		return true;
	else
		return false;
}

int num_stack::Length(){
	return length;
}

void num_stack::Push(double x){
	num* newnode = BuyListNode(x);
	newnode->next = this->phead;
	this->phead = newnode;
}

void num_stack::Pop(){
	if (this->phead == NULL)
		return;
	num* head = this->phead;
	this->phead = this->phead->next;
	free(head);
	head = NULL;
	length--;
}

void num_stack::Print(){
	num* cur = this->phead;
	for(int i = 0;cur != NULL;i++){
		cout<<"num["<<i<<"]="<<cur->num<<" ";
		cur = cur->next;
	}
	cout<<endl;
}

double num_stack::Top(){
	return this->phead->num;
}

void num_stack::clear(){
	length = 0;
	num* cur = this->phead;
	delete cur;
	phead = NULL;
}
//str_stack function 
op* str_stack::BuyListNode(char ch){
	op* newnode = new op;
	//static SLTNode newnode£»
	if (newnode == NULL)
	{
		perror("malloc:");
		exit(0);
	}
	newnode->op = ch;
	newnode->next = NULL;
	return newnode;
}

str_stack::str_stack(){
	this->phead = NULL;
	length = 0;
}

str_stack::~str_stack(){
//	length = 0;
//	delete this->phead;
//	phead = NULL;
}

bool str_stack::Empty(){
	if(length == 0)
		return true;
	else
		return false;
}

int str_stack::Length(){
	return length;
}

void str_stack::Push(char ch){
	op* newnode = BuyListNode(ch);
	newnode->next = this->phead;
	this->phead = newnode;
}

void str_stack::Pop(){
	if (this->phead == NULL)
		return;
	op* head = this->phead;
	this->phead = this->phead->next;
	free(head);
	head = NULL;
	length--;
}

void str_stack::Print(){
	op* cur = this->phead;
	for(int i = 0;cur != NULL;i++){
		cout<<"op["<<i<<"]="<<cur->op<<" ";
		cur = cur->next;
	}
	cout<<endl;
}

char str_stack::Top(){
	return this->phead->op;
}

void str_stack::clear(){
	length = 0;
	op* cur = this->phead;
	delete cur;
	phead = NULL;
}
