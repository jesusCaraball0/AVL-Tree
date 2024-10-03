#include<iostream>
#include<vector>
#include"avltree.h"
#include"validation.h"

using namespace std;

//Constructor
AvlTree::AvlTree() {
	root = nullptr;
}

//Destructor, calls recursive function to deallocate all nodes
AvlTree::~AvlTree() {
	recDelete(root);
}

// Deallocates all nodes
Node* AvlTree::recDelete(Node* root) {
	if (root == nullptr) {
		return nullptr;
	}
	recDelete(root->getLeft());
	recDelete(root->getRight());
	delete root;
	root = nullptr;
}

// returns height given a node
int AvlTree::getHeight(Node* node) {
	if (node == nullptr) {
		return 0;
	}
	else {
		return node->getHeight();
	}
}

// swaps root with left node and properly relocates children
Node* AvlTree::rightRotate(Node* subtreePrevRoot) {
	Node* subtreeNewRoot = subtreePrevRoot->getLeft();
	Node* prevDescendants = subtreeNewRoot->getRight();

	//perform rotation
	subtreeNewRoot->setRight(subtreePrevRoot);
	subtreePrevRoot->setLeft(prevDescendants);

	// recalculate heights of each
	subtreePrevRoot->setHeight(1 + max(getHeight(subtreePrevRoot->getLeft()), getHeight(subtreePrevRoot->getRight())));
	subtreeNewRoot->setHeight(1 + max(getHeight(subtreeNewRoot->getLeft()), getHeight(subtreeNewRoot->getRight())));


	return subtreeNewRoot;
}

// swaps root with right node and properly relocates children
Node* AvlTree::leftRotate(Node* subtreePrevRoot) {
	Node* subtreeNewRoot = subtreePrevRoot->getRight();
	Node* prevDescendants = subtreeNewRoot->getLeft();

	//perform rotation
	subtreeNewRoot->setLeft(subtreePrevRoot);
	subtreePrevRoot->setRight(prevDescendants);

	// recalculate heights of each
	subtreePrevRoot->setHeight(1 + max(getHeight(subtreePrevRoot->getLeft()), getHeight(subtreePrevRoot->getRight())));
	subtreeNewRoot->setHeight(1 + max(getHeight(subtreeNewRoot->getLeft()), getHeight(subtreeNewRoot->getRight())));

	return subtreeNewRoot;
}

// recursively iterates through path where new node should go
// on the way down it finds the path and inserts node in the right place
// on the way back up it recalculates balance factors and rebalances if needed
Node* AvlTree::recInsert(Node* root, int& id, string& name) {
	if (root == nullptr) {
		root = new Node(name, id);
		root->setHeight(1);
		return root;
	}
	else if (root->getId() > id) {
		root->setLeft(recInsert(root->getLeft(), id, name));
	}
	else {
		root->setRight(recInsert(root->getRight(), id, name));
	}

	root->setHeight(1 + max(getHeight(root->getLeft()), getHeight(root->getRight())));

	int balanceFactor = getHeight(root->getLeft()) - getHeight(root->getRight());

	// rebalancing
	// left left case
	if (balanceFactor > 1 && root->getLeft()->getId() > id) {
		return rightRotate(root);
	}
	// left right case
	else if (balanceFactor > 1 && root->getLeft()->getId() < id) {
		root->setLeft(leftRotate(root->getLeft()));
		return rightRotate(root);
	}
	// right left case
	else if (balanceFactor < -1 && root->getRight()->getId() > id) {
		root->setRight(rightRotate(root->getRight()));
		return leftRotate(root);
	}
	// right right case
	else if (balanceFactor < -1 && root->getRight()->getId() < id) {
		return leftRotate(root);
	}
	// no rebalancing needed case
	return root;
}

// returns a node given its id
Node* AvlTree::findId(Node* root, int& id) {
	if (root == nullptr) {
		return nullptr;
	}
	else if (root->getId() == id) {
		return root;
	}
	else if (root->getId() < id) {
		findId(root->getRight(), id);
	}
	else {
		findId(root->getLeft(), id);
	}
}

// AVL Tree insertion given name and id
void AvlTree::insert(string name, int id) {
	try {
		// validate id and name according to constraints
		Validation v;
		if (!v.validateId(id) || !v.validateName(name) || findId(root, id) != nullptr) {
			string error = "unsuccessful";
			throw(error);
		}
		// bst insert in tree, rebalance if needed
		root = recInsert(root, id, name);
		cout << "successful" << endl;
	}
	catch (string error){
		cout << error << endl;
	}
}

// returns leftmost node in a given subtree
Node* AvlTree::minRightSubtree(Node* root) {
	if (root == nullptr) {
		return nullptr;
	}
	else if (root->getLeft() == nullptr) {
		return root;
	}
	else {
		minRightSubtree(root->getLeft());
	}
}

// recursively iterates through tree to find node that should be deleted
// on the way down it finds the node to be deleted, deletes it, and relocates children
// on the way back up it recalculates heights for path affected
Node* AvlTree::recRemove(Node* root, int id) {
	// return nullptr if tree is empty
	if (root == nullptr) {
		return root;
	}

	if (root->getId() < id) {
		root->setRight(recRemove(root->getRight(), id));
	}
	else if (root->getId() > id) {
		root->setLeft(recRemove(root->getLeft(), id));
	}
	// if root is the node to be deleted, delete the node and replace with inorder successor
	else {
		// no children case
		if (root->getRight() == nullptr && root->getLeft() == nullptr) {
			delete root;
			root = nullptr;
		}
		// one child case
		else if (root->getRight() == nullptr || root->getLeft() == nullptr) {
			Node* successor = nullptr;
			if (root->getRight() != nullptr) {
				successor = root->getRight();
			}
			else {
				successor = root->getLeft();
			}
			*root = *successor;
			delete successor;
			successor = nullptr;
		}
		// two children case
		else {
			Node* successor = minRightSubtree(root->getRight());
			root->setId(successor->getId());
			root->setName(successor->getName());
			root->setRight(recRemove(root->getRight(), successor->getId()));
		}

	}

	if (root == nullptr) {
		return root;
	}


	// update height for nodes in the path affected (path between root and node to be deleted)
	root->setHeight(1 + max(getHeight(root->getLeft()), getHeight(root->getRight())));

	return root;
}

