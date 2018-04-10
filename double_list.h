#include<iostream>
#include<utility>
#include<sstream>
#include<initializer_list>
class double_list {
public:
	struct node
	{
		int value;
		node* next;
		node* previous;
		node() = default;
		node(int element) :value(element) {};
	};
	double_list() = default;
	double_list(std::initializer_list<int> il)
	{
		auto iter = il.begin();
		firstnode = new node(*iter++);
		firstnode->previous = nullptr;
		auto temp = firstnode;
		for (iter; iter != il.end(); ++iter)
		{
			temp->next = new node(*iter);
			auto before = temp;
			temp = temp->next;
			temp->previous = before;
		}
		lastnode = temp;
		lastnode->next = nullptr;
		listsize = il.size();
	}
	double_list(const double_list& rhs)
	{
		firstnode = new node(rhs.firstnode->value);
		firstnode->previous = nullptr;
		auto temprhs = rhs.firstnode->next, temp = firstnode;
		for (temprhs; temprhs; temprhs = temprhs->next)
		{
			temp->next = new node(temprhs->value);
			auto before = temp;
			temp = temp->next;
			temp->previous = before;
		}
		lastnode = temp;
		lastnode->next = nullptr;
		listsize = rhs.listsize;
	}
	~double_list()
	{
		free();
	}
	//ÖØÔØÔËËã·ûº¯Êý
	int& operator[](const int index)
	{
		return getindex(index);
	}
	double_list& operator=(const double_list& rhs)
	{
		double_list newlist(rhs);
		free();
		return newlist;
	}
	int& getindex(const int index)
	{
		check_index(index);
		if (index > listsize / 2)
		{
			auto temp = lastnode;
			for (int i = listsize - 1; i >= index; --i)
				temp = temp->previous;
			return temp->value;
		}
		else {
			auto temp = firstnode;
			for (int i = 0; i < index; ++i)
				temp = temp->next;
			return temp->value;
		}
	}
	int index_of(const int& element)
	{
		int pos = -1, index = 0;
		auto temp = firstnode;
		while (temp)
		{
			if (temp->value == element)
			{
				pos = index;
				break;
			}
			else {
				index++;
				temp = temp->next;
			}
		}
		return pos;
	}
	int last_index_of(const int& element)
	{
		int pos = -1, index = 0;
		auto temp = firstnode;
		while (temp)
		{
			if (temp->value == element)
			{
				pos = index;
			}
			index++;
			temp = temp->next;
		}
		return pos;
	}
	void push_back(const int&element)
	{
		auto newnode = new node(element);
		lastnode->next = newnode;
		newnode->previous = lastnode;
		lastnode = newnode;
		listsize++;
	}
	void push_front(const int& element)
	{
		auto newnode = new node(element);
		firstnode->previous = newnode;
		newnode->next = firstnode;
		firstnode = newnode;
		listsize++;
	}
	void erase(int index)
	{
		check_index(index);
		if (index == listsize - 1)
		{
			auto temp = lastnode->previous;
			temp->next = nullptr;
			delete lastnode;
			lastnode = temp;
			listsize--;
			return;
		}
		else if (index == 0)
		{
			auto temp = firstnode->next;
			temp->previous = nullptr;
			delete firstnode;
			firstnode = temp;
			listsize--;
			return;
		}
		if (index > listsize / 2)
		{
			auto temp = lastnode;
			for (int i = listsize - 1; i >index; --i)
				temp = temp->previous;
			auto before = temp->previous;
			auto later = temp->next;
			delete temp;
			before->next = later;
			later->previous = before;
			listsize--;
		}
		else {
			auto temp = firstnode;
			for (int i = 0; i < index; ++i)
				temp = temp->next;
			auto before = temp->previous;
			auto later = temp->next;
			delete temp;
			before->next = later;
			later->previous = before;
			listsize--;
		}
	}
	void insert(int index, const int&element)
	{
		check_index(index);
		if (index == 0)
			push_front(element);
		else if (index = listsize - 1)
			push_back(element);
		if (index > listsize / 2)
		{
			auto temp = lastnode;
			for (int i = listsize - 1; i >= index; --index)
				temp = temp->previous;
			auto later = temp->next;
			auto newnode = new node(element);
			newnode->previous = temp;
			newnode->next = later;
			temp->next = newnode;
			later->previous = newnode;
			listsize++;
		}
		else {
			auto temp = firstnode;
			for (int i =0; i<=index; --index)
				temp = temp->previous;
			auto before = temp->previous;
			auto newnode = new node(element);
			before->next = newnode;
			temp->previous = newnode;
			newnode->previous = before;
			newnode->next = temp;
			listsize++;
		}
	}
	int size()
	{
		return listsize;
	}
	bool empty()
	{
		return listsize == 0;
	}
private:
	void check_index(int index)
	{
		if (index < 0 || index >= listsize)
		{
			std::ostringstream s;
			s << "index=" << index << "size=" << listsize;
			throw s.str();
		}
	}
	void free()
	{
		while (firstnode != lastnode)
		{
			auto temp = firstnode->next;
			delete firstnode;
			firstnode = temp;
		}
		delete firstnode;
	}
	int listsize = 0;
	node* firstnode;
	node* lastnode;
};

