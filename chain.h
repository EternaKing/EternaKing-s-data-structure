#include<iostream>
#include<utility>
#include<sstream>
class chain {
	friend bool operator!=(const chain&rhs, const chain&lhs);
	friend bool operator==(const chain&rhs, const chain&lhs);
	friend bool operator<(const chain&rhs, const chain&lhs);
	friend std::ostream& operator<<(std::ostream& out, const chain& rhs);
	friend chain& meld(chain&a, chain&b);
	friend chain& merge(chain&a, chain&b);
public:
	struct node
	{
		node* next;
		int element;
		node() = default;
		node(const int &value):element(value){ }
		node(const int &value, node* next)
		{
			element = value;
			this->next = next;
		}
	};
	chain()
	{
		firstnode->next = nullptr;
		listsize = 0;
	}
	chain(const chain& rhs)
	{
		listsize = rhs.listsize;
		node* temp = rhs.firstnode;
		firstnode = new node;
		firstnode->element = temp->element;
		node* targetnode = firstnode;
		while (temp != nullptr)
		{
			targetnode->next = new node(temp->element);
			targetnode = targetnode->next;
			temp = temp->next;
		}
		targetnode->next = nullptr;
		lastnode = targetnode;
	}
	~chain()
	{
		while(firstnode!=nullptr)
		{
			node* nextnode = firstnode->next;
			delete firstnode;
			firstnode = nextnode;
		}
	}
	int& operator[](int index)
	{
		checkindex(index);
		if (index = listsize - 1)
			return lastnode->element;
		else {
			auto temp = firstnode;
			for (int i = 0; i < index; ++i)
				temp = temp->next;
			return temp->element;
		}
	}
	bool empty()const
	{
		return listsize == 0;
	}
	int size()const
	{
		return listsize;
	}
	void setsize(int newsize)
	{
		if (newsize > listsize)
			return;
		else {
			int index = 0;
			auto temp = firstnode;
			for (; index < newsize; ++index)
				temp = temp->next;
			for (index; index < listsize; ++index)
			{
				auto newnode = temp->next;
				delete temp;
				temp = newnode;
			}
			listsize = newsize;
		}
	}
	void set(int index, int value)
	{
		checkindex(index);
		auto temp = firstnode;
		for (int count = 0; count < index; ++index)
			temp = temp->next;
		temp->element = value;
	}
	void remove_range(int start, int end)
	{
		if (start>=end)
		{
			std::ostringstream s;
			s << "start=" << start << "," << "end=" << end << std::endl << "这个范围是无效的";
			throw s.str();
		}
		else {
			auto temp = firstnode;
			int index;
			for (index = 0; index < start - 1; ++index)
				temp = temp->next;
			while (index != end)
			{
				auto nextnode = temp->next;
				temp->next = nextnode->next;
				delete nextnode;
			}
			listsize -= (end - start + 1);
		}
	}
	int& get(int index)const
	{
		int count;
		node* temp = firstnode;
		checkindex(index);
		for (count = 0; count <= index; ++count)
		{
			temp = temp->next;
		}
		return temp->element;
	}
	int indexof(const int& value)const
	{
		int pos = 0;
		node* temp = firstnode;
		while (temp&&temp->element!=value)
		{
			temp = temp->next;
			pos++;
		}
		if (pos == listsize&&temp->element != value)
			pos = -1;
		return pos;
	}
	int last_index_of(int value)
	{
		int pos = -1;
		int index = 0;
		auto temp = firstnode;
		while (temp)
		{
			if (temp->element == value)
				pos = index;
			temp = temp->next;
			index++;
		}
		return pos;
	}
	void erase(int index)
	{
		checkindex(index);
		int count;
		node* temp = firstnode;
		for (int count = 0; count < index - 1; ++count)
			temp = temp->next;
		node* aim = temp->next;
		temp = aim->next;
		delete aim;
		listsize--;
	}
	void insert(int index, const int& value)
	{
		checkindex(index);
		if (index == 0)
			firstnode = new node(value, firstnode);
		else {
			int count;
			node* temp = firstnode;
			for (count = 0; count < index - 1; ++count)
				temp = temp->next;
			node* aim = new node(value);
			aim->next = temp->next;
			temp->next = aim;
		}
			listsize++;
	}
	void pushback(int value)
	{
		node* newnode = new node;
		newnode = lastnode->next;
		newnode->element = value;
		lastnode = newnode;
	}
	void swap(chain& rhs)
	{
		auto temp = rhs.firstnode;
		rhs.firstnode = firstnode;
		firstnode = temp;
		int size = listsize;
		listsize = rhs.listsize;
		rhs.listsize = size;
	}
	void left_shift(int number)
	{
		while (number--)
		{
			auto temp = firstnode->next;
			delete firstnode;
			firstnode = temp;
		}
	}
	void reverse()
	{
		lastnode = firstnode;
		auto temp = firstnode->next;
		firstnode->next = nullptr;
		while (temp->next)
		{
			auto next_temp = temp->next;
			temp->next = firstnode;
			firstnode = temp;
			temp = next_temp;
		}
		firstnode = temp;
	}
	void output(std::ostream& out)const
	{
		for (auto temp = firstnode; temp != nullptr; temp = temp->next)
			out << temp->element << " ";
	}
protected:
	void checkindex(int index)const
	{
		if (index < 0 || index >= listsize)
		{
			std::ostringstream s;
			s << "index=" << index << "size=" << listsize;
			throw s.str();
		}
	}
	node* firstnode;
	node* lastnode;
	int listsize;
};
std::ostream& operator<<(std::ostream& out, const chain& rhs)
{
	rhs.output(out);
	return out;
}
bool operator==(const chain&rhs, const chain&lhs)
{
	bool ret = true;
	if (rhs.listsize != lhs.listsize)
		ret = false;
	else {
		auto rhs_temp = rhs.firstnode, lhs_temp = lhs.firstnode;
		while(rhs_temp&&lhs_temp)
			if (rhs_temp->element != lhs_temp->element)
			{
				ret = false;
				break;
			}
			else {
				rhs_temp = rhs_temp->next;
				lhs_temp = lhs_temp->next;
			}
	}
	return ret;
}
bool operator!=(const chain&rhs, const chain&lhs)
{
	return !(rhs == lhs);
}
bool operator<(const chain&rhs, const chain&lhs)
{
	if (rhs.listsize > lhs.listsize)
		return false;
	bool ret = true;
	if (rhs.listsize != lhs.listsize)
	{
		auto temp_rhs = rhs.firstnode, temp_lhs = lhs.firstnode;
		while (temp_rhs&&temp_lhs)
		{
			if (temp_rhs->element > temp_lhs->element)
			{
				ret = false;
				break;
			}
			temp_rhs = temp_rhs->next;
			temp_lhs = temp_lhs->next;
		}
	}
	else ret = false;
	return ret;
}
chain& meld(chain&a, chain&b)
{
	chain newchain;
	int index = 0;
	auto temp1 = a.firstnode, temp2 = b.firstnode,newtemp= newchain.firstnode;
	while (temp1 || temp2)
	{
		if (index % 2 == 0)
		{
			if (temp1)
			{
				newtemp->next = temp1;
				newtemp = newtemp->next;
				temp1 = temp1->next;
				index++;
				if (temp2)
					temp2 = temp2->next;
				continue;
			}
			else if (temp2)
			{
				newtemp->next = temp2;
				newtemp = newtemp->next;
				temp2 = temp2->next;
				index++;
				continue;
			}
		}
		else {
			if (temp2)
			{
				newtemp->next = temp2;
				newtemp = newtemp->next;
				temp2 = temp2->next;
				index++;
				if (temp1)
					temp1 = temp1->next;
				continue;
			}
			else if (temp1)
			{
				newtemp->next = temp1;
				newtemp = newtemp->next;
				temp1 = temp1->next;
				index++;
				continue;
			}
		}
	}
	newtemp->next = nullptr;
	newchain.listsize = index;
	newchain.lastnode = newtemp;
	//不想重写了，就不析构了！！！！！
}
chain& merge(chain&a, chain&b)
{
	chain newchain;
	newchain.firstnode = new chain::node;
	auto  tempa = a.firstnode, tempb = b.firstnode;
	if (tempa->element >= tempb->element)
	{
		newchain.firstnode->element = tempa->element;
		tempa = tempa->next;
	}
	else {
		newchain.firstnode->element = tempb->element;
		tempb = tempb->next;
	}
	auto temp = newchain.firstnode->next;
	temp = new chain::node;
	while (tempa || tempb)
	{
		if (tempa&&tempb)
		{
			if (tempa->element == tempb->element)
			{
				temp->element = tempa->element;
				temp = temp->next;
				temp = new chain::node;
				temp->element = tempb->element;
				tempa = tempa->next;
				tempb = tempb->next;
				temp = temp->next;
				if (tempa || tempb)
					temp = new chain::node;
				else {
					temp = nullptr;
					break;
				}
			}
			else if (tempa->element > tempa->element)
			{
				temp->element = tempa->element;
				tempa = tempa->next;
				temp = temp->next;
				temp = new chain::node;
			}
			else {
				temp->element = tempb->element;
				tempb = tempb->next;
				temp = temp->next;
				temp = new chain::node;
			}
		}
		else if (tempa)
		{
			temp->element = tempa->element;
			tempa = tempa->next;
			temp = temp->next;
			if (tempa)
				temp = new chain::node;
			else {
				temp = nullptr;
				break;
			}
		}
		else {
			temp->element = tempb->element;
			tempb = tempb->next;
			temp = temp->next;
			if (tempb)
				temp = new chain::node;
			else {
				temp = nullptr;
				break;
			}
		}
	}
	newchain.lastnode = temp;
	newchain.listsize = a.listsize + b.listsize;
}