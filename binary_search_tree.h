#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include<iostream>
#include<utility>
#include<algorithm>
#include<queue>
#include<stack>
#include<numeric>
#include<string>
using element = std::pair<int, int>;
struct binary_search_tree_node {
	element data;
	binary_search_tree_node* left_child=nullptr;
	binary_search_tree_node* right_child=nullptr;
	binary_search_tree_node() = default;
	binary_search_tree_node(const element& value)
	{
		data.first = value.first;
		data.second = value.second;
		left_child = right_child = nullptr;
	}
	binary_search_tree_node(int keyword, int value)
	{
		data.first = keyword;
		data.second = value;
		left_child = right_child = nullptr;
	}
	binary_search_tree_node(const element& value, binary_search_tree_node* initia_left, binary_search_tree_node* initia_right)
	{
		data.first = value.first;
		data.second = value.second;
		left_child = initia_left;
		right_child = initia_right;
	}
};
class binary_search_tree {
public:
	binary_search_tree() = default;
	binary_search_tree(std::vector<element> rhs)
	{
		for (auto iter = rhs.begin(); iter != rhs.end(); ++iter)
			this->insert(*iter);
	}
	~binary_search_tree()
	{
		erase();
	}
	bool emepty()
	{
		return tree_size == 0;
	}
	int get_size()
	{
		return tree_size;
	}
	void preorder(void(*thevisit)(binary_search_tree_node* node))
	{
		visit = thevisit;
		preorder(root);
	}
	void inorder(void(*thevisit)(binary_search_tree_node* node))
	{
		visit = thevisit;
		inorder(root);
	}
	void postorder(void(*thevisit)(binary_search_tree_node* node))
	{
		visit = thevisit;
		postorder(root);
	}
	void levelorder(void(*thevisit)(binary_search_tree_node* node))
	{
		visit = thevisit;
		std::queue<binary_search_tree_node*> storage;
		auto temp = root;
		while (temp)
		{
			visit(temp);
			if (temp->left_child)
				storage.push(temp->left_child);
			if (temp->right_child)
				storage.push(temp->right_child);
			if (!storage.empty())
			{
				temp = storage.front();
				storage.pop();
			}
		}
	}
	void output_in_range(int low, int high)
	{
		auto temp = root;
		inorder_for_output(temp, low, high);
	}
	int height(binary_search_tree_node* node)
	{
		if (!node)
			return 0;
		int hl = height(node->left_child);
		int hr = height(node->right_child);
		if (hl > hr)
			return ++hl;
		else return ++hr;
	}
	void erase()
	{
		postorder(dispose);
		root = nullptr;
		tree_size = 0;
	}
    element* search(const int& keyword)
	{
		binary_search_tree_node* temp = root;
		while (temp != nullptr)
		{
			if (keyword < temp->data.first)
				temp = temp->left_child;
			else if (keyword > temp->data.first)
				temp = temp->right_child;
			else return &temp->data;
		}
		return nullptr;
	}
	void insert(const element& value)
	{
		binary_search_tree_node* temp_root = root, *be_temp_root = nullptr;
		while(temp_root)
		{
			be_temp_root = temp_root;
			if (value.first > temp_root->data.first)
				temp_root = temp_root->right_child;
			else if (value.first < temp_root->data.first)
				temp_root = temp_root->left_child;
			else {
				temp_root->data.second = value.second;
				return;
			}
		}
		binary_search_tree_node* newnode = new binary_search_tree_node(value);
		if (root)
			if (value.first > be_temp_root->data.first)
				be_temp_root->right_child = newnode;
			else
				be_temp_root->left_child = newnode;
		else root = newnode;
		tree_size++;
	}
	void remove(const int& keyword)
	{
		binary_search_tree_node* temp_root = root, *be_temp_root = nullptr;
		while (temp_root&&temp_root->data.first != keyword)
		{
			be_temp_root = temp_root;
			if (keyword > temp_root->data.first)
				temp_root = temp_root->right_child;
			else temp_root = temp_root->left_child;
		}
		if (!temp_root)
			return;
		if (temp_root->left_child&&temp_root->right_child)
		{
			binary_search_tree_node* search = temp_root->left_child, *be_search = search;
			while(search->right_child)
			{
				be_search = search;
				search = search->right_child;
			}
			binary_search_tree_node* newnode = new binary_search_tree_node(search->data, temp_root->left_child, temp_root->right_child);
			if (!be_temp_root)
				root = newnode;
			else if (temp_root == be_temp_root->left_child)
				be_temp_root->left_child = newnode;
			else be_temp_root->right_child = newnode;
			if (be_search == temp_root)
				be_temp_root = newnode;
			else be_temp_root = be_search;
			delete temp_root;
			temp_root = search;
		}
		binary_search_tree_node* temp;
		if (temp_root->left_child)
			temp = temp_root->left_child;
		else temp = temp_root->right_child;
		if (temp_root == root)
			root = temp;
		else {
			if (temp_root == be_temp_root->left_child)
				be_temp_root->left_child = temp;
			else be_temp_root->right_child = temp;
		}
		delete temp_root;
		tree_size--;
	}
private:
	binary_search_tree_node* root = nullptr;
	int tree_size = 0;

	static void dispose(binary_search_tree_node* node)
	{
		delete node;
	}
	static void(*visit)(binary_search_tree_node* node);
	static void preorder(binary_search_tree_node* node)
	{
		if (node)
		{
			visit(node);
			preorder(node->left_child);
			preorder(node->right_child);
		}
	}
	static void inorder(binary_search_tree_node* node)
	{
		if (node)
		{
			inorder(node->left_child);
			visit(node);
			inorder(node->right_child);
		}
	}
	static void postorder(binary_search_tree_node* node)
	{
		if (node)
		{
			postorder(node->left_child);
			postorder(node->right_child);
			visit(node);
		}
	}
	static void inorder_for_output(binary_search_tree_node* node, int low, int high)
	{
		if (node)
		{
			if (node->data.first > low)
				inorder_for_output(node->left_child, low, high);
			if (node->data.first >= low&&node->data.first <= high)
				std::cout << node->data.first <<' '<< node->data.second << std::endl;
			if (node->data.first < high)
				inorder_for_output(node->right_child, low, high);
		}
	}
};
void(*binary_search_tree::visit)(binary_search_tree_node* node) = nullptr;
#endif