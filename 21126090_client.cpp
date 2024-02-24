//1
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;


int main()
{
	int sockfd; 
	int len;
	struct sockaddr_in address; 
	int result;
	char ch[2001];
	char buff[2001];
	string s;
	cout << "Nhap bieu thuc: ";
	getline(cin, s);
	for(int i = 0; i < s.size(); i++)
	{
		ch[i] = s[i];
	}
	ch[s.size()] = '\0';
	//2
	sockfd = socket( AF_INET, SOCK_STREAM, 0 );
	
	//3
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr( "127.0.0.1" );
	address.sin_port = htons( 9734 );
	len = sizeof( address );
	
	//5
	result = connect( sockfd, (struct sockaddr*)&address, len );
	if ( result == -1 ) {
		perror( "Oops: client1 problem" );
		return 1;
	}
	
	//5
	send( sockfd, &ch, s.size() + 1, 0);
	recv( sockfd, &buff, 2000, 0);
	string res = "";
	for(int i = 0; i < strlen(buff); i++)
	{
		res = res + buff[i];
	}
	cout << "Result: ";
	cout << res << endl;
	close( sockfd );
	return 0;
}