#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include<iostream>
#include<algorithm>
#include<memory>
#include<numeric>
#include<utility>
class arraylist {
	friend bool operator==(const arraylist& rhs,const arraylist& lhs);
	friend bool operator!=(arraylist& rhs, arraylist& lhs);
	friend bool operator<(arraylist& rhs, arraylist&lhs);
	//friend void meld(const arraylist& rhs, const arraylist& lhs);
public:
	arraylist() = default;
	arraylist(const arraylist& rhs):list(rhs.list),arraylength(rhs.arraylength),listsize(rhs.listsize){ }
	arraylist(int sizenumber) :arraylength(sizenumber),listsize(0)
	{
		list = new int[sizenumber];
	}
	~arraylist()
	{
		delete[]list;
	}
	arraylist& operator=(const arraylist& rhs)
	{
		list = rhs.list;
		listsize = rhs.~arraylist;
		arraylength = rhs.arraylength;
		return *this;
	}
	int& operator[](int index) const
	{
		if (checkindex(index))
			return list[index];
		else return list[0];
	}
	std::pair<arraylist&, arraylist&> split()
	{
		int length = arraylength / 2;
		arraylist a(length), b(length);
		for (int i = 0; i < listsize; ++i)
		{
			if (i % 2)
				b[b.listsize++] = list[i];
			else a[a.listsize++] = list[i];
		}
		return std::make_pair(a, b);
	}
	void set_size(int newsize)
	{
		int *p = new int[newsize];
		std::copy(list, list + listsize, p);
		delete[]p;
		list = p;
		listsize = arraylength = newsize;
	}
	void reserve(int thecapacity)
	{
		if (arraylength >= thecapacity)
			return;
		else changelengthID(list, arraylength, thecapacity);
	}
	void push_back(int value)
	{
		if (listsize < arraylength)
			list[listsize++] = value;
		else {
			changelengthID(list, arraylength, 2 * arraylength);
			list[listsize++] = value;
		}
	}
	void pop_back()
	{
		list[--listsize] = 0;
	}
	int& set(int index, int value)
	{
		if (checkindex(index))
		{
			int temp = list[index];
			list[index] = value;
			return temp;
		}
		else return list[0];
	}
	void trimtosize()
	{
		if (arraylength == listsize)
			return;
		else {
			int *p = new int[listsize];
			std::copy(list, list + listsize, p);
			delete[]list;
			list = p;
			arraylength = listsize;
		}
	}
	void clear()
	{
		delete[]list;
		int *p = new int[arraylength];
		listsize = 0;
	}
	void remove_range(int start, int end)
	{
		if (start >= end)
		{
			std::cout << "这个区域无效";
			return;
		}
		else std::copy(list + end + 1, list + listsize, list + start);
		listsize -= (end - start + 1);
		if (listsize < (arraylength / 4))
		{
			int newsize = std::max(arraylength / 2, 100);
			changelengthID(list, arraylength, newsize);
		}
	}
	void reserve()
	{
		int *p = new int[arraylength];
		for (int i = 0; i < listsize; ++i)
			p[i] = list[listsize - i - 1];
		delete[]list;
		list = p;
	}
	void left_shift(int distance)
	{
		for (int i = 0; i < listsize - distance; ++i)
			list[i] = list[i + distance];
		listsize -= distance;
	}
	void half()
	{
		int *p = new int[arraylength];
		int index = 1, i;
		for (i = 0; index < listsize; index+=2)
			p[i++] = p[index];
		listsize -= (listsize / 2);
	}
	bool empty()const
	{
		return listsize == 0;
	}
	int capacity()
	{
		return arraylength;
	}
	int size() const
	{
		return listsize;
	}
	int& get(int index)
	{
		int ret;
		if(checkindex(index))
			ret=list[index];
		else ret = 0;
		return ret;
	}
	int last_index_of(int value)
	{
		int pos = -1;
		for (int i = 0; i < listsize; ++i)
			if (list[i] == value)
				pos = i;
		return pos;
	}
	int indexof(const int& theelement) const
	{
		int index = (int)std::find(list, list + listsize, theelement);
		if (index != listsize)
			return index;
		else return -1;
	}
	void erase(int index)
	{
		if (checkindex(index))
			std::copy(list + index + 1, list + listsize, list + index);
		listsize--;
		if (listsize < (arraylength / 4))
		{
			int newsize =std::max(arraylength / 2, 100);
			changelengthID(list, arraylength, newsize);
		}
	}
	void insert(int index, int& theelement)
	{
		if (checkindex(index))
			if (listsize == arraylength)
			{
				changelengthID(list, arraylength, 2 * arraylength);
				arraylength *= 2;
			}
		std::copy_backward(list + index, list + listsize, list + listsize + 1);
		list[index] = theelement;
		listsize++;
	}
	void print(std::ostream& out)
	{
		std::for_each(list, list + listsize, [&](int a) {out << a << " "; });
	}
	void swap(arraylist& rhs)
	{
		arraylist temp = rhs;
		rhs = *this;
		*this = temp;
	}
protected:
	void changelengthID(int* &a, int oldlength, int newlength)
	{
		int *temp = new int [newlength];
		int number = std::min(oldlength, newlength);
		std::copy(a, a + number, temp);
		delete[]a;
		a = temp;
	}
	bool checkindex(const int index) const
	{
		bool ret = true;
		if (index<0 || index>listsize)
		{
			ret = false;
			std::cerr << "这个下标是非法的" << std::endl;
		}
		return ret;
	}
	int *list;                                                                         //线性表
	int arraylength=50;                                                               //数组的大小 
	int listsize;                                                                      //线性表元素数量
};
bool operator==(const arraylist& rhs,const arraylist& lhs)
{
	bool ret = true;
	if (rhs.listsize != lhs.listsize)
		ret = false;
	else {
		for (int i = 0; i < rhs.listsize; ++i)
		{
			if (rhs[i] == lhs[i])
				continue;
			else ret = false;
		}
	}
	return ret;
}
bool operator!=(arraylist& rhs, arraylist& lhs)
{
	return !(rhs == lhs);
}
bool operator<(arraylist& rhs, arraylist& lhs)
{
	int len = std::min(rhs.listsize, lhs.listsize);
	bool ret = true;
	if (rhs != lhs)
	{
		for (int i = 0; i < len; ++i)
		{
			if (rhs[i] > lhs[i])
			{
				ret = false;
				break;
			}
		}
	}
	else ret = false;
	return ret;
}
#endif