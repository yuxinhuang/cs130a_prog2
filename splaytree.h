//splaytree.h
//Yuxin Huang 5557277
#ifndef SPLAYTREE_H
#define SPLAYTREE_H
#include<stdio.h> 
#include<stdlib.h> 
#include <iostream>
#include <utility>

class SplayTree{
public:
	SplayTree();
	~SplayTree();
	void find(int i);
	void insert(int i);
	void delete_(int i);
	void print();
private:
	struct Node{
		int i;
		Node *left, *right ;
		Node(int v=0) : i(v), left(0), right(0){ }
	};
	Node* root;
	void clear(struct Node*n); //delete node in heap
	//struct Node* newNode(int i); //helper function to create a new node with left right child being null
	Node* leftRotate(Node* n); //return the root 
	Node* rightRotate(Node* n); //return the root you are rotating
	Node* splay(Node* root, int i); 
	Node* access(int i); 
	Node* accesshelper(int i, Node* n);
	Node* getMax(Node* n);
	Node* getMin(Node* n);
	Node* join(Node* n1, Node *n2);
	std::pair<SplayTree,SplayTree> split(int i, SplayTree t);






};
#endif