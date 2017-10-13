#ifndef INC_REPLY_ADMIN
#define INC_REPLY_ADMIN

#define NUM_OF_CHAT 200

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

class ReplyAdmin
{
private:
	list<string> *chats;

public:
	ReplyAdmin();
	~ReplyAdmin();

	bool addChat(string _chat);
	bool removeChat(int _index);                // #remove #
	bool removeChat(list<int>& _indices);		// #remove #,#,#,#
	bool removeChat(int * _indices, int count);
	bool removeChat(int _start, int _end);      // #remove #-#
	void printChat();
};

#endif