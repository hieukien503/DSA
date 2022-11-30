#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
bool is_greater(T& a, T& b)
{
	return a > b;
}

template<typename T>
bool is_smaller(T& a, T& b)
{
	return a < b;
}

template<typename T>
class Heap
{
protected:
	T* arr;
	int count;
	int max_size;
public:
	Heap(int max_size)
	{
		this->count = 0;
		this->max_size = max_size;
		this->arr = new T[this->max_size];
		for (int i = 0; i < this->max_size; i++)
		{
			arr[i] = 0;
		}
	}
	Heap(int max_size, T& init_val)
	{
		this->count = 0;
		this->max_size = max_size;
		this->arr = new T[this->max_size];
		for (int i = 0; i < this->max_size; i++)
		{
			arr[i] = init_val;
		}
	}
	~Heap()
	{
		delete[] arr;
	}
protected:
	void resizeHeap(int newMaxSize)
	{
		T* newArr = new T[newMaxSize];
		memcpy(newArr, arr, count * sizeof(int));
		this->max_size = newMaxSize;
		delete[] this->arr;
		this->arr = newArr;
	}
	void makeHeap(int index, bool (*comparision)(T&, T&))
	{
		if (index == 0)
		{
			return;
		}
		int parent_index = (index % 2 == 0 ? (index - 2) / 2 : (index - 1) / 2);
		if (comparision(this->arr[index], this->arr[parent_index]))
		{
			swap(this->arr[index], this->arr[parent_index]);
		}
		makeHeap(parent_index, comparision);
	}
	void heapify(T* start, T* end, int i, bool (*compare)(T&, T&))
	{
		int root = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int len = end - start;
		if (left < len && compare(arr[root], arr[left]))
		{
			root = left;
		}
		if (right < len && compare(arr[root], arr[right]))
		{
			root = right;
		}
		if (root != i)
		{
			swap(start[root], start[i]);
			heapify(start, end, root, compare);
		}
	}
	void heapsort(T* start, T* end, bool (*compare)(T&, T&))
	{
		int len = end - start;
		for (int i = len / 2 - 1; i >= 0; i--)
		{
			heapify(start, end, i, compare);
		}
		for (int i = len - 1; i > 0; i--)
		{
			swap(start[i], start[0]);
			heapify(start, start + i, 0, compare);
		}
	}
public:
	void makeHeap(int index, int opt)
	{
		if (index == 0)
		{
			return;
		}
		if (opt % 2 == 0)
		{
			makeHeap(index, is_greater<T>);
		}
		else
		{
			makeHeap(index, is_smaller<T>);
		}
	}
	void insertHeap(T& val, int opt)
	{
		if (count == max_size - 1)
		{
			resizeHeap(2 * this->max_size);
		}
		this->arr[this->count] = val;
		makeHeap(count, opt);
		count++;
	}
	void printHeap()
	{
		cout << "[";
		for (int i = 0; i < this->count; i++)
		{
			cout << this->arr[i] << (i == this->count - 1 ? "" : ",");
		}
		cout << "]\n";
	}
	void heap_sort(int opt)
	{
		if (opt % 2 == 0)
		{
			heapsort(this->arr, this->arr + count, is_greater<T>);
		}
		else
		{
			heapsort(this->arr, this->arr + count, is_smaller<T>);
		}
	}
};

int main()
{
	int arr[] = { 19, 10, 28, 35, 27, 7, 29, 5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	make_heap(arr, arr + n, is_greater<int>);
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << ' ';
	}
}