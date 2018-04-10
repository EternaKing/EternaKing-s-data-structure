#ifndef priority_queue_chain_h
#define priority_queue_chain_h
#include<iostream>
#include<algorithm>
#include<utility>
#include<memory>
#include<numeric>
struct node {
	using element = std::pair<int, int>;
	node * next = nullptr;
	element data;
	node() = default;
	node(int weight, int value)
	{
		data.first = weight;
		data.second = value;
	}
};
class priority_queue{
public:
	priority_queue() = default;
	priority_queue(const priority_queue& rhs)
	{
		node* temp = rhs.chain,*& temp_chain=chain;
		chain_size = rhs.chain_size;
		while(temp)
		{
			temp_chain = new node(temp->data.first, temp->data.second);
			temp_chain = temp_chain->next;
			temp = temp->next;
		}
	}
	~priority_queue()
	{
		while (chain)
		{
			auto temp = chain;
			chain = chain->next;
			delete temp;
		}
		chain_size = 0;
	}
	bool empty()
	{
		return size == 0;
	}
	int size()
	{
		return chain_size;
	}
	void push(int weight,int value)
	{
		node* newnode = new node(weight, value);
		newnode->next = chain;
		chain = newnode;
		chain_size++;
	}
	node* top()
	{
		node* maxpos = nullptr, *temp = chain;
		int max_weight = -1;
		while (temp)
		{
			if (temp->data.first > max_weight)
			{
				maxpos = temp;
			}
			temp = temp->next;
		}
		return maxpos;
	}
	void pop()
	{
		if (!chain)
			return;
		chain_size--;
	    if (chain_size == 1)
		{
			delete chain;
			chain = nullptr;
			return;
		}
		else if (chain_size == 2)
		{
			if (chain->data.first > chain->next->data.first)
			{
				auto temp = chain;
				chain = chain->next;
				delete temp;
			}
			else {
				delete chain->next;
				chain->next = nullptr;
			}
			return;
		}
		node* maxpos = chain, *be_maxpos = nullptr;
		node* temp = chain->next, *be_temp = chain;
		while (temp)
		{
			if (temp->data.first > maxpos->data.first)
			{
				maxpos = temp;
				be_maxpos = be_temp;
			}
			be_temp = temp;
			temp = temp->next;
		}
		if (!be_temp)
		{
			node* temp = chain;
			chain = chain->next;
			delete temp;
		}
		else {
			be_temp->next = temp->next;
			delete temp;
		}
	}
private:
	node* chain = nullptr;
	int chain_size;
};
#endif