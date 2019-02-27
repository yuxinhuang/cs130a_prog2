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


SplayTree::Node* SplayTree::rightRotate(Node*n){ 
	if (n==NULL)
		return n;

	Node* m=n->left;
	if (m==NULL)
		return n;

	n->left=m->right;
	m->right=n;
	//cout<<"right"<<endl;
	return m;
}
SplayTree::Node* SplayTree::leftRotate(Node*n){
	if (n==NULL)
		return n;

	Node* m=n->right;
	if (m==NULL)
		return n;
	n->right=m->left;
	m->left=n;
	//cout<<"left"<<endl;
	return m;
}

SplayTree::Node* SplayTree::splay(Node* root, int i){
	//base case: root is null or present at root
	if (root==NULL||root->i==i){
		//cout<<"hi"<<endl;
		return root;
	}
	if (root->i>i){ //in the left subtree
		if (root->left==NULL) //no node in the left subtree
			return root;
		if (root->left->i==i){ //zig
			root=rightRotate(root);
			return root;
		}
		else if ((root->left->i)>i){// left zig-zig
			if (root->left->left==NULL){
				root=rightRotate(root);
				return root;
			}
			if ((root->left->left->i==i) || ((root->left->left->left==NULL)&&(root->left->left->right==NULL))){ //splay on rll
				root=rightRotate(root);
				root=rightRotate(root);
				return root;
			}
			if (i<root->left->left->i){//rlll
				if (root->left->left->left==NULL){
					root=rightRotate(root);
					root=rightRotate(root);
					return root;
				}
				if (((root->left->left->left->left==NULL)&&(root->left->left->left->right==NULL))||( root->left->left->left->i==i)){//4 layers
					root->left=rightRotate(root->left);
					root->left=rightRotate(root->left);
					root=rightRotate(root);
					return root;

				}
				//cout<<"done"<<endl;

				Node *m=root->left->left->left;
				//cout<<"m->i: "<<m->i<<endl;
				 if (i<m->i){
					if (m->left==NULL){ //4layers splay
				 		root->left=rightRotate(root->left);
				 		root->left=rightRotate(root->left);
				 		root=rightRotate(root);
						return root;

				 	}
				 }
				 if (i>m->i){
				 	if (m->right==NULL){
				 		//cout<<"hi"<<endl;
				 		root->left=rightRotate(root->left);
				 		root->left=rightRotate(root->left);
				 		root=rightRotate(root);
				 		return root;
					}
				 }

			}
			if (i>root->left->left->i){ //rllr
				if (root->left->left->right==NULL){
					root=rightRotate(root);
					root=rightRotate(root);
					return root;

				}
				if (((root->left->left->right->left==NULL)&&(root->left->left->right->right==NULL))|| ( root->left->left->right->i==i)){
					root->left->left=leftRotate(root->left->left);
					root->left=rightRotate(root->left);
				
					root=rightRotate(root);
					return root;
				}
				Node *m=root->left->left->right;
				if (i<m->i){//rllrl
					if (m->left==NULL){
						root->left->left=leftRotate(root->left->left);
						root->left=rightRotate(root->left);
				
						root=rightRotate(root);
						return root;
					}
				}
				if (i>m->i){
					if (m->right==NULL){
						root->left->left=leftRotate(root->left->left);
						root->left=rightRotate(root->left);
				
						root=rightRotate(root);
						return root;
					}
				}
			}
		
				
				root->left->left=splay(root->left->left, i);
				root=rightRotate(root);
				root=rightRotate(root);
				return root ;
			

		}
		else{ //left zig-zag
			if (root->left->right==NULL){ //splay on root->left
				root=rightRotate(root);
				return root;
			}
			if (((root->left->right->left==NULL )&& (root->left->right->right==NULL) )|| (root->left->right->i==i)){ //splay on rlr
				root->left=leftRotate(root->left);
				root=rightRotate(root);
				return root;
			}
			if (i<root->left->right->i){ //rlrl
				if (root->left->right->left==NULL){
					root->left=leftRotate(root->left);
					root=rightRotate(root);
					return root;

				}
				if (((root->left->right->left->left==NULL)&&(root->left->right->left->right==NULL))|| ( root->left->right->left->i==i)){
					root->left->right=rightRotate(root->left->right);
					root->left=leftRotate(root->left);
					root=rightRotate(root);
					return root;
				}
				Node *m=root->left->right->left;
				if (i<m->i){
					if (m->left==NULL){
						root->left->right=rightRotate(root->left->right);
						root->left=leftRotate(root->left);
						root=rightRotate(root);
						return root;
					}
				}
				if (i>m->i){
					if (m->right==NULL){
						root->left->right=rightRotate(root->left->right);
						root->left=leftRotate(root->left);
						root=rightRotate(root);
						return root;
					}
				}
			}
			if (i>root->left->right->i){//rlrr
				if (root->left->right->right==NULL){
					root->left=leftRotate(root->left);
					root=rightRotate(root);
					return root;
				}
				if (((root->left->right->right->left==NULL)&&(root->left->right->right->right==NULL))|| ( root->left->right->right->i==i)){
					root->left=leftRotate(root->left);
					root->left=leftRotate(root->left);
					root=rightRotate(root);
					return root;
				}
				Node *m=root->left->right->right;
				if (i<m->i){
					if (m->left==NULL){
						root->left=leftRotate(root->left);
						root->left=leftRotate(root->left);
						root=rightRotate(root);
						return root;
					}
				}
				if (i>m->i){
					if (m->right==NULL){
						root->left=leftRotate(root->left);
						root->left=leftRotate(root->left);
						root=rightRotate(root);
						return root;
					}
				}

			}
			
			
				root->left->right= splay(root->left->right,i);
				root->left=leftRotate(root->left);
				root=rightRotate(root);
				return root;
			}
	}else{ //in the right subtree
		if (root->right==NULL){
			return root;
		}
		if ((root->right->i)==i){ //zig
			root= leftRotate(root);
			return root;
		}
		else if (root->right->i<i){ //right zigzig
			if (root->right->right==NULL){ //splay on root->right
				root=leftRotate(root);
				return root;
			}
			if ((root->right->right->i==i) || ((root->right->right->left==NULL)&&(root->right->right->right==NULL))){ //splay on rrr

				root=leftRotate(root);
				root=leftRotate(root);

				return root;
			}
			if (i<root->right->right->i){ //rrrl
				if (root->right->right->left==NULL){
					root=leftRotate(root);
					root=leftRotate(root);

					return root;
				}
				if ((root->right->right->left->i==i) ||((root->right->right->left->left==NULL)&& (root->right->right->left->right==NULL)) ){//4 layers
					root->right->right=rightRotate(root->right->right);
					root->right=leftRotate(root->right);
					root=leftRotate(root);
					return root;
				}
				Node *m=root->right->right->left;
				if (i<m->i){
					if (m->left==NULL){
						root->right->right=rightRotate(root->right->right);
						root->right=leftRotate(root->right);
						root=leftRotate(root);
						return root;

					}
				}
				if (i>m->i){
					if (m->right==NULL){
						root->right->right=rightRotate(root->right->right);
						root->right=leftRotate(root->right);
						root=leftRotate(root);
						return root;

					}
				}


			}
			if (i>root->right->right->i){ //rrrr
				if (root->right->right->right==NULL){
					root=leftRotate(root);
					root=leftRotate(root);

					return root;

				}
				if ((root->right->right->right->i==i) ||((root->right->right->right->left==NULL)&& (root->right->right->right->right==NULL)) ){
					root->right=leftRotate(root->right);
					root->right=leftRotate(root->right);
					root=leftRotate(root);
					return root;
				}
				Node *m = root->right->right->right;
				if (i<m->i){
					if (m->left==NULL){
						root->right=leftRotate(root->right);
						root->right=leftRotate(root->right);
						root=leftRotate(root);
						return root;
					}
				}
				if (i>m->i){
					if (m->right==NULL){
						root->right=leftRotate(root->right);
						root->right=leftRotate(root->right);
						root=leftRotate(root);
						return root;
					}
				}


			}
			
				//root->right->right = splay(root->right->right, i);
				//root = leftRotate(root); 
				root->right->right=splay(root->right->right, i);
				//root->right->right=splay(root->right->right, i);
				root=leftRotate(root);
				root=leftRotate(root);
				//root=leftRotate(root);
				return root;
			}
		
		else{ //right zigzag
			if (root->right->left==NULL){//splay on root->right
				root=leftRotate(root);
				
				return root;
			}
			if (((root->right->left->left==NULL) && (root->right->left->right==NULL) )|| (root->right->left->i==i)){ //rrl
				root->right=rightRotate(root->right);
				root=leftRotate(root);
				return root;
			}
			if (i<root->right->left->i){//rrll
				if (root->right->left->left==NULL){
					root->right=rightRotate(root->right);
					root=leftRotate(root);
					return root;
				}
				if ((root->right->left->left->i==i)|| ((root->right->left->left->left==NULL)&&(root->right->left->left->right==NULL))){
					root->right=rightRotate(root->right);
					root->right=rightRotate(root->right);
					root=leftRotate(root);
					return root;
				}
				Node*m=root->right->left->left;
				if (i<m->i){
					if (m->left==NULL){
						root->right=rightRotate(root->right);
						root->right=rightRotate(root->right);
						root=leftRotate(root);
						return root;
					}
				}
				if (i>m->i){
					if (m->right==NULL){
						root->right=rightRotate(root->right);
						root->right=rightRotate(root->right);
						root=leftRotate(root);
						return root;
					}
				}


			}
			if (i>root->right->left->i){//rrlr
				if (root->right->left->right==NULL){
					root->right=rightRotate(root->right);
					root=leftRotate(root);
					return root;
				}
				if ((root->right->left->right->i==i)|| ((root->right->left->right->left==NULL)&&(root->right->left->right->right==NULL))){
					root->right->left=leftRotate(root->right->left);
					root->right=rightRotate(root->right);
					root=leftRotate(root);
				    return root;
				}
				Node*m=root->right->left->right;
				if (i<m->i){
					if (m->left==NULL){
						root->right->left=leftRotate(root->right->left);
						root->right=rightRotate(root->right);
						root=leftRotate(root);
				    	return root;
					}
				}
				if (i>m->i){
					if (m->right==NULL){
						root->right->left=leftRotate(root->right->left);
						root->right=rightRotate(root->right);
						root=leftRotate(root);
				    	return root;
					}
				}

			}

				root->right->left= splay(root->right->left,i);
				root->right=rightRotate(root->right);
				root=leftRotate(root);
				return root;
				
				
			
		}

	}
	
}


