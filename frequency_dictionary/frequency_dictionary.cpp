#include "pch.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <string>
#include <Windows.h>

using namespace std;

class map_pair {
public:
	char first[17];
	int second;

	map_pair() {

	}

	map_pair(char* key, int value) {
		strcpy(this->first, key);
		this->second = value;
	}

	bool operator > (map_pair& p) {
		return strcmp(this->first, p.first) > 0;
	}

	bool operator < (map_pair& p) {
		return strcmp(this->first, p.first) < 0;
	}

	bool operator == (map_pair& p) {
		return strcmp(this->first, p.first) == 0;
	}

	friend ostream& operator <<(ostream& o, map_pair& p) {

		o << "{" << p.first << ", " << p.second << "} " << endl;

		return o;
	}

};
class map {
public:
	class node {
	public:
		node* right;
		node* left;
		map_pair key;

		node() {
			right = nullptr;
			left = nullptr;
		}

		node(map_pair& key) {
			this->key = key;
			right = nullptr;
			left = nullptr;
		}

	};

	node* root;

	map() {
		root = nullptr;
	}

	void push(node* parent, map_pair& key) {

		if (key > parent->key) {
			if (parent->right == nullptr) {
				parent->right = new node(key);
			}
			else {
				push(parent->right, key);
			}
		}
		else if (key < parent->key) {
			if (parent->left == nullptr) {
				parent->left = new node(key);
			}
			else {
				push(parent->left, key);
			}
		}
		else if (key == parent->key) {
			parent->key.second++;
		}
	}

	void push(map_pair& key) {
		if (root == nullptr)
			root = new node(key);
		else
			push(root, key);
	}

	void print(node* parent) {

		if (parent->left != nullptr)
			print(parent->left);

		cout << parent->key;

		if (parent->right != nullptr)
			print(parent->right);

	}

	void print() {
		print(root);
	}

	int size(node* parent, int t) {

		if (parent->left != nullptr)
			t = size(parent->left, t);

		if (parent->right != nullptr)
			t = size(parent->right, t);

		return ++t;
	}

	int size() {

		int n = 0;
		if (root != nullptr) {
			n = size(root, n);
		}

		return n;
	}
};

void load() {

	map m1;
	string str;
	char buffer[17];

	ifstream fin("input.txt");

	while (!fin.eof()) {

		memset(buffer, 0, 17);

		fin.read(buffer, 16);

		str.append(buffer);

	}

	fin.close();

	char* c_str = (char*)str.c_str();

	char* t_str = strtok(c_str, " ;.,!\t\n()[]+?{}+=*&^$#@:\";'%");

	while (t_str != nullptr) {

		map_pair b = map_pair(t_str, 1);
		m1.push(b);
		t_str = strtok(nullptr, " ;.,!\t\n()[]+?{}+=*&^$#@:\";'%");

	}

	fin.close();

	m1.print();

}

int main() {


	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	load();

	return 0;
}