#include "reply_admin.h"
#include <vector>
#include <algorithm>
#include <iostream>

ReplyAdmin::ReplyAdmin() {
	chats = new string[NUM_OF_CHAT];
}

ReplyAdmin::~ReplyAdmin() {
	delete[] chats;
}

int ReplyAdmin::getChatCount() {
	int i;
	for (i = 0; i < NUM_OF_CHAT; ++i)
		if (chats[i].empty())
			break;
	return i;
}

bool ReplyAdmin::addChat(string _chat) {
	int size = getChatCount();
	if (size >= NUM_OF_CHAT) 
		return false;
	chats[size] = _chat;
	return true;
}

bool ReplyAdmin::removeChat(int _index)                // #remove #
{
	int size = getChatCount();
	if (_index<0 || _index>=size)
		return false;
	int i;
	for (i = _index; i < size - 1; ++i)
		chats[i] = chats[i+1];
	chats[i].clear();
	return true;
}

bool ReplyAdmin::removeChat(int *_indices, int _count) { // #remove #,#,#,#
	vector<int> list(_indices, _indices+_count);
	vector<int>::iterator it;
	bool successful = false;
	sort(list.begin(), list.end());
	it = unique(list.begin(), list.end());
	list.erase(it, list.end());
	for (int i = list.size() - 1; i >= 0; --i)
		successful |= removeChat(list[i]);
	return successful;
}

bool ReplyAdmin::removeChat(int _start, int _end) {      // #remove #-#
	int i;
	bool successful = false;
	for (i = _end; i >= _start; --i)
		successful |= removeChat(i);
	return successful;
}

void ReplyAdmin::printChat() {
	for (int i = 0, size = getChatCount(); i < size; ++i)
		cout << i << " " <<chats[i] << endl;
}