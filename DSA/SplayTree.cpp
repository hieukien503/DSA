#include <iostream>
#include <cmath>
#include <random>
#include <time.h>
using namespace std;

template<typename T>
class SplayTree
{
public:
	class Node;
private:
	Node* root;
public:
	SplayTree()
	{
		root = nullptr;
	}
	~SplayTree()
	{
		
	}
private:
	void leftRotate(Node* x)
	{
		Node* y = x->right;
		x->right = y->left;
		if (y->left != nullptr)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr)
		{
			this->root = y;
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}
	void rightRotate(Node* x)
	{
		Node* y = x->left;
		x->left = y->right;
		if (y->right != nullptr)
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr)
		{
			this->root = y;
		}
		else if (x == x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}
	void splay(Node* x)
	{
		while (x->parent != nullptr)
		{
			if (x->parent->parent == nullptr)
			{
				if (x == x->parent->left)
				{
					rightRotate(x->parent);
				}
				else
				{
					leftRotate(x->parent);
				}
			}
			else if (x == x->parent->left && x->parent == x->parent->parent->left)
			{
				rightRotate(x->parent->parent);
				rightRotate(x->parent);
			}
			else if (x == x->parent->right && x->parent == x->parent->parent->right)
			{
				leftRotate(x->parent->parent);
				leftRotate(x->parent);
			}
			else if (x == x->parent->left && x->parent == x->parent->parent->right)
			{
				rightRotate(x->parent);
				leftRotate(x->parent);
			}
			else
			{
				leftRotate(x->parent);
				rightRotate(x->parent);
			}
		}
	}
	Node* searchHelper(Node* root, T key)
	{
		if (root == nullptr || root->key == key)
		{
			return root;
		}
		if (root->key > key)
		{
			return searchHelper(root->left, key);
		}
		return searchHelper(root->right, key);
	}
	void printHelper(Node* root, string indent, bool last) {
		if (root != nullptr) {
			cout << indent;
			if (last) {
				cout << "+----";
				indent += "     ";
			}
			else {
				cout << "|----";
				indent += "|    ";
			}

			cout << root->key << endl;

			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}
	Node* findMax(Node* x)
	{
		while (x->right != nullptr)
		{
			x = x->right;
		}
		return x;
	}
	void split(Node*& x, Node*& s, Node*& t)
	{
		splay(x);
		if (x->right != nullptr)
		{
			t = x->right;
			t->parent = nullptr;
		}
		else
		{
			t = nullptr;
		}
		s = x;
		s->right = nullptr;
		x = nullptr;
	}
	Node* join(Node* s, Node* t)
	{
		if (s == nullptr)
		{
			return t;
		}
		Node* x = findMax(s);
		splay(x);
		x->right = t;
		if (t != nullptr)
		{
			t->parent = x;
		}
		return x;
	}
	Node* deleteHelper(Node* root, T key)
	{
		Node* x = nullptr;
		Node* s, * t;
		Node* temp = root, * prev = nullptr;
		while (temp != nullptr)
		{
			if (temp->key == key)
			{
				x = temp;
				break;
			}
			if (temp->key < key) {
				prev = temp;
				temp = temp->right;
			}
			else {
				prev = temp;
				temp = temp->left;
			}
		}
		if (x == nullptr)
		{
			splay(prev);
			return nullptr;
		}
		split(x, s, t);
		if (s->left != nullptr)
		{
			s->left->parent = nullptr;
		}
		this->root = join(s->left, t);
		delete(s);
		s = nullptr;
		return this->root;
	}
public:
	void insert(T key)
	{
		Node* tmp = new Node(key);
		Node* x = this->root, * y = nullptr;
		while (x != nullptr)
		{
			y = x;
			if (x->key > tmp->key)
			{
				x = x->left;
			}
			else
			{
				x = x->right;
			}
		}
		tmp->parent = y;
		if (y == nullptr)
		{
			this->root = tmp;
		}
		else if (tmp->key < y->key)
		{
			y->left = tmp;
		}
		else
		{
			y->right = tmp;
		}
		splay(tmp);
	}
	void printTreeStructure()
	{
		printHelper(root, "", true);
	}
	bool search(T key)
	{
		Node* tmp = searchHelper(root, key);
		if (tmp != nullptr)
		{
			splay(tmp);
			return true;
		}
		return false;
	}
	Node* remove(T key)
	{
		return deleteHelper(this->root, key);
	}
public:
	class Node
	{
	private:
		T key;
		Node* left, * right, * parent;
		friend class SplayTree<T>;
	public:
		Node(T data = T{})
		{
			this->key = data;
			this->left = this->right = this->parent = nullptr;
		}
		~Node()
		{

		}
	};
};

int main()
{
	SplayTree<int> tree;
	int query;
	cin >> query;
	for (int i = 0; i < query; i++) {
		string op;
		int val;
		cin >> op >> val;
		if (op == "insert")
			tree.insert(val);
		else if (op == "remove")
			cout << (tree.remove(val) != nullptr ? "removed" : "not found") << '\n';
		else if (op == "search")
			cout << (tree.search(val) ? "found" : "not found") << '\n';
		else if (op == "print")
			tree.printTreeStructure();
	}
}
