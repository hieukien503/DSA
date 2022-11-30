#include <iostream>
#include <string>
using namespace std;

class AVL
{
public:
    class Node;
protected:
    Node* root;
    int numNodes;
public:
    AVL()
    {
        root = nullptr;
        numNodes = 0;
    }
    ~AVL()
    {
        while (root != nullptr)
        {
            deleteAVLTree(root->id);
        }
    }
protected:
    int height(Node* root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        int leftHeight = 1 + height(root->left), rightHeight = 1 + height(root->right);
        return max(leftHeight, rightHeight);
    }
    int getBalanceFactor(Node* x)
    {
        if (x == nullptr)
        {
            return 0;
        }
        return height(x->left) - height(x->right);
    }
    Node* rightRotate(Node* x)
    {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        y->bal_factor = getBalanceFactor(y);
        x->bal_factor = getBalanceFactor(x);
        return y;
    }
    Node* leftRotate(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        y->bal_factor = getBalanceFactor(y);
        x->bal_factor = getBalanceFactor(x);
        return y;
    }
    Node* LeftRightRotate(Node* x)
    {
        x->left = leftRotate(x->left);
        return rightRotate(x);
    }
    Node* RightLeftRotate(Node* x)
    {
        x->right = rightRotate(x->right);
        return leftRotate(x);
    }
    Node* balanced(Node* root)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        root->bal_factor = getBalanceFactor(root);
        if (root->bal_factor > 1)
        {
            if (getBalanceFactor(root->left) > 0)
            {
                root = rightRotate(root);
            }
            else
            {
                root = LeftRightRotate(root);
            }
        }
        else if (root->bal_factor < -1)
        {
            if (getBalanceFactor(root->right) > 0)
            {
                root = RightLeftRotate(root);
            }
            else
            {
                root = leftRotate(root);
            }
        }
        return root;
    }
    Node* addAVL(Node* root, int key)
    {
        if (root == nullptr)
        {
            root = new Node(key);
            numNodes++;
        }
        else
        {
            if (key < root->id)
            {
                root->left = addAVL(root->left, key);
            }
            else
            {
                root->right = addAVL(root->right, key);
            }
            root = balanced(root);
        }
        return root;
    }
    Node* findMaxValue(Node* x)
    {
        Node* temp = x;
        while (temp->right != nullptr)
        {
            temp = temp->right;
        }
        return temp;
    }
    Node* deleteAVL(Node* root, int key)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (key < root->id)
        {
            root->left = deleteAVL(root->left, key);
        }
        else if (key > root->id)
        {
            root->right = deleteAVL(root->right, key);
        }
        else
        {
            if (root->left == nullptr || root->right == nullptr)
            {
                Node* temp = (root->left == nullptr ? root->right : root->left);
                if (temp == nullptr)
                {
                    temp = root;
                    delete temp;
                    root = nullptr;
                }
                else
                {
                    *root = *temp;
                    delete temp;
                    temp = nullptr;
                }
                numNodes--;
            }
            else
            {
                Node* temp = findMaxValue(root->left);
                root->id = temp->id;
                root->left = deleteAVL(root->left, temp->id);
            }
        }
        return balanced(root);
    }
    string toStringPreOrder(Node* root, string ans = "") const
    {
        if (root == nullptr)
        {
            return "";
        }
        ans = ("(id=" + to_string(root->id) + ");");
        ans += toStringPreOrder(root->left, ans);
        ans += toStringPreOrder(root->right, ans);
        return ans;
    }
public:
    void addAVLTree(int key)
    {
        root = addAVL(root, key);
    }
    void deleteAVLTree(int key)
    {
        root = deleteAVL(root, key);
    }
    int size() const
    {
        return this->numNodes;
    }
    string toStringPreOrder() const
    {
        string ans = "AVL[";
        ans += toStringPreOrder(root, ans);
        ans[ans.length() - 1] = ']';
        return ans;
    }
public:
    class Node
    {
    private:
        int id;
        Node* left, * right;
        int bal_factor;
        friend class AVL;
    public:
        Node(int id = 1, Node* left = nullptr, Node* right = nullptr, int bal_fac = 0)
        {
            this->id = id;
            this->left = left;
            this->right = right;
            this->bal_factor = bal_fac;
        }
    };
};

int main()
{
    AVL avl;
    for (int i = 0; i < 1; i++)
    {
        avl.addAVLTree(i);
    }
    cout << avl.toStringPreOrder() << '\n';
    avl.deleteAVLTree(0);
    cout << avl.size();
}
