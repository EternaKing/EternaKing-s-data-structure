#include<iostream>
#include<vector>
#include<initializer_list>
#include<numeric>
#include<algorithm>
#include<utility>
#include<queue>
struct tree_node {
	int element;
	tree_node* leftchild;
	tree_node* rightchild;
	tree_node() = default;
	tree_node(const int&value) :element(value), leftchild(nullptr), rightchild(nullptr) { };
};
class binary_tree {
public:
	binary_tree() = default;
	binary_tree(const binary_tree&rhs)
	{
		root = new tree_node;
		copy_a_node(rhs.root, root);
	}
	~binary_tree()
	{
		erase();
	}
	void preorder(void(*thevisit)(tree_node* node))
	{
		visit = thevisit;
		preorder(root);
	}
	void inorder(void(*thevisit)(tree_node* node))
	{
		visit = thevisit;
		inorder(root);
	}
	void postorder(void(*thevisit)(tree_node* node))
	{
		visit = thevisit;
		postorder(root);
	}
	void levelorder(void(*thevisit)(tree_node* node))
	{
		visit = thevisit;
		std::queue<tree_node*> storage;
		auto temp = root;
		while (temp)
		{
			visit(temp);
			if (temp->leftchild)
				storage.push(temp->leftchild);
			if (temp->rightchild)
				storage.push(temp->rightchild);
			if (!storage.empty())
			{
				temp = storage.front();
				storage.pop();
			}
		}
	}
	std::pair<int,int> maxnode_height()
	{
		if (root)
		{
			std::queue<tree_node*> q;
			q.push(root);
			return max_node(q);
		}
		else return std::make_pair(0, -1);
	}
	int Tree_size() const
	{
		return treesize;
	}
	bool emepty()
	{
		return treesize == 0;
	}
	int height(tree_node* node)
	{
		if (!node)
			return 0;
		int hl = height(node->leftchild);
		int hr = height(node->rightchild);
		if (hl > hr)
			return ++hl;
		else return ++hr;
	}
	bool is_equal(const binary_tree& rhs)
	{
		return is_equal(rhs.root, root);
	}
	void swap_tree()
	{
		swap_tree(root);
	}
	void erase()
	{
		preorder(dispose);
		root = nullptr;
		treesize = 0;
	}
	int count_node()
	{
		int number = 0;
		count(root, number);
		return number;
	}
private:
	tree_node* root;
	int treesize;
	//静态成员
	static void dispose(tree_node* node)
	{
		delete node;
	}
	static void(*visit)(tree_node*);//公有访问方法
	static void preorder(tree_node* node)
	{
		if (node)
		{
			visit(node);
			preorder(node->leftchild);
			preorder(node->rightchild);
		}
	}
	static void inorder(tree_node* node)
	{
		if (node)
		{
			inorder(node->leftchild);
			visit(node);
			inorder(node->rightchild);
		}
	}
	static void postorder(tree_node* node)
	{
		if (node)
		{
			postorder(node->leftchild);
			postorder(node->rightchild);
			visit(node);
		}
	}
	static void copy_a_node(tree_node* source,tree_node* aim)
	{
		if (source)
		{
			aim->element = source->element;
			aim->leftchild = new tree_node;
			aim->rightchild = new tree_node;
			copy_a_node(source->leftchild, aim->leftchild);
			copy_a_node(source->rightchild, aim->rightchild);
		}
	}
	static bool is_equal(tree_node* rhs,tree_node* lhs)
	{
		if (!rhs && !lhs)
			return true;
		if (!rhs || !lhs)
			return false;
		if (rhs->element == lhs->element)
			return is_equal(rhs->leftchild, lhs->leftchild) && is_equal(rhs->rightchild, lhs->rightchild);
		else return false;
	}
	static void swap_tree(tree_node* rhs)
	{
		if (rhs)
		{
			auto temp = rhs->leftchild;
			rhs->leftchild = rhs->rightchild;
			rhs->rightchild = temp;
			swap_tree(rhs->leftchild);
			swap_tree(rhs->rightchild);
		}
	}
	static void count(tree_node* node,int& number)
	{
		if (node)
			number++;
		count(node->leftchild, number);
		count(node->rightchild, number);
	}
	static std::pair<int,int> max_node(std::queue<tree_node*>& Q)
	{
		static int floor = -1;
		int cnt = 0;
		tree_node* temp;
		std::queue<tree_node*> newQ;
		while (!Q.empty())
		{
			temp = Q.front();
			Q.pop();
			cnt++;
			if (temp->leftchild)
				newQ.push(temp->leftchild);
			if (temp->rightchild)
				newQ.push(temp->rightchild);
		}
		if (newQ.empty())
			return std::make_pair(0, floor);
		floor++;
		if (cnt > max_node(newQ).second)
			return std::make_pair(cnt, floor);
		else return max_node(newQ);
	}
};
void(*binary_tree::visit)(tree_node* node) = nullptr;//初始化函数指针静态成员