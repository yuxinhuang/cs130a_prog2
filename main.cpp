//main.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "splaytree.h"
#include <stdlib.h>
#include <cstdlib>

using namespace std;
int main(){
	string num_ins;
	string ins; //instruction
	string data;
	cin>>num_ins; //the first line
	SplayTree tree;
	int num=atoi(num_ins.c_str());
	while (!cin.eof()){
		cin>>ins;
		if (ins=="insert"){
			cin>>data;
			tree.insert(atoi(data.c_str()));
			//cout<<"hello"<<endl;
			num--;
		}
		if (ins=="find"){
			cin>>data;
			tree.find(atoi(data.c_str()));
			num--;
		}
		if (ins=="delete"){
			cin>>data;
			tree.delete_(atoi(data.c_str()));
			num--;
		}
		if (ins=="print"){
			tree.print();
			num--;
			return 0;
		}
	}
	return 0;
}
