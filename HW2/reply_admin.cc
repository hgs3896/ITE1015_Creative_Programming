#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

using namespace std;

const int NUM_OF_CHAT = 200;

unsigned int getChatCount(string *_chatList){
	unsigned int i;
	for(i=0;i<NUM_OF_CHAT;++i)
		if(_chatList[i].empty())
			break;
	return i;
}

void printChat(string *_chatList){
	for(int i=0, count=getChatCount(_chatList);i<count;++i)
		cout << i << " " << _chatList[i] << endl;
}

// Implement these functions
bool addChat(string *_chatList, string _chat){
	unsigned int size = getChatCount(_chatList);
	if(size>=NUM_OF_CHAT) return false;
	_chatList[size] = _chat;
	return true;
}

bool removeChat(string *_chatList, int _index){
	unsigned int size = getChatCount(_chatList);
	if(_index<0 || _index>=size)
		return false;
	
	for(int i=_index;i<size-1;++i)
		_chatList[i]=_chatList[i+1];

	_chatList[size-1].clear();
	return true;
}

bool isQuitCMD(string command){
	int pos = command.find("#quit");
	if(pos==string::npos) return false;
	while(--pos>=0)
		if(command[pos]!=' ') return false;	
	return true;
}

bool isRMCMD(string command){
	int i, pos;
	pos = command.find("#remove");
	if(pos==string::npos) return false;
	for(i=0;i<pos;++i)
		if(command[i]!=' ') return false;
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
			for(int i=removal_list.size()-1;i>=0;--i)
				removeChat(chats, removal_list[i]);
			printChat(chats);
		}
		else if(addChat(chats, command))
			printChat(chats);
	}
	delete[] chats;
	return 0;
}