/*
SplayTree::Node* SplayTree::splay(Node* root, int i){
	if (!root)
		return NULL;
	
	Node header;
	header.left=header.right=NULL;
	Node* leftTreeMax=&header;
	Node* rightTreeMin=&header;
	while(1){
		if (i<root->i){
			if (!root->left)
				break;
			if (i<root->left->i){
				root=rightRotate(root);
				if (!root->left)
					break;
			}
			rightTreeMin->left=root;
			rightTreeMin=rightTreeMin->left;
			root=root->left;
			rightTreeMin->left=NULL;
		}
		else if (i>root->i){
			if (!root->right)
				break;
			if (i>root->right->i){
				root=leftRotate(root);
				if (!root->right)
					break;

			}
			leftTreeMax->right=root;
			leftTreeMax=leftTreeMax->right;
			root=root->right;
			leftTreeMax->right=NULL;

		}
		else
			break;
	}
	leftTreeMax->right=root->left;
	rightTreeMin->left=root->right;
	root->left=header.right;
	root->right=header.left;
	return root;

	
	//base case: root is null or present at root
	if (root==NULL||root->i==i){
		//cout<<"hi"<<endl;
		return root;
	}
	//key lies in the left subtree
	if (root->i>i){
		if (root->left==NULL){
			//cout<<"hi"<<endl;
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
		if (root->left){
			//cout<<"hi"<<endl;
			root= rightRotate(root);
			return root;
		}
		return root;

	}else{//key lies in the right subtree
		if (root->right==NULL){
			//cout<<"hi"<<endl;
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
		if (root->right){
			//cout<<"hi"<<endl;
			root=leftRotate(root);
			return root;
		}
		return root;


	}
	

}
*/

