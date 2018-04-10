#ifndef ARRAY_TREE_H
#define ARRAY_TREE_H

#include<iostream>
#include<vector>
#include<utility>
class array_tree {
public:
	using element = std::pair<bool, int>;
	array_tree() = default;
	array_tree(int size)
	{
		tree.resize(size);
		treesize = 0;
		for (auto iter = tree.begin(); iter != tree.end(); ++iter)
		{
			(*iter).first = false;
			(*iter).second = 0;
		}
	}
	~array_tree()
	{
		treesize = 0;
		tree.clear();
	}
	bool emepty() const
	{
		return treesize == 0;
	}
	int size() const
	{
		return treesize;
	}
	void insert(const int& value)
	{
		if (tree.empty())
			tree.reserve(10);
		for (auto iter=tree.begin();iter!=tree.end();++iter)
		{
			if (!(*iter).first)
			{
				(*iter).first = true;
				(*iter).second = value;
				treesize++;
				return;
			}
		}
		tree.push_back(std::make_pair(true, value));
		treesize++;
		tree.reserve(2 * tree.size());
	}
	bool erase(const int& value)
	{
		for (auto iter = tree.begin(); iter != tree.end(); ++iter)
		{
			if ((*iter).second == value)
			{
				(*iter).first = false;
				return true;
			}
		}
		return false;
	}
	void preorder(int index)
	{
		if (index>treesize)
			return;
		if (tree[index - 1].first)
			std::cout << tree[index - 1].second << " ";
		preorder(2 * index);
		preorder(index * 2 + 1);
	}
	void inorder(int index)
	{
		if (index > treesize)
			return;
		if (tree[index-1].first)
		{
			if (2 * index <= treesize)
				inorder(2 * index);
			std::cout << tree[index - 1].second << " ";
			if (2 * index + 1 <= treesize)
				inorder(2 * index + 1);
		}
	}
	void postorder(int index)
	{
		if (index > treesize)
			return;
		if (tree[index - 1].first)
		{
			if (2 * index <= treesize)
				postorder(2 * index);
			if (2 * index + 1 <= treesize)
				postorder(2 * index + 1);
			std::cout << tree[index - 1].second << " ";
		}
	}
	void levelorder(int index)
	{
		auto count = treesize;
		for (int i = index; i < tree.size(); ++i)
		{
			if (tree[i- 1].first)
			{
				std::cout << tree[i-1].second << " ";
				count--;
			}
			if (count == 0)
				return;
		}
	}
	void preorder_visit(int index,int& start,int*& aim)
	{
		if (index>treesize)
			return;
		if (tree[index - 1].first)
			aim[start++] = tree[index - 1].second;
		preorder(2 * index);
		preorder(index * 2 + 1);
	}
	void postorder_visit(int index,int&start,int*& aim)
	{
		if (index > treesize)
			return;
		if (tree[index - 1].first)
		{
			if (2 * index <= treesize)
				postorder(2 * index);
			if (2 * index + 1 <= treesize)
				postorder(2 * index + 1);
			aim[start] = tree[index - 1].second;
		}
	}
	int* creat_array(bool if_pre,bool if_post)
	{
		int start = 0;
		if (if_pre&&if_post)
			throw "不能同时为TURE";
		int* arr = new int[treesize + 1];
		if (if_pre)
			preorder_visit(1, start, arr);
		else postorder_visit(1, start, arr);
		return arr;
	}
private:
	std::vector<element> tree;
	int treesize = 0;
};
#endif