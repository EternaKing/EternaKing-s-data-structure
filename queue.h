#ifndef QUEUE_H
#define QUEUE_H
#include<iostream>
#include<utility>
#include<initializer_list>
#include<algorithm>
#include<numeric>
class my_queue {
public:
	my_queue() = default;
	my_queue(const int initiasize)
	{
		arraylength = initiasize;
		queuesize = queueback = queuefront = 0;
		queue = new int[initiasize];
	}
	my_queue(std::initializer_list<int> il)
	{
		queueback=queuesize = il.size();
		arraylength = queuesize * 2;
		queue = new int[arraylength];
		std::copy(il.begin(), il.end(), queue + 1);
		queuefront = 0;
	}
	my_queue(const my_queue& rhs)
	{
		queuesize = rhs.queuesize;
		queuefront = rhs.queuefront;
		queueback = rhs.queueback;
		arraylength = rhs.arraylength;
		queue = new int[arraylength];
		std::copy(rhs.queue, rhs.queue + queuesize - 1, queue);
	}
	~my_queue()
	{
		delete[]queue;
	}
	bool empty()
	{
		return queuefront == queueback;
	}
	int size()
	{
		return queuesize;
	}
	int& front()
	{
		return queue[(queuefront+1)%arraylength];
	}
	int& back()
	{
		return queue[queueback];
	}
	void pop()
	{
		if (queuefront == queueback)
			throw"©у╤сап";
		queuefront = ++queuefront%arraylength;
		queuesize--;
	}
	void push(const int& value)
	{
		if ((queueback + 1) % arraylength == queuefront)
		{
			int *newqueue = new int[2 * arraylength];
			int start = (queuefront + 1) % arraylength;
			if (start < 2)
				std::copy(queue + start, queue + start + arraylength - 1, newqueue);
			else {
				std::copy(queue + start, queue+arraylength, newqueue);
				std::copy(queue + start, queue +queueback+1, newqueue+arraylength-start);
			}
			queuefront = 2 * arraylength - 1;
			queueback = arraylength - 2;
			arraylength *= 2;
			delete[]queue;
			queue = newqueue;
		}
		queueback = (queueback + 1) % arraylength;
		queue[queueback] = value;
		queuesize++;
	}
	std::ostream& output(std::ostream& os)
	{
		int temp = queuefront;
		while (temp != queueback)
			os << queue[++temp%arraylength];
		return os;
	}
private:
	int* queue;
	int queueback;
	int queuefront;
	int arraylength;
	int queuesize;
};
#endif