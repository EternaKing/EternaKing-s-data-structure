#include<iostream>
#include<utility>
#include<algorithm>
#include<numeric>
class queue{
public:
	struct node
	{
		node* next=nullptr;
		int element;
		node() = default;
		node(const int &value) :element(value) { }
		node(const int &value, node* next)
		{
			element = value;
			this->next = next;
		}
	};
	queue() = default;
	queue(const queue& rhs)
	{
		if (rhs.empty())
			throw "这是一个空队列";
		queuesize = rhs.queuesize;
		queuehead = new node(rhs.queuehead->element);
		auto temp = queuehead, temp_rhs = rhs.queuehead->next;
		while (temp_rhs)
		{
			temp->next = new node(temp_rhs->element);
			temp = temp->next;
			temp_rhs = temp_rhs->next;
		}
		temp->next = nullptr;
		queuerear = temp;
	}
	bool empty()const 
	{
		return queuesize == 0;
	}
	int size()const 
	{
		return queuesize;
	}
	int& front()
	{
		if (queuehead == nullptr)
			throw"这是一个空队列";
		return queuehead->element;
	}
	int& back()
	{
		if (queuehead == nullptr)
			throw "这是一个空队列";
		return queuerear->element;
	}
	void pop()
	{
		if (queuehead == nullptr)
			throw"这是一个空队列";
		auto temp = queuehead->next;
		delete queuehead;
		queuehead = temp;
		queuesize--;
	}
	void push(const int& value)
	{
		if (queuehead == nullptr)
		{
			queuehead = new node(value);
			queuerear = queuehead;
			queuerear->next = nullptr;
			return;
		}
		queuerear->next = new node(value);
		queuerear = queuerear->next;
		queuesize++;
	}
private:
	node* queuehead=nullptr;
	node* queuerear=nullptr;
	int queuesize;
};