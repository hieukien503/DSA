#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <list>
using namespace std;

template<class T>
class Stack
{
public:
	virtual void push(T element) = 0;
	virtual void pop() = 0;
	virtual T top() = 0;
	virtual bool empty() = 0;
	virtual int size() = 0;
};

template<class T>
class ArrayStack : public Stack<T>
{
private:
	T* arr;
	int topArray, max_size;
public:
	ArrayStack(int size = 10)
	{
		this->max_size = size;
		this->arr = new T[this->max_size]{ T() };
		this->topArray = -1;
	}
	~ArrayStack()
	{
		delete[] this->arr;
	}
protected:
	void ensureCapacity()
	{
		if (topArray == this->max_size)
		{
			int newSize = this->max_size * 2;
			T* newArr = new T[newSize]{ T() };
			for (int i = 0; i < this->max_size; i++)
			{
				newArr[i] = this->arr[i];
			}
			this->max_size = newSize;
			delete[] this->arr;
			this->arr = newArr;
		}
	}
public:
	void push(T element) override
	{
		ensureCapacity();
		this->arr[++topArray] = element;
	}
	void pop() override
	{
		if (this->topArray == -1)
		{
			throw underflow_error("Stack Underflow!");
		}
		--topArray;
	}
	T top() override
	{
		if (this->topArray == -1)
		{
			throw runtime_error("Stack is empty!");
		}
		return this->arr[this->topArray];
	}
	bool empty() override
	{
		return this->topArray == -1;
	}
	int size() override
	{
		return this->topArray + 1;
	}
};

template<class T>
class ListStack : public Stack<T>
{
private:
	list<T> l;
public:
	void push(T element) override
	{
		l.push_back(element);
	}
	void pop() override
	{
		if (l.empty() == true)
		{
			throw underflow_error("Stack Underflow!");
		}
		l.pop_back();
	}
	T top() override
	{
		return l.back();
	}
	bool empty() override
	{
		return l.empty();
	}
	int size() override
	{
		return l.size();
	}
};
#endif // STACK_H
