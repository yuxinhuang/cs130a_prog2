//splaytree.cpp
//Yuxin Huang 5557277
#include "splaytree.h"
#include <queue>
using namespace std;
SplayTree::SplayTree() : root(0){} 

SplayTree::~SplayTree(){
	clear(root);
}
void SplayTree::clear(Node*n){
	if (n){
	clear(n->left);
	clear(n->right);
	delete n;
	}
}
/*
struct Node* SplayTree::newNode(int i){
	struct Node* Node = (struct Node*)malloc(sizeof(struct Node)); 
	Node->i=i;
	Node->left=Node->right=NULL;
	return (Node);
}
*/
SplayTree::Node* SplayTree::rightRotate(Node*n){ 
	Node* m=n->left;
	n->left=m->right;
	m->right=n;
	cout<<"right"<<endl;
	return m;
}
SplayTree::Node* SplayTree::leftRotate(Node*n){
	Node* m=n->right;
	n->right=m->left;
	m->left=n;
	cout<<"left"<<endl;
	return m;
}

SplayTree::Node* SplayTree::splay(Node* root, int i){
	//base case: root is null or present at root
	if (root==NULL||root->i==i){
		cout<<"hi"<<endl;
		return root;
	}
	//key lies in the left subtree
	if (root->i>i){
		if (root->left==NULL){
			cout<<"hi"<<endl;
			return root;
		}
		//zig-zig
		if (root->left->i>i){
			root->left->left=splay(root->left->left,i);
			root=rightRotate(root);

		}
		else if (root->left->i<i){
			root->left->right=splay(root->left->right,i);
			if (root->left->right!=NULL)
				root->left = leftRotate(root->left);

		}
		if (root->left==NULL){
			cout<<"hi"<<endl;
			return root;
		}else{
			root= rightRotate(root);
			cout<<"hi"<<endl;
			return root;
		}

	}else{//key lies in the right subtree
		if (root->right==NULL){
			cout<<"hi"<<endl;
			return root;
		}
		//zig-zag
		if (root->right->i>i){
			root->right->left=splay(root->right->left,i);
			if (root->right->left!=NULL){
				root->right=rightRotate(root->right);
			}
		}
		else if(root->right->i<i){ //zig-zig
			root->right->right = splay(root->right->right, i);
			root = leftRotate(root); 
		}
		if (root->right==NULL){
			cout<<"hi"<<endl;
			return root;
		}else{
			root=leftRotate(root);
			cout<<"hi"<<endl;
			return root;
		}


	}

}

SplayTree::Node* SplayTree:: accesshelper(int i, Node* n){
	//cout<<"hi"<<endl;
	if ((n->left==NULL) && (n->right==NULL))
		splay(n, i);
	if (n->i==i) 
		splay (n,i);
	if (n==NULL || n->i==i){

		return n;
	}
	if (i<n->i){
		return accesshelper(i, n->left);
	}
	return accesshelper(i, n->right);
}
SplayTree::Node* SplayTree:: access (int i){
	return accesshelper(i, root);

}
SplayTree::Node* SplayTree::getMax(Node* n){
	Node* current= n;
	while (current->right!=NULL){
		current=current->right;

	}
	return current;
}
SplayTree::Node* SplayTree::getMin(Node* n){
	Node* current= n;
	while (current->left!=NULL){
		current=current->left;

	}
	return current;	
}
/*
SplayTree SplayTree:: join(SplayTree t1, SplayTree t2){
	if (((t1.getMax(t1.root))->i)>=((t2.getMin(t2.root))->i)){ 
		int max2=(t2.getMax(t2.root))->i;

		t2.splay(t2.getMax(t2.root), max2);
		t2.root->right=t1.root;
		return t2;
	}
	int max1= (t1.getMax(t1.root))->i;
	t1.splay(t1.getMax(t1.root),max1);
	t1.root->right=t2.root;
	return t1;

}
*/
SplayTree::Node*  SplayTree:: join(Node* n1, Node *n2){
	if ((getMax(n1)->i)>=getMin(n2)->i){ 
		int max2=getMax(n2)->i;
		splay(n2, max2);

		n2->right=n1;
		return n2;
	}
	int max1=getMax(n2)->i;
	splay(n1, max1);
	n1->right=n2;
	return n1;

}

pair<SplayTree,SplayTree> SplayTree::split(int i, SplayTree t){
	t.access(i);
	SplayTree t2;
	if (t.root->i>i){
		t2.root=t.root->left;
		t.root->left=NULL;
		return (make_pair(t2, t));
	}else{
		t2.root=t.root->right;
		t.root->right=NULL;
		return (make_pair(t, t2));
	}

}

void SplayTree::find(int i){
	Node *n=access (i);
	if (n==NULL){
		cout<<"item "<<i<<" not found"<<endl;
		return;
	}
	cout<< "item "<<i<<" found"<<endl;
	return;
}

void SplayTree::insert(int i){
	access(i);
	if ((root->i)!=i){
		pair<SplayTree,SplayTree> tree=split(i, *this);
		Node* n= new Node;
		n->i=i;
		n->left=(tree.first).root;
		n->right=(tree.second).root;
		this->root=n;
		cout<<"item "<<i<<" inserted"<<endl;
		return;
	}else{
		cout<<"item "<<i<<" not inserted; already present"<<endl;
		return;
	}


}

void SplayTree:: delete_(int i){
	access(i);
	if ((root->i)==i){
		Node* m= join(root->left,root->right);
		this->root->left=NULL;
		this->root->right=NULL;
		delete root;
		this->root=m;
		cout<<"item "<<i<<" deleted"<<endl;
		return;
	}else{
		cout<<"item "<<i<< " not deleted; not present"<<endl;
		return;
	}

}
void SplayTree:: print(){
	Node* n=root;
	queue<Node*> q;
	if (n){
		q.push(n);
		cout<<n->i<<endl;
	}
	while (!q.empty()){
		Node *m=q.front();
		q.pop();
		if (m->left){
			q.push(m->left);
			cout<<m->left->i<<endl;	
		}
		if (m->right){
			q.push(m->right);
			cout<<m->right->i<<endl;

		}
	}
}