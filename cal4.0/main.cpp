#include"c_stack.h"

void handle();
void handle_cal();
void handle_pra();

bool check(string s);
char compare(string s,str_stack str);
double str_double(string s);
char str_char(string s);
void str_split(string s,vector<string> &result);
double keep(double &n,int k);
void operate(num_stack &num1,str_stack &str);
void calculation(vector<string> result,num_stack &num1,str_stack &str);

double randomDouble(int min, int max);
int randomInt(int min, int max);
string generateExpression();
string mingenerateExpression();
void writedata(string a,double x);

int main() {
	srand(time(NULL));
	num_stack num1;
	str_stack str;
	str.Push('=');
	string s,ans;
	vector<string> result;
	int cnt = 5;
	int score = 0;
	int k;
	while(cnt--) {
		s = mingenerateExpression();
		str_split(s,result);
		calculation(result,num1,str);
		cout<<s;
		if(score >= 3){
			cout<<"\n是否使用三分换答案：(y/n):";
			cin>>ans;
			if(ans == "y" || ans == "Y"){
				cout<<"本题答案为："<<num1.Top()<<endl;
				score-=3;
				cout<<"现在得分"<<score<<endl;
				writedata(s,num1.Top());
				result.clear();
				continue;
			}
		}
		cin>>k;
		if(k == num1.Top()){
			score++;
			cout<<"结果正确，得分加一"<<endl;
			cout<<"现在得分："<<score<<endl;
		}
		else{
			if(score > 0){
				score--;
				cout<<"结果错误，得分减一"<<endl;
				cout<<"现在得分："<<score<<endl;
			}
			else{
				cout<<"结果错误"<<endl;
				cout<<"现在得分："<<score<<endl;
			}
		}
		result.clear();
	}
	return 0;
}
//string to double
double str_double(string s) {
	int len = s.length();
	double num = 0;
	int flag = 0;//确定为几位小数 
	for(int i = 0; i < len; i++) {
		if(s[i] == '.') {
			flag--;
			continue;
		}
		if(flag == 0)
			num = num*10 + (s[i] - '0');
		else {
			num = num + (s[i] - '0')*pow(10,flag);
			flag--;
		}
	}
	return num;
}
//string to char
char str_char(string s) {
	char ch;
	ch = s[0];
	return ch;
}
//number return true
bool check(string s) {
	int len = s.length();
	for(int i = 0; i < len; i++) {
		if((s[i] >= '0' && s[i] <= '9') || s[i] == '.')
			return true;
	}
	return false;
}
//比较运算符级别
char compare(string s,str_stack str) {
	if(s == "+" || s== "-")
		switch(str.Top()) {
			case '=':
			case '(':
				return '<';
			default:
				return '>';
		}
	else if(s == "*" || s == "/")
		switch(str.Top()) {
			case '*':
			case '/':
				return '>';
			default:
				return '<';
		}
	else if(s == "(")
		return '<';
	else if(s == "=")
		switch(str.Top()) {
			case '=':
				return '=';
			default:
				return '>';
		}
	else if(s == ")")
		return '>';
}
//进行运算
void operate(num_stack &num1,str_stack &str) {
//	cout<<"operate function"<<endl;
//	cout<<"num1.Top="<<num1.Top()<<endl;
	double a = num1.Top();
	num1.Pop();
//	cout<<"num1.Top="<<num1.Top()<<endl;
	double b = num1.Top();
	num1.Pop();
//	cout<<"a="<<a<<" b="<<b<<endl;
//	cout<<"str.top="<<str.Top()<<endl;
	switch(str.Top()) {
		case '+':
			num1.Push(b+a);
			break;
		case '-':
			num1.Push(b-a);
			break;
		case '*':
			num1.Push(b*a);
			break;
		case '/':
			double n = b/a;
			num1.Push(keep(n,2));
			break;
	}
	str.Pop();
}
//保留k位小数
double keep(double &n,int k) {
	n = n*pow(10,k);
	double x = (int)n;
	if(n-x >= 0.5)
		return (x+1)/pow(10,k);
	else
		return x/pow(10,k);
}
//分割运算式
void str_split(string s,vector<string> &result) {
	string part;
	char c;
	for (int j = 0; j < s.length(); j++) {
		c = s[j];
		if (c == '+' || c == '-' || c == '=' || c == '*' || c == '/' || c == '(' || c == ')') {
			if (!part.empty()) {
				result.push_back(part);
				part.clear();
			}
			result.push_back(string(1, c));
		} else {
			part += c;
		}
	}
	if (!part.empty()) {
		result.push_back(part);
	}
//	for(int j = 0;j < result.size();j++)
//	    cout<<"result["<<j<<"]="<<result[j]<<endl;
}
// 生成指定范围内的随机浮点数
double randomDouble(int min, int max) {
	double num = (double)(rand()%max+min)/10;
	return num;
}
// 生成指定范围内的随机整数
int randomInt(int min, int max) {
	int num = rand()%max+min;
	return num;
}
// 生成复杂随机算术表达式
string generateExpression() {
	ostringstream oss;
	double num1 = randomDouble(1,98);
	double num2 = randomDouble(10,98);
	double num3 = randomDouble(10,98);
	int op1 = randomInt(1, 4);
	int op2 = randomInt(1, 4);
	int flag = rand()%2;
	if(op1%2 == op2%2 || (op1%2 == 1&&op2%2 == 0))
		flag = 1;
	oss << num1;
	if (op1 == 1)
		oss << "+";
	else if (op1 == 3)
		oss << "-";
	else if (op1 == 2)
		oss << "*";
	else if (op1 == 4)
		oss << "/";

	if(flag == 0)
		oss << "(" ;
	oss << num2;
	if (op2 == 1)
		oss << "+";
	else if (op2 == 3)
		oss << "-";
	else if (op2 == 2)
		oss << "*";
	else if (op2 == 4)
		oss << "/";
	oss << num3;
	if(flag == 0)
		oss << ")";
	oss << "=";
	return oss.str();
}
// 生成简单随机算术表达式
string mingenerateExpression() {
	ostringstream oss;
	int num1 = randomInt(1,50);
	int num2 = randomInt(1,50);
	int op1 = randomInt(1, 4);

	oss << num1;
	if (op1 == 1)
		oss << "+";
	else if (op1 == 3)
		oss << "-";
	else if (op1 == 2)
		oss << "*";
	else if (op1 == 4)
		oss << "/";
	oss << num2 <<"=";
	return oss.str();
}
//记录题目 
void writedata(string a,double x){
	fstream datafile;
	datafile.open("题库.txt",ios_base::out|ios::app);
	if(!datafile){
		cout<<"file can't open"<<endl;
		abort();
	}
	datafile<<a<<x<<endl;
	datafile.close();
} 
//计算整个结果 
void calculation(vector<string> result,num_stack &num1,str_stack &str){
	int i = -1;
	do {
		i++;
		if(check(result[i])) {
			num1.Push(str_double(result[i]));
		} 
		else {
//			cout<<"result["<<i<<"]="<<result[i]<<endl;
//			cout<<"str.Top="<<str.Top()<<endl;
//			cout<<"compare(result[i],str)="<<compare(result[i],str)<<endl;
			switch(compare(result[i],str)) {
				case '<':
					str.Push(str_char(result[i]));
					break;
				case '>':
					operate(num1,str);
					if(result[i] != ")" && result[i] != "=")
						str.Push(str_char(result[i]));
					else if(result[i] == ")")
						str.Pop();
					break;
				case '=':
					str.Pop();
					break;
			}
		}
//		cout<<"result["<<i<<"]="<<result[i]<<endl;
	} while(result[i] != "=");
//		cout<<"str.Top="<<str.Top()<<endl;
	while(str.Top() != '=') {
		operate(num1,str);
	}
}
