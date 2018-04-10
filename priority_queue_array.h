#ifndef priority_queue_array_H
#define priority_queue_array_H
#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<iterator>
#include<numeric>
class priority_queue {
public:
	using element = std::pair<int, int>;
	priority_queue() = default;
	priority_queue(const int&size)
	{
		data.reserve(size);
	}
	~priority_queue()
	{
		data.clear();
	}
	void push(int value, int weight)
	{
		auto newdata = std::make_pair(value, weight);
		data.push_back(newdata);
	}
	std::pair<int,int> top()
	{
		if (data.empty())
			throw "没有数据";
		int maxweight = -1, maxpos = -1, i;
		auto _size = data.size();
		for (i = 0; i < _size; ++i)
		{
			if (data[i].second > maxweight)
			{
				maxweight = data[i].second;
				maxpos = i;
			}
		}
		if (i != -1)
			return data[maxpos];
	}
	void pop()
	{
		if (data.empty())
			throw "没有数据";
		int maxweight = -1, maxpos = -1, i;
		auto _size = data.size();
		for (i = 0; i < _size; ++i)
		{
			if (data[i].second > maxweight)
			{
				maxweight = data[i].second;
				maxpos = i;
			}
		}
		std::vector<element> newdata(data.size());
		std::copy(data.begin(), data.begin() + maxpos, newdata.begin());
		std::copy(data.begin() + maxpos + 1, data.end(), newdata.begin() + maxpos);
		data = newdata;
	}
private:
	std::vector<element> data;
};
#endif