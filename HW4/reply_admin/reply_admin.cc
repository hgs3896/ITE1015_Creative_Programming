#include "reply_admin.h"

ReplyAdmin::ReplyAdmin() {
	chats = new list<string>;
}

ReplyAdmin::~ReplyAdmin() {
	delete[] chats;
}

bool ReplyAdmin::addChat(string _chat) {
	if (chats->size() >= NUM_OF_CHAT) 
		return false;
	chats->push_back(_chat);
	return true;
}

bool ReplyAdmin::removeChat(int _index)                // #remove #
{
	int size = chats->size();
	if (_index<0 || _index>=size)
		return false;
	auto it = chats->begin();
	for (int i = 0; i < _index; ++i) ++it;
	chats->erase(it);
	return true;
}

bool ReplyAdmin::removeChat(int * _indices, int count) {
	list<int> indices;
	for (int i = 0; i < count; ++i)
		indices.push_back(_indices[i]);
	return removeChat(indices);
}

bool ReplyAdmin::removeChat(list<int>& _indices) { // #remove #,#,#,#
	bool successful = false;
	_indices.sort();
	_indices.erase(unique(_indices.begin(), _indices.end()), _indices.end());
	for (auto it = _indices.rbegin(); it != _indices.rend(); ++it)
		successful |= removeChat(*it);
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
	int i = 0;
	for (auto it = chats->begin(); it != chats->end(); ++it)
		cout << i++ << " " << *it << endl;
}