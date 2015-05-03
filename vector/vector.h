#include <iostream>
#include <vector>

//struct for vector<bool>
struct bit
{
public:
	bool* value;
	char pos;//position of bit in the byte
	bit()
	{
		value = 0;
		pos = 0;
	};
	bit(bit& x)
	{
		value = x.value;
		pos = x.pos;
	};

	bit& operator=(bool x)
	{
		*value = ( (*value) && (~(1<<pos)) ) //making  the bit equal to false
				|| ( (x?1:0)<<pos);//making  the bit equal to x
		return *this;
	};

	operator bool()
	{
		return (*value)&&(1<<pos);
	};

};



template <class T,class A_x = std::allocator<T> >
class MyVector 
{
protected:
	A_x Alloc;
	T* value;
	size_t _size;//count of elements of array
	size_t cup;//count of reserve memory
public:	

	MyVector(size_t __size= 0,T _v = 0)
	{
		value = 0;
		_size= 0;
		resize(_size);
		_size= _size;
		for(int i = 0; i<_size; ++i)
			(*this)[i] = _v;
	};

	MyVector(MyVector& x)
	{
		_size= 0;
		value = 0;
		*this = x;
	};

	MyVector&  operator=(MyVector& x)
	{
		resize(x._size);
		for(int i = 0; i<x._size; ++i)
			(*this)[i] = x[i];
		_size= x._size;
		return *this;
	};
	
	void pop_back()
	{
		--_size;
		if (cup > 2*_size)
			resize(size);
	};

	void push_back(T x)
	{
		if (cup == _size)
			resize(2*cup);
		value[_size++] = x;
	};

	T& operator[](size_t x)
	{
		if (x<_size)
			return value[x];
		else
			throw "Out of bounds";
	};

	void resize(size_t new_cup)
	{
		T* new_value = Alloc.allocate(new_cup);
		if (_size> new_cup) 
			_size= new_cup;
		if (value) 
		{
			for(int i = 0; i<_size; ++i)
				new_value[i] = value[i];
			Alloc.deallocate(value,cup);
		};
		cup = new_cup;
		value = new_value;
	};

	size_t size()
	{
		return _size;
	};
	size_t reserved()
	{
		return cup;
	};

};


template <class A_x>
class MyVector<bool,A_x>
{
protected:
	A_x Alloc;
	bool* value;
	size_t _size;
	size_t cup;
public:
	
	

	MyVector(size_t __size= 0,bool _v = 0)
	{
		value = 0;
		_size= 0;
		resize(_size);
		_size= _size;
		for(int i = 0; i<_size; ++i)
			(*this)[i] = _v;
	};

	MyVector(MyVector& x)
	{
		_size= 0;
		value = 0;
		*this = x;
	};

	MyVector&  operator=(MyVector& x)
	{
		resize(x._size);
		for(int i = 0; i<x._size; ++i)
			(*this)[i] = x[i];
		_size= x.size;
		return *this;
	};
	
	void pop_back()
	{
		--_size;
		if (cup > 2*_size)
			resize(_size);
	};

	void push_back(bool x)
	{
		if (cup == _size)
			resize(2*cup);
		value[_size++] = x;
	};

	bit operator[](size_t i)
	{
		if (i<_size)
		{
			bit res;
			res.value = (value + (i>>3));
				res.pos = i%8;
			return res;
		}
		else
			throw "Out of bounds";
		};


	void resize(size_t new_cup)
	{
		bool* new_value = Alloc.allocate((new_cup>>3) + 1);
		if (_size> new_cup) 
			_size= new_cup;

		for(int i = (_size>>3); i < ( (new_cup>>3) +1); ++i)
			new_value[i] = 0;

		if (value) 
		{
			for(int i = 0; i<_size; ++i)
				new_value[i>>3] = (new_value[i>>3]||(1<<(i%8))) && (value[i>>3] || (~(1<<(i%8))));
			Alloc.deallocate(value,(cup>>3) + 1);
		};
	
		cup = new_cup;
		value = new_value;
	};

	size_t size()
	{
		return _size;
	};
	size_t reserved()
	{
		return cup;
	};
};










void main()
{
	MyVector<bool> v(1,1);
	v.push_back(0);
	std::cout<<v[1];
};