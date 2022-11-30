#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <list>
using namespace std;

template<class T>
class Queue
{
public:
	virtual void push(T element) = 0;
	virtual void pop() = 0;
	virtual T front() = 0;
	virtual T back() = 0;
	virtual bool empty() = 0;
	virtual int size() = 0;
};

template<class T>
class ArrayQueue : public Queue<T>
{
private:
	T* arr;
	int rearArray, frontArray, max_size;
public:
	ArrayQueue(int size = 10)
	{
		this->max_size = size;
		this->arr = new T[this->max_size]{ T() };
		this->rearArray = -1;
		this->frontArray = 0;
	}
	~ArrayQueue()
	{
		delete[] this->arr;
	}
protected:
	void ensureCapacity()
	{
		if (rearArray == this->max_size)
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
		this->arr[++rearArray] = element;
	}
	void pop() override
	{
		if (this->frontArray > this->rearArray || this->rearArray == -1)
		{
			throw underflow_error("Queue Underflow!");
		}
		++frontArray;
	}
	T front() override
	{
		if (this->rearArray == -1 || this->frontArray > this->rearArray)
		{
			throw runtime_error("Queue is empty!");
		}
		return this->arr[frontArray];
	}
	T back() override
	{
		if (this->rearArray == -1 || this->frontArray > this->rearArray)
		{
			throw runtime_error("Queue is empty!");
		}
		return this->arr[rearArray];
	}
	bool empty() override
	{
		return this->rearArray == -1 || this->frontArray > this->rearArray;
	}
	int size() override
	{
		return this->rearArray - this->frontArray + 1;
	}
};

template<class T>
class ListQueue : public Queue<T>
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
			throw underflow_error("Queue Underflow!");
		}
		l.pop_front();
	}
	T front() override
	{
		return l.front();
	}
	T back() override
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
#endif // QUEUE_H
