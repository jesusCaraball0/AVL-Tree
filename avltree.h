#pragma once
#include<iostream>
#include<vector>
#include"node.h"

using namespace std;

class AvlTree {
	Node* root = nullptr;

public:

	// Constructor and Destructor
	AvlTree();
	~AvlTree();
	Node* recDelete(Node* root);

	// Helper Functions
	
	// Insertion helper functions
	int getHeight(Node* node);
	Node* recInsert(Node* root, int& id, string& name);
	Node* findId(Node* root, int& id);
	Node* rightRotate(Node* subtreePrevRoot);
	Node* leftRotate(Node* subtreePrevRoot);

	// Removal helper functions
	Node* minRightSubtree(Node* root);
	Node* recRemove(Node* root, int id);

	// Searching helper functions
	void recSearchName(string name, vector<int>& nameIds, Node* root);

	// Printing inorder, preorder, postorder helper functions
	void getInorder(vector<string>& inorder, Node* root);
	void getPreorder(vector<string>& preorder, Node* root);
	void getPostorder(vector<string>& postorder, Node* root);

	// Removing inorder N helper function
	void recFindInorder(Node* root, int& removeId, int& n, int& m);


	// AVL Tree Functions
	
	// AVL Tree Insertion
	void insert(string name, int id);

	// AVL Tree Removal
	void remove(int id);

	// AVL Tree Searching
	void searchId(int id);
	void searchName(string name);

	// AVL Tree print inorder, preorder, postorder
	void printInorder();
	void printPreorder();
	void printPostorder();

	// AVL Tree printing number of levels, removing inorder N
	void printLevelCount();
	void removeInorder(int n);
};