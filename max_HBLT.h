#include<iostream>
#include<algorithm>
#include<numeric>
#include<utility>
#include<memory>
#include<queue>
#include<cstdio>
struct tree_node {
	using element = std::pair<int, int>;
	element data;
	tree_node* leftchild=nullptr;
	tree_node* rightchild=nullptr;
	tree_node() = default;
	tree_node(const int& value)
	{
		data.second = value;
		data.first = 1;
		leftchild = nullptr;
		rightchild = nullptr;
	}
};
class MAX_HBLT {
public:
	MAX_HBLT() = default;
	MAX_HBLT(int* arr, int arr_size)
	{
		initialize(arr, arr_size);
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
	void meld(MAX_HBLT& rhs)
	{
		meld(root, rhs.root);
		tree_size += rhs.tree_size;
		rhs.root = nullptr;
		rhs.tree_size = 0;
	}
	void push(const int& value)
	{
		tree_node* newnode = new tree_node(value);
		meld(root, newnode);
		tree_size++;
	}
	void pop()
	{
		if (root == nullptr)
			throw "empty tree";
		tree_node* left = root->leftchild, *right = root->rightchild;
		delete root;
		root = left;
		meld(root, right);
		tree_size--;
	}
	void erase()
	{
		postorder(dispose);
		root = nullptr;
		tree_size = 0;
	}
	void initialize(int* arr, int arr_size)
	{
		std::queue<tree_node*> q;
		erase();
		for (int i = 0; i < arr_size; ++i)
			q.push(new tree_node(arr[i]));
		for (int i = 0; i < arr_size-1; ++i)
		{
			tree_node* b = q.front();
			q.pop();
			tree_node* c = q.front();
			q.pop();
			meld(b, c);
			q.push(b);
		}
		if (arr_size > 0)
			root = q.front();
		tree_size = arr_size;
	}
private:
	tree_node* root=nullptr;
	int tree_size=0;

	static void meld(tree_node*& x, tree_node*& y)
	{
		if (y == nullptr)
			return;
		else if (x == nullptr)
		{
			x = y;
			return;
		}
		if (x->data.second < y->data.second)
			std::swap(x, y);
		meld(x->rightchild, y);
		if (x->leftchild ==nullptr)
		{
			x->leftchild = x->rightchild;
			x->rightchild = nullptr;
			x->data.first = 1;
		}
		else {
			if (x->leftchild->data.first < x->rightchild->data.first)
				std::swap(x->leftchild, x->rightchild);
			x->data.first = x->rightchild->data.first + 1;
		}
	}
	static void dispose(tree_node* node)
	{
		delete node;
	}
	static void(*visit)(tree_node*);
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
};
void(*MAX_HBLT::visit)(tree_node* node) = nullptr;