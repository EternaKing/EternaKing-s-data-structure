#ifndef CONTAINER_H
#define CONTAINER_H

#include<iostream>
#include<memory>
#include<initializer_list>

template<typename T>
class Container
{
	using Value_Type = T;
	using _Iterator = Value_Type*;
	using _Container_iterator = _Iterator const;
	using _Const_Container_iterator = const _Container_iterator;
	std::allocator<Value_Type> _alloc;//����ռ�
	_Iterator _vec = nullptr;//��������
	_Iterator _pos_of_begin = nullptr;//�����洢���ݵ�λ��
	_Iterator _pos_of_end = nullptr;//δ�������ݵĵ�һ��λ��
	size_t _capacity = 0;//������С
	size_t _start_index = 0;//������ʼλ��
	int _max_index = -1;//�������λ�ã�0��ʾ������
						//���index�Ƿ�Խ��
	void Check_Index(size_t index) {
		if (_start_index + index > _max_index)
			throw "The index has been out of range!";
	}
	void Check_Index() {
		if (_max_index < _start_index)
			throw "The index has been out of range!";
	}
	//��������ռ��Ƿ��㹻
	void Check_Capacity() {
		if (_max_index + 1 == _capacity)
			Resize(2 * _capacity);
	}
	//�ͷ�����
	void Free() {
		while (_pos_of_end != _pos_of_begin)
			_alloc.destroy(--_pos_of_end);
		_max_index = -1;
		_alloc.deallocate(_vec, _capacity);
		_pos_of_begin = _pos_of_end = _vec = nullptr;
		_start_index = _capacity = 0;
	}
public:
	//�ĸ����캯��
	Container() = default;
	Container(size_t init_size) {
		_pos_of_begin = _pos_of_end = _vec = _alloc.allocate(init_size);
		_capacity = init_size;
		_start_index = 0;
		_max_index = -1;
	}
	Container(std::initializer_list<Value_Type>& rhs) {
		_capacity = rhs.size() * 2;
		index = rhs.size() - 1;
		_start_index = 0;
		_pos_of_begin = _vec = _alloc.allocate(_capacity);
		_pos_of_end = std::uninitialized_copy(rhs.begin(), rhs.end(), _vec);
	}
	Container(Container<Value_Type>& rhs) {
		_capacity = 2 * rhs._capacity;
		_max_index = rhs._max_index - rhs._start_index;
		_start_index = 0;
		_pos_of_begin = _vec = _alloc.allocate(_capacity);
		_pos_of_end = std::uninitialized_copy(rhs._pos_of_begin, rhs._pos_of_end, _vec);
	}
	//����Free()��������
	~Container() {
		Free();
	}
	//����������С
	void Resize(size_t newsize) {
		std::allocator<Value_Type> new_allocator;
		_Iterator new_vec = new_allocator.allocate(newsize);
		_Iterator new_pos_of_begin = new_vec;
		_Iterator new_pos_of_end = nullptr;
		int new_max_index = -1;
		if (newsize >= _max_index - _start_index + 1) {
			new_pos_of_end = std::uninitialized_copy(_pos_of_begin, _pos_of_end, new_vec);
			new_max_index = _max_index - _start_index;
		}
		else {
			new_pos_of_end = std::uninitialized_copy_n(_pos_of_begin, newsize, new_vec);
			new_max_index = newsize - 1;
		}
		Free();
		_alloc = new_allocator;
		_vec = new_vec;
		_pos_of_begin = new_pos_of_begin;
		_pos_of_end = new_pos_of_end;
		_capacity = newsize;
		_start_index = 0;
		_max_index = new_max_index;
	}
	bool Empty()const {
		return _max_index < _start_index;
	}
	size_t Capacity()const {
		return _capacity;
	}
	size_t Size()const {
		return _max_index + 1 - _start_index;
	}
	void Push_Back(const T& value) {
		Check_Capacity();
		_alloc.construct(_pos_of_end++, value);
		_max_index++;
	}
	void Pop_Back() {
		Check_Index();
		_alloc.destroy(--_pos_of_end);
		_max_index--;
		if (_max_index - _start_index < _capacity / 2)
			Resize(_capacity / 2);
	}
	void Pop_Front() {
		Check_Index();
		_alloc.destroy(_pos_of_begin++);
		_start_index++;
		if (_max_index - _start_index < _capacity / 2)
			Resize(_capacity / 2);
	}
	//���ص�һ��Ԫ��
	Value_Type Front() {
		Check_Index();
		return *_pos_of_begin;
	}
	//�������һ��Ԫ��
	Value_Type Back() {
		Check_Index();
		return *(_pos_of_end - 1);
	}
	Value_Type At(size_t index) {
		Check_Index(index);
		return _vec[_start_index + index];
	}
	Container<Value_Type>& operator=(const Container<Value_Type>& rhs) {
		if (&rhs == this)
			return *this;
		Free();
		_capacity = rhs._capacity;
		_max_index = rhs._max_index - rhs._start_index;
		_vec = _pos_of_begin = _alloc.allocate(_capacity);
		_pos_of_end = std::uninitialized_copy(rhs._pos_of_begin, rhs._pos_of_end, _vec);
		_start_index = 0;
		return *this;
	}
	Value_Type operator[](size_t index) {
		return At(index);
	}
	_Container_iterator Begin() {
		return _pos_of_begin;
	}
	_Container_iterator End() {
		return _pos_of_end;
	}
	_Const_Container_iterator Cbegin() {
		return _pos_of_begin;
	}
	_Const_Container_iterator Cend() {
		return _pos_of_end;
	}
};
#endif 
