#include <iostream>
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
void printArray(T* start, T* end)
{
	int n = end - start;
	for (int i = 0; i < n; i++)
	{
		cout << start[i] << (i == n - 1 ? "\n" : " ");
	}
}

template<typename T>
void selection_sort(T* start, T* end, bool (*compare)(T&, T&) = is_smaller<T>)
{
	int len = end - start;
	for (int i = 0; i < len - 1; i++)
	{
		int min_idx = i;
		for (int j = i + 1; j < len; j++)
		{
			if (compare(start[j], start[min_idx]))
			{
				min_idx = j;
			}
		}
		swap(start[i], start[min_idx]);
	}
}

template<typename T>
void insertion_sort(T* start, T* end, bool (*compare)(T&, T&) = is_smaller<T>)
{
	int len = end - start;
	for (int i = 1; i < len; i++)
	{
		int j = i - 1;
		T temp = start[i];
		while (j >= 0 && compare(temp, start[j]))
		{
			start[j + 1] = start[j];
			j--;
		}
		start[j + 1] = temp;
	}
}

template<typename T>
T MedianOfThree(T& a, T& b, T& c)
{
	if ((a > b) ^ (a > c))
	{
		return a;
	}
	if ((b < a) ^ (b < c))
	{
		return b;
	}
	return c;
}

template<typename T>
int partition(T* start, T* end, bool (*compare)(T&, T&) = is_smaller<T>)
{
	int len = end - start;
	T pivot = start[len - 1];
	int left = 0, right = len - 2;
	while (true)
	{
		while (left <= right && compare(start[left], pivot))
		{
			left++;
		}
		while (right >= left && compare(pivot, start[right]))
		{
			right--;
		}
		if (left >= right)
		{
			break;
		}
		swap(start[left], start[right]);
		left++;
		right--;
	}
	swap(start[left], start[len - 1]);
	return left;
}

template<typename T>
void quicksort(T* start, T* end, bool (*compare)(T&, T&) = is_smaller<T>)
{
	int len = end - start;
	if (len > 0)
	{
		T pivot = MedianOfThree(start[0], start[len / 2], start[len - 1]);
		int pivot_idx = (pivot == start[0] ? 0 : (pivot == start[len - 1] ? len - 1 : len / 2));
		int k = partition(start, end);
		quicksort(start, start + k, compare);
		quicksort(start + k + 1, end, compare);
	}
}

template<typename T>
void heapify(T* start, T* end, int i, bool (*compare)(T&, T&))
{
	int root = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int len = end - start;
	if (left < len && compare(start[root], start[left]))
	{
		root = left;
	}
	if (right < len && compare(start[root], start[right]))
	{
		root = right;
	}
	if (root != i)
	{
		swap(start[root], start[i]);
		heapify(start, end, root, compare);
	}
}

template<typename T>
void heapsort(T* start, T* end, bool (*compare)(T&, T&) = is_smaller<T>)
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

template<typename T>
void introsort(T* start, T* end, int depthLimit, bool (*compare)(T&, T&) = is_smaller<T>)
{
	int len = end - start;
	if (len < 16)
	{
		insertion_sort(start, end, compare);
		return;
	}
	if (depthLimit == 0)
	{
		heapsort(start, end, compare);
		return;
	}
	T pivot = MedianOfThree(start[0], start[len / 2], start[len - 1]);
	if (pivot == start[0])
	{
		swap(start[0], start[len - 1]);
	}
	else if (pivot == start[len / 2])
	{
		swap(start[len / 2], start[len - 1]);
	}
	int k = partition(start, end);
	introsort(start, start + k, depthLimit - 1, compare);
	introsort(start + k + 1, end, depthLimit - 1, compare);
}

template<typename T>
void sort(T* start, T* end, bool (*compare)(T&, T&) = is_smaller<T>)
{
	int len = end - start;
	int depthLimit = 2 * (int)log(len);
	introsort(start, end, depthLimit, compare);
}

