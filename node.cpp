#include<iostream>
#include"node.h"

using namespace std;

// Constructor and copy assignment operator
Node::Node(string _name, int _id) {
	name = _name;
	id = _id;
	height = 0;
}
void Node::operator=(const Node& node) {
	right = node.right;
	left = node.left;
	name = node.name;
	id = node.id;
	height = node.height;
}

// Setters
void Node::setRight(Node* temp) {
	right = temp;
}
void Node::setLeft(Node* temp) {
	left = temp;
}
void Node::setHeight(int temp) {
	height = temp;
}
void Node::setName(string temp) {
	name = temp;
}
void Node::setId(int temp) {
	id = temp;
}

// Getters
Node* Node::getRight() {
	return right;
}
Node* Node::getLeft() {
	return left;
}
string Node::getName() {
	return name;
}
int Node::getId() {
	return id;
}
int Node::getHeight() {
	return height;
}