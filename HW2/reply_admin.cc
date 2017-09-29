#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NUM_OF_CHAT = 200;

size_t getChatCount(const string *_chatList){
	size_t i;
	for(i=0;i<NUM_OF_CHAT;++i)
		if(_chatList[i].empty())
			break;
	return i;
}

void printChat(const string *_chatList){
	for(int i=0, count=getChatCount(_chatList);i<count;++i)
		cout << i << " " << _chatList[i] << endl;
}

bool hasThatCMD(const string &cmd, const string &_chat){
	int pos = _chat.find(cmd);
	if(pos==string::npos) return false;
	while(--pos>=0)
		if(_chat[pos]!=' ' && _chat[pos]!='\t')
			return false;
	return true;
}

bool convertToInt(const string &str, int &v) {
	int i, size = str.size(), nums = 0;
	for (i = 0; i < size; ++i)
		if (str[i] == ' ' || str[i] == '/t') continue;
		else if(str[i] >= '0' && str[i] <= '9') nums++;
		else return false;
	sscanf(str.c_str(), "%d", &v);
	return nums>0;
}

bool addChat(string *_chatList, const string &_chat){
	size_t size = getChatCount(_chatList);
	// If the limit exceeds, fail to add a chat.
	if(size>=NUM_OF_CHAT)
		return false;
	// If a chat has some command, ignore it.
	if(hasThatCMD("#", _chat))
		return false;

	// Add chat
	_chatList[size] = _chat;
	return true;
}

bool isQuitCMD(const string &_chat){
	return hasThatCMD("#quit", _chat);
}

bool isRMCMD(const string &_chat){
	return hasThatCMD("#remove", _chat);
}

bool removeChat(string *_chatList, int _index){
	size_t size = getChatCount(_chatList);
	if(_index<0 || _index>=size || size==0)
		return false;
	
	for(size_t i=_index;i<size-1;++i)
		_chatList[i]=_chatList[i+1];

	_chatList[size-1].clear();
	return true;
}

vector<int> getRemovalList(const string &cmd){
	int cmd_pos, dash_pos, c_pos, size = cmd.size();
	vector<int> list;

	cmd_pos = cmd.find("#remove") + 7;
	dash_pos = cmd.find("-");
	c_pos = cmd.find(",");

	// In case when the input doesn't match the right form,
	if (dash_pos != string::npos && c_pos != string::npos)
		return list;
	else if(dash_pos != string::npos){
		int s, e;
		if (convertToInt(cmd.substr(cmd_pos, dash_pos - cmd_pos), s) &&
			convertToInt(cmd.substr(dash_pos + 1, size - dash_pos - 1), e))
			for (int i = s; i <= e; ++i)
				list.push_back(i);
	}else if(c_pos != string::npos){
		int x, pos = cmd_pos;
		do{
			if(convertToInt(cmd.substr(pos, c_pos - pos), x))
				list.push_back(x);
			pos = c_pos + 1;
			c_pos = cmd.find(",", c_pos + 1);
		}while (c_pos != string::npos);

		if (convertToInt(cmd.substr(pos, size - pos), x))
			list.push_back(x);
		sort(list.begin(), list.end());
	}
	else {
		int x;
		if (convertToInt(cmd.substr(cmd_pos, size - cmd_pos), x))
			list.push_back(x);		
	}
	vector<int>::iterator it = unique(list.begin(), list.end());
	list.erase(it, list.end());
	return list;
}

int main(){
	string *chats = new string[NUM_OF_CHAT];

	addChat(chats, "Hello, Reply Administrator!");
	addChat(chats, "I will be a good programmer.");
	addChat(chats, "THis class is awesome.");
	addChat(chats, "Professor Lim is wise.");
	addChat(chats, "Two TAs are kind and helpful.");
	addChat(chats, "I think TAs look cool.");

	while(true){
		string command;
		getline(cin, command);

		// quit
		if(isQuitCMD(command)) break;
		else if(isRMCMD(command))	//remove
		{
			vector<int> removal_list = getRemovalList(command);
			// remove chat
			size_t size = removal_list.size();
			if(size>=1){
				for(int i=size-1;i>=0;--i)
					removeChat(chats, removal_list[i]);
				printChat(chats);
			}
		}
		else if(addChat(chats, command))
			printChat(chats);
	}
	delete[] chats;
	return 0;
}
