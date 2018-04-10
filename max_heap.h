#include<iostream>
#include<algorithm>
#include<utility>
#include<numeric>
template <class T>
class max_heap {
public:
	max_heap() = default;
	max_heap(T* arr,int arr_size)
	{
		initialize_heap(arr, arr_size);
	}
	max_heap(const max_heap& rhs)
	{
		heap_size = rhs.heap_size;
		heap_capacity = rhs.heap_capacity;
		heap = new T[heap_size];
		for (int i = 1; i <= heap_size; ++i)
			heap[i] = rhs.heap[i];
	}
	~max_heap()
	{
		delete heap;
		heap_size = heap_capacity = 0;
	}
	void push(const T& value)
	{
		if (heap_size + 1 == heap_capacity)
			change_capacity();
		int current_node = ++heap_size;
		while (current_node != 1 && heap[current_node / 2] < value)
		{
			heap[current_node] = heap[current_node / 2];
			current_node /= 2;
		}
		heap[current_node] = value;
	}
	void pop()
	{
		if (heap_size == 0)
			throw "空堆";
		else if (heap_size == 1)
		{
			heap[1].~T();
			heap_size = 0;
			return;
		}
		T last_element = heap[heap_size--];
		int current_node = 1, child = 2;
		for (child; child <= heap_size; current_node=child,child*=2)
		{
			if (child < heap_size&&heap[child] < heap[child + 1])
				++child;
			if (last_element > heap[child])
				break;
			heap[current_node] = heap[child];
		}
		heap[current_node] = last_element;
	}
	int size()
	{
		return heap_size;
	}
	bool empty()
	{
		return heap_size== 0;
	}
	T& top()
	{
		return heap[1];
	}
	void change_max(const T& new_max)
	{
		int parent = 1, child = 2;
		while (child < heap_size)
		{
			if (child + 1 <= heap_size&&heap[child] < heap[child + 1])
				child++;
			if (heap[child] < new_max)
				break;
			heap[parent] = heap[child];
			parent = child;
			child *= 2;
		}
		heap[child / 2] = new_max;
	}
	void remove(int index)
	{
		if (index > heap_size)
			throw "堆中无该索引的元素";
		if (index == 1)
		{
			max_heap::pop();
			return;
		}
		T last_element = heap[heap_size--];
		int current_node = index, child = 2 * index;
		for (child; child <= heap_size; current_node = child, child *= 2)
		{
			if (child < heap_size&&heap[child] < heap[child + 1])
				++child;
			if (last_element > heap[child])
				break;
			heap[current_node] = heap[child];
		}
		heap[current_node] = last_element;
	}
	void initialize_heap(T* arr, int arr_size)
	{
		if (heap)
			delete heap;
		heap_size = arr_size;
		heap_capacity = 2 * heap_size;
		heap = new T[heap_capacity];
		for (int i = 0; i < arr_size; ++i)
			heap[i + 1] = arr[i];
		for (int parent = heap_size / 2; parent >= 1; --parent)
		{
			int child = 2 * parent;
			T temp = heap[parent];
			while (child <= heap_size)
			{
				if (child + 1 <= heap_size&&heap[child] < heap[child + 1])
					child++;
				if (heap[child] <= temp)
					break;
				heap[child / 2] = heap[child];
				child *= 2;
			}
			heap[child / 2] = temp;
		}
	}
	void heap_sort(T* arr, int size)
	{
		max_heap<T> temp(arr, size);
		for (int i = size - 1; i >= 0; i--)
		{
			arr[i] = temp.top();
			temp.pop();
		}
	}
private:
	void change_capacity()
	{
		heap_capacity *= 2;
		T* newheap = new T[heap_capacity];
		std::copy(heap + 1, heap + heap_size + 1, newheap + 1);
		delete heap;
		heap = newheap;
	}
	T* heap=nullptr;
	int heap_size;
	int heap_capacity;
};