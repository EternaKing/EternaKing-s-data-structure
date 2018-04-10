#include<iostream>
#include<initializer_list>
class diag_matrix {
	friend std::ostream& operator<<(std::ostream&,const diag_matrix&);
	friend std::istream& operator>>(std::istream&, diag_matrix&);
	friend diag_matrix& operator+( diag_matrix&,  diag_matrix&);
	friend diag_matrix& operator-(diag_matrix&,  diag_matrix&);
	friend diag_matrix& operator*( diag_matrix&,  diag_matrix&);
public:
	diag_matrix(int size)
	{
		if (size < 1)
			throw"矩阵维数必须大于0";
		n = size;
		element = new int[size];
	}
	diag_matrix() = default;
	diag_matrix(std::initializer_list<int> il)
	{
		if (!il.size())
			throw"初始化所用的数据不能为0";
		n = il.size();
		element = new int[n];
		int index = 0;
		for (auto iter = il.begin(); iter != il.end(); ++iter)
		{
			element[index++] = *iter;
		}
	}
	~diag_matrix()
	{
		delete[]element;
	}
	int get(int therows, int thecolumns)
	{
		if (therows<1 || thecolumns<1 || therows>n || thecolumns>n)
			throw"矩阵中没有对应元素";
		if (therows == thecolumns)
			return element[therows - 1];
		else return 0;
	}
	void set(int newrows, int newcolumns,int newvalue)
	{
		if (newrows<1 || newcolumns<1 || newrows>n || newcolumns>n)
			throw"矩阵中没有对应元素";
		if (newrows == newcolumns)
			element[newrows - 1] = newvalue;
		else throw"除了对角线之外的其他元素必须是0";
	}
	int size()
	{
		return n;
	}
private:
	int n;
	int* element;
};
std::ostream& operator<<(std::ostream& out, const diag_matrix& rhs)
{
	for (int i = 0; i < rhs.n; ++i)
	{
		for (int j = 0; j < rhs.n; ++j)
		{
			if (i == j)
				std::cout << rhs.element[i] << " ";
			else std::cout << 0 << " ";
		}
		std::cout << std::endl;
	}
	return out;
}
std::istream& operator>>(std::istream& is, diag_matrix& rhs)
{
	for (int i = 0; i < rhs.n; ++i)
		is >> rhs.element[i];
	return is;
}
diag_matrix& operator+(diag_matrix& rhs,diag_matrix& lhs)
{
	if (rhs.n != lhs.n)
		throw"这两个矩阵的维数不同";
	for (int i = 0; i < rhs.n; ++i)
		rhs.element[i] += lhs.element[i];
	return rhs;
}
diag_matrix& operator-(diag_matrix& rhs, diag_matrix& lhs)
{
	if (rhs.n != lhs.n)
		throw"这两个矩阵的维数不同";
	for (int i = 0; i < rhs.n; ++i)
		rhs.element[i] -=lhs.element[i];
	return rhs;
}
diag_matrix& operator*(diag_matrix& rhs,diag_matrix& lhs)
{
	if (rhs.n != lhs.n)
		throw"这两个矩阵的维数不同";
	for (int i = 0; i < rhs.n; ++i)
	 rhs.element[i]*=lhs.element[i];
	return rhs;
}