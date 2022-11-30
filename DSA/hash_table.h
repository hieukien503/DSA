#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
using namespace std;

template<class T>
class Hash_Table;

template<class T>
class Element
{
public:
	T data;
	int key;
public:
	Element(T data = T(), int key = 0)
	{
		this->data = data;
		this->key = key;
	}
	friend bool operator== (const Element<T>& e, const Element<T>& f)
	{
		return e.key == f.key;
	}
};

template<class T>
int linear_probing(int size, Element<T> e, int i, int c1, int c2 = 0)
{
	int h_func = e.key % size;
	return (h_func % size + ((c1 % size) * (i % size)) % size) % size;
}

template<class T>
int quadratic_probing(int size, Element<T> e, int i, int c1, int c2)
{
	int h_func = e.key % size;
	return (h_func % size + ((c1 % size) * (i % size)) % size + ((c2 % size) * (i % size) * (i % size)) % size) % size;
}

enum class status
{
	NIL, NON_EMPTY, DELETED
};

template<class T>
class Hash_Table
{
protected:
	vector<Element<T>> hash;
	vector<status> s;
	double load_factor, lambda;
	int (*hp)(int, Element<T>, int, int, int);
	int c1, c2, curSize;
protected:
	void reHashing()
	{
		vector<Element<T>> newHashTable(2 * (int)hash.size());
		vector<status> newStatus(newHashTable.size(), status::NIL);
		for (int i = 0; i < (int)hash.size(); i++)
		{
			if (s[i] == status::NON_EMPTY)
			{
				int j = 0;
				while (j < (int)newHashTable.size())
				{

					int index = this->hp((int)newHashTable.size(), hash[i], j, c1, c2);
					if (newStatus[index] != status::NON_EMPTY)
					{
						newHashTable[index] = hash[i];
						newStatus[index] = status::NON_EMPTY;
						break;
					}
					j++;
				}
				if (j == (int)newHashTable.size())
				{
					throw overflow_error("No possible slot!");
				}
			}
		}
		this->hash = newHashTable;
		this->s = newStatus;
	}
public:
	Hash_Table(int size, int (*hp)(int, Element<T>, int, int, int), double lambda = 0.75)
	{
		srand((unsigned int)time(NULL));
		hash = vector<Element<T>>(size);
		s = vector<status>(size, status::NIL);
		this->hp = hp;
		this->curSize = 0;
		if (this->hp == linear_probing)
		{
			c2 = 0;
			c1 = rand() % 20 + 1;
		}
		else
		{
			c1 = rand() % 20 + 1;
			c2 = rand() % 20 + 1;
		}
		this->load_factor = 0;
		this->lambda = lambda;
		this->curSize = 0;
	}
	void insert(Element<T> e)
	{
		int i = 0;
		while (i < (int)hash.size())
		{
			int index = this->hp((int)hash.size(), e, i, c1, c2);
			if (s[index] != status::NON_EMPTY)
			{
				hash[index] = e;
				s[index] = status::NON_EMPTY;
				this->curSize += 1;
				this->load_factor = (this->curSize * 1.0) / (int)this->hash.size();
				break;
			}
			i++;
		}
		if (i == (int)hash.size())
		{
			throw overflow_error("No possible slot!");
		}
		if (this->load_factor > this->lambda)
		{
			reHashing();
		}
	}
	void print()
	{
		cout << "Hash Table: [";
		for (int i = 0; i < (int)hash.size(); i++)
		{
			if (s[i] == status::NON_EMPTY)
			{
				cout << "(" << hash[i].data << "," << hash[i].key << ")";
			}
			else
			{
				cout << "()";
			}
			cout << (i == (int)hash.size() - 1 ? "" : ";");
		}
		cout << "]";
	}
	void remove(Element<T> e)
	{
		int i = 0;
		while (i < (int)hash.size())
		{
			int index = this->hp((int)this->hash.size(), e, i, c1, c2);
			if (s[index] == status::NIL)
			{
				break;
			}
			if (hash[index] == e)
			{
				hash[index] = Element<T>();
				s[index] = status::DELETED;
				int j = i + 1;
				while (j < (int)hash.size())
				{
					int index2 = this->hp((int)this->hash.size(), e, j, c1, c2);
					if (s[index2] == status::NON_EMPTY)
					{
						s[index2] = status::NIL;
						insert(hash[index2]);
					}
					j++;
				}
				break;
			}
			i++;
		}
		if (i == (int)hash.size())
		{
			throw logic_error("Element does not appear in Hash Table!");
		}
	}
};
#endif // !HASH_TABLE_H
