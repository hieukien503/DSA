#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
using namespace std;

template<typename T>
class BST
{
public:
	class Node;
private:
    	Node* root;
public:
	BST()
	{
		this->root = nullptr;
	}
	~BST()
	{
	        this->cleanUp(&this->root);
	}
private:
	Node* addHelper(Node* root, T val)
	{
	        if (root == nullptr)
	        {
	            return new Node(val);
	        }
	        if (val < root->data)
	        {
	            root->left = this->addHelper(root->left, val);
	        }
	        else
	        {
	            root->right = this->addHelper(root->right, val);
	        }
	        return root;
	}

    	Node* findLeftMost(Node* param)
	{
		Node* temp = param->right;
	        while (temp->left != nullptr)
	        {
	            temp = temp->left;
	        }
	        return temp;
	}

    	Node* findRightMost(Node* param)
    	{
	        Node* temp = param->left;
	        while (temp->right != nullptr)
	        {
	            temp = temp->right;
	        }
	        return temp;
    	}

    	Node* deleteHelper(Node* root, T val, bool isLeft = false)
	{
	        if (root == nullptr)
	        {
	            return nullptr;
	        }
	        if (root->data > val)
	        {
	            root->left = this->deleteHelper(root->left, val, isLeft);
	        }
	        else if (root->data < val)
	        {
	            root->right = this->deleteHelper(root->right, val, isLeft);
	        }
	        else
	        {
	            if (root->left == nullptr)
	            {
	                Node* temp = root->right;
	                delete root;
	                return temp;
	            }
	            else if (root->right == nullptr)
	            {
	                Node* temp = root->left;
	                delete root;
	                return temp;
	            }
	            else
	            {
	                Node* replace = (isLeft? this->findLeftMost(root) : this->findRightMost(root));
	                root->data = replace->data;
	                if (isLeft)
	                {
	                    root->right = this->deleteHelper(root->right, replace->data);
	                }
	                else
	                {
	                    root->left = this->deleteHelper(root->left, replace->data);
	                }
	            }
	        }
	        return root;
	}

    	void printHelper(Node* root, string indent, bool last)
	{
		if (root != nullptr)
	        {
			cout << indent;
			if (last)
			{
				cout << "+----";
				indent += "     ";
			}
			else
			{
				cout << "|----";
				indent += "|    ";
			}
	
			cout << root->data << endl;
	
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}

    	void cleanUp(Node** root)
    	{
	        if (*root == nullptr)
	        {
	            return;
	        }
	        cleanUp(&(*root)->left);
	        cleanUp(&(*root)->right);
	        delete *root;
	        *root = nullptr;
    	}
public:
    	void addValue(T data)
	{
	        root = this->addHelper(root, data);
	}
	
	void deleteValue(T data, bool isLeft)
	{
	        root = this->deleteHelper(root, data, isLeft);
	}
	
	void printTreeStructure()
	{
		printHelper(root, "", true);
	}
public:
	class Node
	{
	    protected:
	        T data;
	        Node* left, *right;
	        friend class BST<T>;
	    public:
	        Node(T data = T(), Node* left = nullptr, Node* right = nullptr)
	        {
	            this->data = data;
	            this->left = left;
	            this->right = right;
	        }
	};
};

int randInRange(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

int main()
{
	srand((unsigned int)time(nullptr));
	BST<int>* bst = new BST<int>();
	int numValue = randInRange(10, 20);
	vector<int> v;
	for (int i = 0; i < numValue; i++)
	{
	v.push_back(randInRange(10, 100));
	}
	cout << "Random input:\n";
	for (int i = 0; i < numValue; i++)
	{
		bst->addValue(v[i]);
		cout << v[i] << (i == numValue - 1? '\n' : ' ');
	}
	bst->printTreeStructure();
	cout << "The value to delete is: ";
	int idx = randInRange(0, numValue - 1);
	cout << v[idx] << '\n';
	cout << "Choose which way to delete (L for Left most the right, R for right most the left): ";
	char opt;
	cin >> opt;
	bool isLeft = (opt == 'L'? true : false);
	bst->deleteValue(v[idx], isLeft);
	bst->printTreeStructure();
}
