//1
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <netinet/in.h>
/* dành riêng cho AF_INET */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <queue>
#include <stack>
#include <string.h>
#include <vector>
#include <cctype>
#include <algorithm>
#include <math.h>
using namespace std;

bool checkOperator(char a);

bool checkParentheses(string s)
{
	stack<char> Stack;
	for(int i = 0; i < s.size(); i++)
	{
		if(s[i] == '(')
		{
			Stack.push(s[i]);
		}
		else if(s[i] == ')')
		{
			Stack.pop();
		}
	}

	if(Stack.empty() == false)
	{
		return false;
	}
	return true;
}

bool checkRepete(string s)
{
	if(checkOperator(s[0]) == true || checkOperator(s[s.size()-1]) == true)
	{
		return false;
	}
	for(int i = 0; i < s.size() - 1; i++)
	{
		if(checkOperator(s[i]) == true && checkOperator(s[i+1]) == true)
		{
			return false;
		}
		if(s[i] == '(' && s[i+1] == ')')
		{
			return false;
		}
		if(s[i] == ')' && s[i+1] == '(')
		{
			return false;
		}
	}
	return true;
}

bool checkValidExp(string exp)
{
	for (int i = 0; i < exp.size(); i++)
	{
		if ((exp[i] - '0' > 9 || exp[i] - '0' < 0) && exp[i] != '+' && exp[i] != '-' && exp[i] != '*' && exp[i] != '/' && exp[i] != '(' && exp[i] != ')')
		{
			return 0;
		}
	}
	return 1;
}

bool checkCalculation(string s)
{
	if(checkParentheses(s) == false)
		return false;
	if(checkRepete(s) == false)
		return false;
	return true;
}

#define MAX_STACK 100
float _stack[MAX_STACK];
int tos = 0;

bool Full(){
	return tos >= MAX_STACK - 1;
}

bool Empty(){
	return tos == 0;
}

void Push(float value){
	if (Full()){
		return;
	}
	tos++;
	_stack[tos] = value;
}

float Pop(){
	float t = _stack[tos];
	tos--;
	return t;
}

int checkPriority(char a)
{
    if (a == '+' || a == '-')
        return 1;
    if (a == '*' || a == '/')
        return 2;
    return 0;
}

void infixToPostfix(string s, string &result)
{
    stack<char> st;

    for (int i = 0; i < s.length(); i++) 
    {
        char c = s[i];
        cout << c << " ";
        if (c >= '0' && c <= '9')
        {
            result += c;
        }
 
        else if (c == '(')
            st.push('(');
 
        else if (c == ')') {
            while (st.top() != '(') 
            {
                result += " ";
                result += st.top();
                st.pop();
            }
            st.pop();
        }
 
        else {
            result += " ";
            while (!st.empty() && checkPriority(s[i]) <= checkPriority(st.top())) {
                result += st.top();
                result += " ";
                st.pop();
            }
            st.push(c);
        }
    }
    
    while (!st.empty()) 
    {
        result += " ";
        result += st.top();
        st.pop();
    }

    cout << "r = " << result << endl;
 
}

bool checkOperator(char a)
{
   if(a == '+'|| a == '-'|| a == '*'|| a == '/')
      return true;
   return false;
}

int PolishNotation(string expression){
	int i = 0;
	float v1, v2, ret;
	v1 = ret = v2 = 0.0;

	string tok = "";

	while (i < expression.length()){
		
		while (isspace(expression[i])){
			i++;
		}
		
		if (isdigit(expression[i]) | expression[i] == '.'){
			while (isdigit(expression[i]) | expression[i] == '.'){
				tok += expression[i];
				i++;
			}
			
			Push(atof(tok.c_str()));
			tok = "";
		}
		
		else if (checkOperator(expression[i])){
			if (expression[i] == '+'){
				v1 = Pop();
				v2 = Pop();
				ret = (v1 + v2);
			}
			if (expression[i] == '-'){
				v1 = Pop();
				v2 = Pop();
				ret = v2 - v1;
			}
			if (expression[i] == '*'){
				v1 = Pop();
				v2 = Pop();
				ret = (v1 * v2);
			}
			if (expression[i] == '/'){
				v1 = Pop();
				v2 = Pop();
				ret = (v2 / v1);
			}
			i++;
			Push(ret);
		}
		else{
			cout << "Invaild Expression." << endl;
			break;
		}
	}
	return Pop();
}


int main()
{
	int server_sockfd, client_sockfd;
	socklen_t server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	
	//2
	server_sockfd = socket( AF_INET, SOCK_STREAM, 0 );
	
	//3
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr( "127.0.0.1" );
	server_address.sin_port = htons( 9734 );
	server_len = sizeof( server_address );
	
	//4
	bind( server_sockfd, (struct sockaddr *)&server_address, server_len );
	
	//5
	listen( server_sockfd, 5 );
	signal(SIGCHLD, SIG_IGN);
	//6
	while ( 1 ) {
		char ch[1025];
		printf( "server waiting...\n" );

		/* Chờ và chấp nhận kết nối */
		client_len = sizeof(client_address);
		client_sockfd = accept( server_sockfd, (struct sockaddr*)&client_address, &client_len );

		/* Đọc dữ liệu do trình khách gửi đến */
		if(fork() == 0)
		{
			recv( client_sockfd, &ch, 1024, 0);
			sleep(3);
			string s = "";
			for(int i = 0; i < strlen(ch); i++)
			{
				s = s + ch[i];
			}
			s.erase(remove_if(s.begin(), s.end(), ::isspace),s.end());
			if (checkCalculation(s) == 1 && checkValidExp(s) == 1)
			{
				char buff[1025];
				string postFix;
				infixToPostfix(s, postFix);
				int res = PolishNotation(postFix);
				sprintf(buff, "%d", res);
				/* Gửi trả dữ liệu về cho trình khách */
				write( client_sockfd, &buff,strlen(buff));
				close( client_sockfd );
				exit(0);
			}
			else
			{
				cout << "wrong\n";
				char buff[] = "Cu phap khong hop le";
				write( client_sockfd, &buff,strlen(buff));
				close( client_sockfd );
				exit(0);
			}
		}
		else
		{
			/* Đóng kết nối */
			close( client_sockfd );
		}
	}
}