// AVL Tree removal given id
void AvlTree::remove(int id) {
	try {
		Validation v;
		if (!v.validateId(id)) {
			string error = "unsuccessful";
			throw(error);
		}
		root = recRemove(root, id);
		cout << "successful" << endl;
	}
	catch (string error) {
		cout << error << endl;
	}
}

// BST searches tree for given ID, prints the name
void AvlTree::searchId(int id) {
	try {
		Validation v;
		if (!v.validateId(id)) {
			string error = "unsuccessful";
			throw(error);
		}
		Node* res = findId(root, id);
		if (res == nullptr) {
			string error = "unsuccessful";
			throw(error);
		}
		else {
			cout << res->getName() << endl;
		}
	}
	catch(string error){
		cout << error << endl;
	}
}

// Brute Force searches for a certain name in the tree, updates a vector of all IDs with that name
void AvlTree::recSearchName(string name, vector<int>& nameIds, Node* root) {
	if (root == nullptr) {
		return;
	}
	if (root->getName() == name) {
		nameIds.push_back(root->getId());
	}

	recSearchName(name, nameIds, root->getLeft());
	recSearchName(name, nameIds, root->getRight());
}

// Prints list of IDs matching a given name
void AvlTree::searchName(string name) {
	try {
		// validate name input
		Validation v;
		if (!v.validateName(name)) {
			string error = "unsuccessful";
			throw(error);
		}

		// getting list of ids with given name
		vector<int> nameIds;
		recSearchName(name, nameIds, root);

		// if no names found, print unsuccessful
		if (nameIds.size() == 0) {
			string error = "unsuccessful";
			throw(error);
		}
		// printing ids of people with given name
		for (int i = 0; i < nameIds.size(); i++) {
			cout << nameIds[i] << endl;
		}
	}
	catch(string error) {
		cout << error << endl;
	}
}

// Adds the names to a vector in inorder
void AvlTree::getInorder(vector<string>& inorder, Node* root) {
	if (root == nullptr) {
		return;
	}
	getInorder(inorder, root->getLeft());
	inorder.push_back(root->getName());
	getInorder(inorder, root->getRight());
}

// Prints the names in the tree inorder
void AvlTree::printInorder() {
	// make vector of elements in inorder
	vector<string> inorder;
	getInorder(inorder, root);

	// print names
	for (int i = 0; i < inorder.size(); i++) {
		if (i == inorder.size() - 1) {
			cout << inorder.at(i) << endl;
		}
		else {
			cout << inorder.at(i) << ", ";
		}
	}
}

// Adds the names to a vector in preorder
void AvlTree::getPreorder(vector<string>& preorder, Node* root) {
	if (root == nullptr) {
		return;
	}

	preorder.push_back(root->getName());
	getPreorder(preorder, root->getLeft());
	getPreorder(preorder, root->getRight());
}

// Prints the names in the tree preorder
void AvlTree::printPreorder() {
	// make vector of names in preorder
	vector<string> preorder;
	getPreorder(preorder, root);

	// print names
	for (int i = 0; i < preorder.size(); i++) {
		if (i == preorder.size() - 1) {
			cout << preorder.at(i) << endl;
			break;
		}
		cout << preorder.at(i) << ", ";
	}
}

// Adds the names to a vector in postorder
void AvlTree::getPostorder(vector<string>& postorder, Node* root) {
	if (root == nullptr) {
		return;
	}
	getPostorder(postorder, root->getLeft());
	getPostorder(postorder, root->getRight());
	postorder.push_back(root->getName());
}

// Prints the names in the tree in postorder
void AvlTree::printPostorder() {
	// make vector of names in postorder
	vector<string> postorder;
	getPostorder(postorder, root);

	for (int i = 0; i < postorder.size(); i++) {
		if (i == postorder.size() - 1) {
			cout << postorder.at(i) << endl;
			break;
		}
		cout << postorder.at(i) << ", ";
	}
}

// Prints the number of levels in the tree
void AvlTree::printLevelCount() {
	if (root == nullptr) {
		cout << 0 << endl;
	}
	else {
		cout << root->getHeight() << endl;
	}
}

// Given a number N, it returns the ID matching the N's inorder node
void  AvlTree::recFindInorder(Node* root, int& removeId, int& n, int& m) {
	if (root == nullptr) {
		return;
	}
	recFindInorder(root->getLeft(), removeId, n, m);
	if (n == m) {
		removeId = root->getId();
	}
	m += 1;
	recFindInorder(root->getRight(), removeId, n, m);
}

// Given a number N, it deletes the N's inorder node
void AvlTree::removeInorder(int n) {
	try {
		int inorderNId = 0;
		int m = 0;
		recFindInorder(root, inorderNId, n, m);
		if (inorderNId == 0) {
			string error = "unsuccessful";
			throw(error);
		}
		else {
			remove(inorderNId);
		}
	}
	catch(string error){
		cout << error << endl;
	}
}