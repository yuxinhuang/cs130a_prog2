//main.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "splaytree.h"
using namespace std;
int main(){
	string num_ins;
	string ins; //instruction
	string data;
	cin>>num_ins; //the first line
	SplayTree tree;
	int num=stoi(num_ins);
	while (num!=0){
		cin>>ins;
		if (ins=="insert"){
			cin>>data;
			tree.insert(stoi(data));
			cout<<"hello"<<endl;
			num--;
		}
		if (ins=="find"){
			cin>>data;
			tree.find(stoi(data));
			num--;
		}
		if (ins=="delete"){
			cin>>data;
			tree.delete_(stoi(data));
			num--;
		}
		if (ins=="print"){
			tree.print();
			num--;
		}
	}
	return 0;
}