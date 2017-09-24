#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NUM_OF_CHAT = 200;

size_t getChatCount(string *_chatList){
	size_t i;
	for(i=0;i<NUM_OF_CHAT;++i)
		if(_chatList[i].empty())
			break;
	return i;
}

void printChat(string *_chatList){
	for(int i=0, count=getChatCount(_chatList);i<count;++i)
		cout << i << " " << _chatList[i] << endl;
}

bool hasThatCMD(string cmd, string _chat){
	int pos = _chat.find(cmd);
	if(pos==string::npos) return false;
	while(--pos>=0)
		if(_chat[pos]!=' ' && _chat[pos]!='\t')
			return false;
	return true;
}

bool addChat(string *_chatList, string _chat){
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

bool isQuitCMD(string _chat){
	return hasThatCMD("#quit", _chat);
}

bool isRMCMD(string _chat){
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

vector<int> getRemovalList(string cmd){
	int pos, dash_pos, c_pos, size = cmd.size(), s, e, x;
	pos = cmd.find_first_of("0123456789");
	vector<int> list;
	if(pos==string::npos) return list;
	dash_pos = cmd.find("-");
	c_pos = cmd.find(",");
	if(dash_pos != string::npos){
		sscanf(cmd.substr(pos,dash_pos-pos).c_str(), "%d", &s);
		sscanf(cmd.substr(dash_pos+1, size-dash_pos-1).c_str(), "%d", &e);
		for(int i=s;i<=e;++i)
			list.push_back(i);
	}else if(c_pos != string::npos){
		while(true){
			sscanf(cmd.substr(pos, c_pos-pos).c_str(), "%d", &x);
			list.push_back(x);
			if(c_pos>=size) break;
			pos = cmd.find_first_of("0123456789", c_pos+1);
			c_pos = cmd.find(",", pos+1);
			c_pos = c_pos==string::npos ? size : c_pos;
		}
		sort(list.begin(), list.end());
	}else{
		sscanf(cmd.substr(pos, size-pos).c_str(), "%d", &x);
		list.push_back(x);
	}
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
			if(size==1){
				if(removeChat(chats, removal_list[0]))
					printChat(chats);
			}else{
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