SplayTree::Node* SplayTree:: accesshelper(int i, Node* n){
	return splay(n,i);
}
SplayTree::Node* SplayTree:: access (int i){
	return accesshelper(i, this->root);

}

SplayTree::Node* SplayTree::getMax(Node* n){
	//cout<<"h1"<<endl;
	Node* current=n;
	//cout<<n->i<<endl;
		while (current->right){

		current=current->right;
	}
	//cout<<"h2"<<endl;
	return current;
}

SplayTree::Node*  SplayTree:: join(Node* n1, Node *n2){ //assume t1<t2

	if (n1==NULL && n2==NULL){
		return n1;
	}
	if (n1==NULL){
		return n2;
	}


	int max1=getMax(n1)->i;
	splay(n1, max1);
	n1->right=n2;
	return n1;

}
pair<SplayTree::Node*, SplayTree::Node*> SplayTree::split(int i, Node* n){
	n=access(i);
	
	
	if (n->i>i){

		Node* n2=n->left;
		n->left=NULL;
		return (make_pair(n2, n));
	}else{
		Node* n2=n->right;
		n->right=NULL;
		return (make_pair(n, n2));
	}

}


void SplayTree::find(int i){
	this->root=access (i);
	if (this->root==NULL){
		cout<<"item "<<i<<" not found"<<endl;
		return;
	}
	if (i==this->root->i){
		cout<< "item "<<i<<" found"<<endl;
		return;
	}
	//print();
	cout<< "item "<<i<<" not found"<<endl;
	return;
}

