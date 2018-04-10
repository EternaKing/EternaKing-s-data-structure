#ifndef  AVL_SEARCH_TREE_H
#define  AVL_SEARCH_TREE_H

#include<iostream>
#include<algorithm>
#include<string>
#include<utility>
#include<stack>
#include<vector>
#include<queue>


template<typename T>
struct AVL_Node {
	AVL_Node* left_child = nullptr;
	AVL_Node* right_child = nullptr;
	T data = 0;
	int balance_factor = 0;
	AVL_Node() = default;
	AVL_Node(T& value) :data(value), left_child(nullptr), right_child(nullptr), balance_factor(0) {}
	AVL_Node(const AVL_Node*& rhs) :left_child(rhs->left_child), right_child(rhs->right_child), data(rhs->data), balance_factor(rhs->balance_factor) {}
};
template<typename T>
class AVL_search_tree {
private:
	AVL_Node<T>* root = nullptr;
	size_t tree_size = 0;
	static void Clear(AVL_Node<T>* lhs)
	{
		if (lhs)
		{
			Clear(lhs->left_child);
			Clear(lhs->right_child);
			delete lhs;
		}
	}
	static size_t Height(AVL_Node<T>* rhs)
	{
		if (rhs)
			return std::max(Height(rhs->left_child), Height(rhs->right_child)) + 1;
		else return 0;
	}
	static int Absolute(int value)
	{
		return value >= 0 ? value : -value;
	}
	static void(*Visit)(AVL_Node<T>*);
	static void Pre_order(AVL_Node<T>* rhs)
	{
		if (rhs)
		{
			Visit(rhs);
			Pre_order(rhs->left_child);
			Pre_order(rhs->right_child);
		}
	}
	static void In_order(AVL_Node<T>* rhs)
	{
		if (rhs)
		{
			In_order(rhs->left_child);
			Visit(rhs);
			In_order(rhs->right_child);
		}
	}
	static void Post_order(AVL_Node<T>* rhs)
	{
		if (rhs)
		{
			Post_order(rhs->left_child);
			Post_order(rhs->right_child);
			Visit(rhs);
		}
	}
	static void Level_order(AVL_Node<T>* rhs)
	{
		std::queue<AVL_Node<T>*> BFS;
		BFS.push(rhs);
		while (!BFS.empty())
		{
			AVL_Node* now_operated = BFS.front();
			BFS.pop();
			Visit(now_operated);
			if (now_operated->left_child)
				BFS.push(now_operated->left_child);
			if (now_operated->right_child)
				BFS.push(now_operated->right_child);
		}
	}
public:
	AVL_search_tree() = default;
	~AVL_search_tree() { Clear(); }
	AVL_Node<T>* Left_left_rotate(AVL_Node<T>* rhs)
	{
		AVL_Node<T>* new_root = rhs->left_child;
		rhs->left_child = new_root->right_child;
		new_root->right_child = rhs;
		rhs->balance_factor = Height(rhs->left_child) - Height(rhs->right_child);
		new_root->balance_factor = Height(new_root->left_child) - Height(new_root->right_child);
		return new_root;
	}
	AVL_Node<T>* Right_right_rotate(AVL_Node<T>* rhs)
	{
		AVL_Node<T>* new_root = rhs->right_child;
		rhs->right_child = new_root->left_child;
		new_root->left_child = rhs;
		rhs->balance_factor = Height(rhs->left_child) - Height(rhs->right_child);
		new_root->balance_factor = Height(new_root->left_child) - Height(new_root->right_child);
		return new_root;
	}
	AVL_Node<T>* Left_right_rotate(AVL_Node<T>* rhs)
	{
		rhs->left_child = Right_right_rotate(rhs->left_child);
		return Left_left_rotate(rhs);
	}
	AVL_Node<T>* Right_left_rorate(AVL_Node<T>* rhs)
	{
		rhs->right_child = Left_left_rotate(rhs->right_child);
		return Right_right_rotate(rhs);
	}
	void Insert(T& value)
	{
		tree_size++;
		if (!root)
		{
			root = new AVL_Node<T>(value);
			return;
		}
		std::stack<AVL_Node<T>*> path;
		AVL_Node<T>* temp_for_root = root;
		while (temp_for_root)
		{
			path.push(temp_for_root);
			if (temp_for_root->data > value)
			{
				if (temp_for_root->left_child)
					temp_for_root = temp_for_root->left_child;
				else {
					temp_for_root->left_child = new AVL_Node<T>(value);
					break;
				}
			}
			if (temp_for_root->data < value)
				if (temp_for_root->right_child)
					temp_for_root = temp_for_root->right_child;
				else {
					temp_for_root->right_child = new AVL_Node<T>(value);
					break;
				}
		}
		while (!path.empty())
		{
			AVL_Node<T>* node_in_path = path.top();
			path.pop();
			if (node_in_path->data > value)
				node_in_path->balance_factor++;
			else node_in_path->balance_factor--;
			if (Absolute(node_in_path->balance_factor) == 0)
				return;
			else if (Absolute(node_in_path->balance_factor) == 2)
			{
				if (node_in_path->left_child&&node_in_path->left_child->balance_factor == 1)
					node_in_path = Left_left_rotate(node_in_path);
				else if (node_in_path->left_child&&node_in_path->left_child->balance_factor == -1)
					node_in_path = Left_right_rotate(node_in_path);
				else if (node_in_path->right_child&&node_in_path->right_child->balance_factor == 1)
					node_in_path = Right_left_rorate(node_in_path);
				else if (node_in_path->right_child&&node_in_path->right_child->balance_factor == -1)
					node_in_path = Right_right_rotate(node_in_path);
				if (!path.empty())
				{
					AVL_Node<T>* precursor = path.top();
					if (precursor->data > node_in_path->data)
						precursor->left_child = node_in_path;
					else precursor->right_child = node_in_path;
				}
				else root = node_in_path;
				return;
			}
		}
	}
	void Remove(T value)
	{
		if (!root)
			return;
		std::vector<AVL_Node<T>*> path;
		int wait_for_erase = -1;
		AVL_Node<T>* target_node = root;
		while (target_node)
		{
			path.push_back(target_node);
			if (target_node->data > value)
				target_node = target_node->left_child;
			else if (target_node->data < value)
				target_node = target_node->right_child;
			else {
				wait_for_erase = path.size() - 1;
				break;
			}
		}
		if (wait_for_erase == -1)
			return;
		tree_size--;
		if (target_node->left_child)
		{
			target_node = target_node->left_child;
			while (target_node->right_child)
			{
				path.push_back(target_node);
				target_node = target_node->right_child;
			}
			value = path[wait_for_erase]->data = target_node->data;
			if (wait_for_erase == path.size() - 1)
				path[wait_for_erase]->left_child = target_node->left_child;
			else path[path.size() - 1]->right_child = nullptr;
			delete target_node;
		}
		else if (target_node->right_child)
		{
			target_node = target_node->right_child;
			while (target_node->left_child)
			{
				path.push_back(target_node);
				target_node = target_node->left_child;
			}
			value = path[wait_for_erase]->data = target_node->data;
			if (wait_for_erase == path.size() - 1)
				path[wait_for_erase]->right_child = target_node->right_child;
			else path[path.size() - 1]->left_child = nullptr;
			delete target_node;
		}
		else {
			if (path.size() == 1)
			{
				root = nullptr;
				return;
			}
			if (path[wait_for_erase - 1]->data > value)
				path[wait_for_erase - 1]->left_child = nullptr;
			else path[wait_for_erase - 1]->right_child = nullptr;
			delete target_node;
			path.pop_back();
		}
		for (int back = path.size() - 1; back >= 0; back--)
		{
			if (path[back]->data > value)
				path[back]->balance_factor--;
			else path[back]->balance_factor++;
			if (Absolute(path[back]->balance_factor) == 1)
				return;
			else if (Absolute(path[back]->balance_factor) == 2)
			{
				if (path[back]->balance_factor == 2)
				{
					if (path[back]->left_child->balance_factor >= 0)
						path[back] = Left_left_rotate(path[back]);
					else path[back] = Left_right_rotate(path[back]);
				}
				else {
					if (path[back]->right_child->balance_factor <= 0)
						path[back] = Right_right_rotate(path[back]);
					else path[back] = Right_left_rorate(path[back]);
				}
				if (back - 1 >= 0)
					if (path[back - 1]->data > path[back]->data)
						path[back - 1]->left_child = path[back];
					else path[back - 1]->right_child = path[back];
				else root = path[back];
			}
		}
	}
	size_t Height() { return Height(root); }
	bool Empty() { return tree_size == 0; }
	size_t Size() { return tree_size; }
	void Clear()
	{
		Clear(root);
		tree_size = 0;
	}
	void Pre_order(void(*thevisit)(AVL_Node<T>* rhs))
	{
		Visit = thevisit;
		Pre_order(root);
	}
	void In_order(void(*thevisit)(AVL_Node<T>* rhs))
	{
		Visit = thevisit;
		In_order(root);
	}
	void Post_order(void(*thevisit)(AVL_Node<T>* rhs))
	{
		Visit = thevisit;
		Post_order(root);
	}
	void Level_order(void(*thevisit)(AVL_Node<T>* rhs))
	{
		Visit = thevisit;
		Level_order(root);
	}
};
template<typename T>
void(*AVL_search_tree<T>::Visit)(AVL_Node<T>* rhs) = nullptr;


#endif 