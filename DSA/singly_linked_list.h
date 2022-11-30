#ifndef SLL_h
#define SLL_h
#include <iostream>
using namespace std;
#define Null -2147483648

template<class T>
class slist
{
public:
	class Node;
	class iterator;
protected:
	Node* head;
	Node* tail;
	int size;
public:
	slist()
	{
		head = tail = nullptr;
		size = 0;
	}
	~slist()
	{
		while (head != nullptr)
		{
			Node* temp = head;
			head = head->next;
			if (head == nullptr)
			{
				tail = nullptr;
			}
			delete temp;
		}
	}
protected:
	void delete_head()
	{
		if (head == nullptr)
		{
			cout << "List is empty, cannot preform deletion!";
			return;
		}
		Node* p = head;
		head = head->next;
		p->next = nullptr;
		p = nullptr;
		size--;
		delete p;
	}
	void delete_tail()
	{
		if (head == nullptr)
		{
			cout << "List is empty, cannot preform deletion!";
			return;
		}
		Node* p = head;
		Node* q = p->next;
		while (q->next != nullptr)
		{
			p = q;
			q = q->next;
		}
		p->next = nullptr;
		tail = p;
		q = nullptr;
		size--;
		delete q;
	}
public:
	void insert_head(T value);
	void insert_last(T value);
	void insert_at(T value, int index);
	int find(T value)
	{
		if (head == nullptr)
		{
			return -1;
		}
		int i = 0;
		for (Node* p = head; p != nullptr; p = p->next)
		{
			if (p->value == value)
			{
				return i;
			}
			i++;
		}
		return -1;
	}
	int find(T value, int index)
	{
		if (index == 0)
		{
			return find(value);
		}
		if (index >= size)
		{
			return -1;
		}
		if (index == size - 1)
		{
			return (tail->value == value ? index : -1);
		}
		Node* curr = head;
		Node* pre = nullptr;
		int i = 0;
		while (i < index)
		{
			pre = curr;
			curr = curr->next;
			i++;
		}
		for (; curr != nullptr; curr = curr->next)
		{
			if (curr->value == value)
			{
				return i;
			}
			i++;
		}
		return -1;
	}
	void delete_at_index(int index)
	{
		if (index == 0)
		{
			delete_head();
			return;
		}
		if (index == size - 1)
		{
			delete_tail();
			return;
		}
		if (index > size - 1)
		{
			cout << "Index is out of range\n";
			return;
		}
		Node* p = head;
		Node* q = p->next;
		int i = 1;
		while (i < index)
		{
			p = q;
			q = q->next;
			i++;
		}
		p->next = q->next;
		q->next = nullptr;
		q = nullptr;
		size--;
		delete q;
	}
	void delete_val(T value)
	{
		if (find(value) == -1)
		{
			cout << "Value not found";
			return;
		}
		while (find(value) != -1)
		{
			delete_at_index(find(value));
		}
	}
	int getSize()
	{
		return this->size;
	}
	void print_list()
	{
		if (head == nullptr)
		{
			cout << "List is empty";
		}
		else
		{
			cout << "HEAD -> ";
			for (Node* p = head; p != nullptr; p = p->next)
			{
				if (p->value == Null)
				{
					cout << "NULL";
				}
				else
				{
					cout << p->value;
				}
				cout << " -> ";
			}
			cout << "NULL" << endl;
		}
	}
	bool is_empty()
	{
		return this->size == 0;
	}
	void clear()
	{
		if (head == nullptr)
		{
			cout << "List is empty";
			return;
		}
		while (head != nullptr)
		{
			delete_head();
		}
	}
	iterator begin()
	{
		return iterator(head);
	}
	iterator end()
	{
		return iterator(tail->next);
	}
public:
	class iterator
	{
	private:
		Node* it;
	public:
		iterator()
		{
			it = nullptr;
		}
		iterator(Node* p)
		{
			it = p;
		}
		~iterator()
		{

		}
	public:
		iterator& operator= (Node* p)
		{
			this->it = p;
			return *this;
		}
		iterator& operator++()
		{
			if (it != nullptr)
			{
				it = it->next;
			}
			return *this;
		}
		iterator& operator++(int)
		{
			iterator p = *this;
			++* this;
			return p;
		}
		bool operator!= (const iterator& iter)
		{
			return it != iter.it;
		}
		T operator*()
		{
			return it->value;
		}
	};
public:
	class Node
	{
	private:
		T value;
		Node* next;
		friend class slist<T>;
	public:
		Node()
		{
			next = nullptr;
		}
		Node(T value)
		{
			this->value = value;
			this->next = nullptr;
		}
	};
};

template<class T>
void slist<T>::insert_head(T value)
{
	Node* temp = new Node(value);
	if (head == nullptr)
	{
		head = temp;
		tail = temp;
	}
	else
	{
		temp->next = head;
		head = temp;
	}
	size++;
}

template<class T>
void slist<T>::insert_last(T value)
{
	Node* temp = new Node(value);
	if (head == nullptr)
	{
		head = temp;
		tail = temp;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}
	size++;
}

template<class T>
void slist<T>::insert_at(T value, int index)
{
	if (index == 0)
	{
		insert_head(value);
		return;
	}
	if (index == size)
	{
		insert_last(value);
		return;
	}
	if (index > size)
	{
		cout << "Index is out of range\n";
		return;
	}
	else
	{
		Node* pre = nullptr;
		Node* curr = head;
		int i = 0;
		while (i < index)
		{
			pre = curr;
			curr = curr->next;
			i++;
		}
		if (curr->value == Null)
		{
			curr->value = value;
		}
		else
		{
			Node* temp = new Node(value);
			if (pre != nullptr)
			{
				pre->next = temp;
				temp->next = curr;
			}
			size++;
		}
	}
}
#endif