void SplayTree::insert(int i){
	this->root=access(i);
	if (this->root==NULL){
		Node* n= new Node;
		n->i=i;
		n->right=NULL;
		n->left=NULL;
		this->root=n;
		
		cout<<"item "<<i<<" inserted"<<endl;
		//print();
		return ;
	}
	if (this->root->i==i){
		//print();
		cout<<"item "<<i<<" not inserted; already present"<<endl;
		return;
		
	}
	pair<Node*, Node*> tree=split(i, this->root);
	
	Node* n= new Node;
	n->i=i;
	n->right=tree.second;
	n->left=tree.first;
	this->root=n;
	cout<<"item "<<i<<" inserted"<<endl;
	//print();
	return ;



}

void SplayTree:: delete_(int i){
	this->root=access(i);
	//cout<<"this->root: "<<this->root->i<<endl;
	if (this->root==NULL){
		//print();
		cout<<"item "<<i<< " not deleted; not present"<<endl;
		return;
	}
	
	if (this->root->i==i){ //if we find the node 
		if (root->left==NULL && root->right==NULL){
			delete root;
			root=NULL;
			return;
		}

		if (root->left==NULL){
			delete root;
			root=root->right;
			return;
		}
		if (root->right==NULL){
			int max=getMax(root->left)->i;
			splay(root->left, max);
			Node *n=root->left;
			delete root;
			root=n;
			return;
		}
	
		Node* m= join(root->left,root->right);
	//	cout<<"m :"<<m->i<<endl;
		delete this->root;
		this->root=m;
		//print();
		cout<<"item "<<i<<" deleted"<<endl;
		return;
		
	}
	//print();
	cout<<"item "<<i<< " not deleted; not present"<<endl;
	return;
	
}
void SplayTree:: print(){

    // Base Case  
    if (root == NULL) return;  
  
    // Create an empty queue for level order tarversal  
    queue<Node *> q;  
  
    // Enqueue Root and initialize height  
    q.push(root);  
  
    while (q.empty() == false)  
    {  
        // nodeCount (queue size) indicates number 
        // of nodes at current lelvel.  
        int nodeCount = q.size();  
  
        // Dequeue all nodes of current level and  
        // Enqueue all nodes of next level  
        while (nodeCount > 0) 
        {  
            Node *node = q.front();  
            cout << node->i << " ";  
            q.pop();  
            if (node->left != NULL)  
                q.push(node->left);  
            if (node->right != NULL)  
                q.push(node->right);  
            nodeCount--;  
        }  
        cout << endl;  
    }  
  
	
	
	
}