template<typename T>
void hybridQuickSort(T* start, T* end, int min_size, bool (*compare)(T&, T&) = is_smaller<T>)
{
	int len = end - start;
	if (len < min_size)
	{
		insertion_sort(start, end, compare);
	}
	else
	{
		T pivot = MedianOfThree(start[0], start[len / 2], start[len - 1]);
		if (pivot == start[0])
		{
			swap(start[0], start[len - 1]);
		}
		else if (pivot == start[len / 2])
		{
			swap(start[len / 2], start[len - 1]);
		}
		int k = partition(start, end);
		if (k < len / 2)
		{
			hybridQuickSort(start, start + k, min_size, compare);
			start = start + k + 1;
		}
		else
		{
			hybridQuickSort(start + k + 1, end, min_size, compare);
			end = start + k;
		}
	}
}

template<typename T>
void merge(T* start, T* mid, T* end, bool (*compare)(T&, T&) = is_smaller<T>)
{
	int len1 = mid - start, len2 = end - mid;
	T* left = new T[len1], * right = new T[len2];
	memcpy(left, start, len1 * sizeof(T));
	memcpy(right, mid, len2 * sizeof(T));
	int i = 0, j = 0, k = 0;
	while (i < len1 && j < len2)
	{
		if (compare(left[i], right[j]) == true)
		{
			start[k] = left[i];
			i++;
		}
		else
		{
			start[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < len1)
	{
		start[k] = left[i];
		i++;
		k++;
	}
	while (j < len2)
	{
		start[k] = right[j];
		j++;
		k++;
	}
}

template<typename T>
void mergeSort(T* start, T* end, bool (*compare)(T&, T&) = is_smaller<T>)
{
	if (start == end - 1)
	{
		return;
	}
	int len = end - start;
	int mid = len / 2;
	mergeSort(start, start + mid, compare);
	mergeSort(start + mid, end, compare);
	merge(start, start + mid, end, compare);
}

template<typename T>
void TimSort(T* start, T* end, int min_size, bool (*compare)(T&, T&) = is_smaller<T>)
{
	int len = end - start;
	for (int i = 0; i < len; i += min_size)
	{
		insertion_sort(start + i, start + min(i + min_size, len), compare);
	}
	cout << "Insertion Sort: ";
	printArray(start, end);
	int i = 1;
	for (int s = min_size; s < len; s = 2 * s)
	{
		for (int l = 0; l < len; l += 2 * s)
		{
			int mid = l + s;
			int right = min(l + 2 * s, len);
			if (mid < right)
			{
				merge(start + l, start + mid, start + right);
			}
			cout << "Merge " << i << ": ";
			printArray(start, end);
			i++;
		}
	}
}

template<typename T>
void ShellSort(T* start, T* end, int* num_segment_list, int num_phase, bool (*compare)(T&, T&) = is_smaller<T>)
{
	int len = end - start;
	insertion_sort(num_segment_list, num_segment_list + num_phase);
	for (int i = num_phase - 1; i >= 0; i--)
	{
		int interval = num_segment_list[i];
		for (int j = interval; j < len; j++)
		{
			T temp = start[j];
			int k = j;
			while (k >= interval && compare(temp, start[k - interval]))
			{
				start[k] = start[k - interval];
				k -= interval;
			}
			start[k] = temp;
		}
	}
}

template<typename T>
void oddEvenSort(T* start, T* end, bool (*compare)(T&, T&) = is_smaller<T>)
{
	int len = end - start;
	bool isSorted = false;
	while (!isSorted)
	{
		isSorted = true;
		for (int i = 1; i < len - 1; i += 2)
		{
			if (compare(start[i + 1], start[i]))
			{
				swap(start[i + 1], start[i]);
				isSorted = false;
			}
		}
		for (int i = 0; i < len - 1; i += 2)
		{
			if (compare(start[i + 1], start[i]))
			{
				swap(start[i + 1], start[i]);
				isSorted = false;
			}
		}
	}
}

int main()
{
	int array[] = { 19, 20, 18, 17 ,12, 13, 14, 15, 1, 2, 9, 6, 4, 7, 11, 16, 10, 8, 5, 3 };
	int min_size = 4;
	TimSort(&array[0], &array[20], min_size);
}