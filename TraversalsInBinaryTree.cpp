#include<bits/stdc++.h>
using namespace std;

template<typename T>
class BinaryTreeNode {
	public:
		T data;
		BinaryTreeNode *left;
		BinaryTreeNode *right;
		BinaryTreeNode(T data) {
			this->data = data;
			this->left = NULL;
			this->right = NULL;
		}
};
BinaryTreeNode<int> *takeInput() {
	int rootData;
	cout<<"Enter the root data: ";
	cin>>rootData;
	if(rootData == -1) {
		return NULL;
	}
	BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootData);
	queue<BinaryTreeNode<int> *> pendingNodes;
	pendingNodes.push(root);
	while(pendingNodes.size() != 0) {
		BinaryTreeNode<int> *front = pendingNodes.front();
		pendingNodes.pop();
		int leftChildData;
		cout<<"Enter the left child of "<<front->data<<": ";
		cin>>leftChildData;
		if(leftChildData != -1) {
			BinaryTreeNode<int> *child = new BinaryTreeNode<int>(leftChildData);
			front->left = child;
			pendingNodes.push(child);
		}
		int rightChildData;
		cout<<"Enter the right child of "<<front->data<<": ";
		cin>>rightChildData;
		if(rightChildData != -1) {
			BinaryTreeNode<int> *child = new BinaryTreeNode<int>(rightChildData);
			front->right = child;
			pendingNodes.push(child);
		}
	}
	return root;
}

void print(BinaryTreeNode<int> *root) {
	queue<BinaryTreeNode<int> *> ans;
	if(root == NULL) {
		return ;
	}
	ans.push(root);
	while(ans.size() != 0) {
		BinaryTreeNode<int> *front = ans.front();
		ans.pop();
		if(front != NULL) {
			cout<<front->data<<":";
		}
		if(front->left != NULL) {
			cout<<"L: "<<front->left->data<<", ";
			ans.push(front->left);
		} else if(front->left == NULL) {
			cout<<"L: -1, ";
		}
		if(front->right != NULL) {
			cout<<"R: "<<front->right->data;
			ans.push(front->right);
		} else if(front->right == NULL) {
			cout<<"R: -1";
		}
		cout<<endl;
	}
}

void printLevel(BinaryTreeNode<int> *root) {
	if(root == NULL) {
		return ;
	}
	queue<BinaryTreeNode<int> *> ans;
	ans.push(root);
	ans.push(NULL);
	while(ans.size() != 0) {
		BinaryTreeNode<int> *front = ans.front();
		ans.pop();
		if(front == NULL) {
			if(ans.empty()) {
				break;
			}
			cout<<endl;
			ans.push(NULL);
			continue;
		}
		cout<<front->data<<" ";
		if(front->left != NULL) {
			ans.push(front->left);
		}
		if(front->right != NULL) {
			ans.push(front->right);
		}
	}
}

void zigZag(BinaryTreeNode<int> *root) {
	stack<BinaryTreeNode<int> *>s1;
	stack<BinaryTreeNode<int> *>s2;
	if(root == NULL) {
		return ;
	}
	s1.push(root);
	while(s1.size() != 0 || s2.size() != 0) {
		while(s1.size() != 0) {
			BinaryTreeNode<int> *front = s1.top();
			s1.pop();
			cout<<front->data<<" ";
			if(front->left != NULL) {
				s2.push(front->left);
			}
			if(front->right != NULL) {
				s2.push(front->right);
			}
			if(s1.size() == 0) {
				cout<<endl;
			}
		}
		while(s2.size() != 0) {
			BinaryTreeNode<int> *front = s2.top();
			s2.pop();
			cout<<front->data<<" ";
			if(front->right != NULL) {
				s1.push(front->right);
			}
			if(front->left != NULL) {
				s1.push(front->left);
			}
			if(s2.size() == 0) {
				cout<<endl;
			}
		}
	}
}

void printDiagUtil(BinaryTreeNode<int> *root, int diagLevel, map<int, vector<int>> &M) {
	if(root == NULL) {
		return ;
	}
	M[diagLevel].push_back(root->data);
	printDiagUtil(root->left, diagLevel + 1, M);
	printDiagUtil(root->right, diagLevel, M);
}

void printDiagonal(BinaryTreeNode<int> *root) {
	map<int, vector<int>>M;
	if(root == NULL) {
		return ;
	}
	printDiagUtil(root, 0, M);
	map<int, vector<int>> :: iterator it;
	for(it=M.begin();it!=M.end();it++) {
		vector<int> ::  iterator vit;
		for(vit = it->second.begin(); vit!=it->second.end();vit++) {
			cout<<*vit<<" ";
		}
		cout<<endl;
	}
}

void printBoundaryLeft(BinaryTreeNode<int> *root) {
	if(root != NULL) {
		if(root->left != NULL) {
			cout<<root->data<<" ";
			printBoundaryLeft(root->left);
		} else if(root->right != NULL) {
			cout<<root->data<<" ";
			printBoundaryLeft(root->right);
		}
	}
}

void printBoundaryRight(BinaryTreeNode<int> *root) {
	if(root != NULL) {
		if(root->right != NULL) {
			printBoundaryRight(root->right);
			cout<<root->data<<" ";
		} else if(root->left != NULL) {
			printBoundaryRight(root->left);	
			cout<<root->data<<" ";		
		}
	}
}

void printLeaves(BinaryTreeNode<int> *root) {
	if(root != NULL) {
		printLeaves(root->left);
		if(root->left == NULL && root->right == NULL) {
			cout<<root->data<<" ";
		}
		printLeaves(root->right);
	}
}

void printBoundary(BinaryTreeNode<int> *root) {
	if(root != NULL ) {
		cout<<root->data<<" ";
		printBoundaryLeft(root->left);
		printLeaves(root->left);
		printLeaves(root->right);
		printBoundaryRight(root->right);
	}
}

void boundary(BinaryTreeNode<int> *root) {
	printBoundary(root);
	cout<<endl;
}

int main() {
	BinaryTreeNode<int> *root = takeInput();
	cout<<"Normal traversal:"<<endl;
	print(root);
	cout<<endl;
	cout<<"Level order traversal:"<<endl;
	printLevel(root);
	cout<<endl;
	cout<<"Zig Zag order traversal:"<<endl;
	zigZag(root);
	cout<<endl;
	cout<<"Diagonal order traversal:"<<endl;
	printDiagonal(root);
	cout<<endl;
	cout<<"Boundary order Traversal:"<<endl;
	boundary(root);
	return 0;
}
