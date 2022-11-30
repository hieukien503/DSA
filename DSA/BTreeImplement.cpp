#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <utility>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
using namespace std;

class BTree
{
public:
	class Node;
	class Entry;
protected:
	Node* root;
	int order;
public:
	BTree(int m = 3)
	{
		this->root = nullptr;
		this->order = m;
	}
	~BTree()
	{
		cleanUp(&this->root);
	}
public:
	void splitNode(Node* prev, Node* temp)
	{
		Entry median = temp->entries[temp->entries.size() / 2];
		temp->entries.erase(temp->entries.begin() + (temp->entries.size() / 2), temp->entries.begin() + (temp->entries.size() / 2 + 1));
		Node* temp1 = new Node;
		temp1->entries = vector<Entry>(temp->entries.begin() + order / 2, temp->entries.end());
		temp->entries = vector<Entry>(temp->entries.begin(), temp->entries.begin() + order / 2);
		if (prev == nullptr)
		{
			this->root = new Node;
			this->root->entries.push_back(median);
			this->root->firstPtr = temp;
			temp1->firstPtr = this->root->entries[0].rightPtr;
			this->root->entries[0].rightPtr = temp1;
		}
		else
		{
			int i = (int)prev->entries.size() - 1;
			while (i >= 0 && prev->entries[i].key >= median.key)
			{
				i--;
			}
			median.rightPtr = temp1;
			prev->entries.insert(prev->entries.begin() + (i + 1), median);
		}
	}
	void addKey(int data, int key)
	{
		Node* temp = this->root, * prev = nullptr;
		stack<pair<Node*, Node*>> st;
		st.push(make_pair(prev, temp));
		while (temp != nullptr)
		{
			if (temp->firstPtr == nullptr)
			{
				int i = (int)temp->entries.size() - 1;
				while (i >= 0 && temp->entries[i].key >= data)
				{
					i--;
				}
				temp->entries.insert(temp->entries.begin() + (i + 1), Entry(data, key));
				st.push(make_pair(prev, temp));
				break;
			}
			if (data < temp->entries[0].key)
			{
				prev = temp;
				temp = temp->firstPtr;
				st.push(make_pair(prev, temp));
			}
			else
			{
				for (int i = (int)temp->entries.size() - 1; i >= 0; i--)
				{
					if (data >= temp->entries[i].key)
					{
						prev = temp;
						temp = temp->entries[i].rightPtr;
						st.push(make_pair(prev, temp));
						break;
					}
				}
			}
		}
		if (prev == nullptr)
		{
			if (temp == nullptr)
			{
				this->root = new Node;
				this->root->entries.push_back(Entry(data, key));
			}
			else
			{
				if ((int)this->root->entries.size() == order)
				{
					splitNode(prev, temp);
				}
			}
		}
		else
		{
			while (!st.empty())
			{
				pair<Node*, Node*> p = st.top();
				st.pop();
				if ((int)p.second->entries.size() == order)
				{
					splitNode(p.first, p.second);
				}
			}
		}
	}
	string toStringPreOrderHelper(Node* root, string ans = "")
	{
		if (root == nullptr)
		{
			return "";
		}
		ans = root->toString() + " ";
		ans += toStringPreOrderHelper(root->firstPtr, ans);
		for (int i = 0; i < (int)root->entries.size(); i++)
		{
			ans += toStringPreOrderHelper(root->entries[i].rightPtr, ans);
		}
		return ans;
	}
	string toStringPreOrder() {
		string ans = "";
		ans = toStringPreOrderHelper(this->root, ans);
		return ans;
	}
	void cleanUp(Node** root)
	{
		if (*root != nullptr)
		{
			cleanUp(&(*root)->firstPtr);
			for (int i = 0; i < (int)(*root)->entries.size(); i++)
			{
				cleanUp(&(*root)->entries[i].rightPtr);
			}
			delete (*root);
			(*root) = nullptr;
		}
	}
public:
	class Entry
	{
	private:
		int key, data;
		Node* rightPtr;
		friend class BTree;
	public:
		Entry(int key = 0, int data = 0)
		{
			this->key = key;
			this->data = data;
			this->rightPtr = nullptr;
		}
		string toString() {
			stringstream ss;
			ss << "<" << this->key << "," << this->data << ">";
			return ss.str();
		}
	};
public:
	class Node
	{
	private:
		vector<Entry> entries;
		Node* firstPtr;
		friend class BTree;
	public:
		Node()
		{
			this->firstPtr = nullptr;
		}
		string toString() {
			stringstream ss;
			ss << "[(" << (int)entries.size() << ")";
			for (int i = 0; i < (int)entries.size(); i++) {
				ss << entries[i].toString();
			}
			ss << "]";

			return ss.str();
		}
	};
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	int keys[] = { 78, 21, 14, 11, 97, 85, 74, 63, 45, 42, 57 };
	int size = sizeof(keys) / sizeof(int);
	BTree* bTree = new BTree(3);
	for (int idx = 0; idx < size; idx++) {
		bTree->addKey(keys[idx], idx);
	}
	cout << bTree->toStringPreOrder();
	delete bTree;
}