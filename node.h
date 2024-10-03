#pragma once
#include<iostream>

using namespace std;

class Node {
	Node* right = nullptr;
	Node* left = nullptr;
	string name;
	int id;
	int height;

public:
	// Constructor and copy assignment operator
	Node(string _name, int _id);
	void operator=(const Node& node);

	// Setters
	void setRight(Node* temp);
	void setLeft(Node* temp);
	void setHeight(int temp);
	void setName(string temp);
	void setId(int temp);

	// Getters
	Node* getRight();
	Node* getLeft();
	string getName();
	int getId();
	int getHeight();

};