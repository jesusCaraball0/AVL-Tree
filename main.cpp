#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cctype>
#include"avltree.h"
#include"node.h"
#include"validation.h"

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

// Main function. Gets input and interacts with AVL Tree API accordingly
int main(){
	string stringNumberCommands;
	getline(cin, stringNumberCommands);
	int numberCommands = stoi(stringNumberCommands);
	string c;
	AvlTree Tree;

	while (numberCommands != 0) {
		vector<string> command;
		string s;
		getline(cin, s);
		stringstream line(s);
		while (getline(line, c, ' ')) {
			command.push_back(c);
		}


		if (command.at(0) == "insert" && command.at(1).at(0) == '"' 
			&& command.at(1).at(command.at(1).length() - 1) == '"') {
			string name = command.at(1).substr(1, (command.at(1).size() - 2)); 
			int id = stoi(command.at(2));

			Tree.insert(name, id);
		}
		else if (command.at(0) == "remove") {
			int id = stoi(command.at(1));

			Tree.remove(id);
		}
		else if (command.at(0) == "search") {
			if (isdigit(command.at(1).at(0))) {
				int id = stoi(command.at(1));

				Tree.searchId(id);
			}
			else if (command.at(1).at(0) == '"' && command.at(1).at(command.at(1).length() - 1) == '"'){
				string name = command.at(1).substr(1, (command.at(1).size() - 2));

				Tree.searchName(name);
			}
			else {
				cout << "unsuccessful" << endl;
			}
		}
		else if (command.at(0) == "printInorder") {
			Tree.printInorder();
		}
		else if (command.at(0) == "printPreorder") {
			Tree.printPreorder();

		}
		else if (command.at(0) == "printPostorder") {
			Tree.printPostorder();
		}
		else if (command.at(0) == "printLevelCount") {
			Tree.printLevelCount();
		}
		else if (command.at(0) == "removeInorder") {
			int n = stoi(command.at(1));

			Tree.removeInorder(n);
		}
		else {
			cout << "unsuccessful" << endl;
		}
		numberCommands--;
	}

	return 0;
}