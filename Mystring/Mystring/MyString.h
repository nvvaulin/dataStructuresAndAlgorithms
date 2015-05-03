#include <vector>

using namespace std;

template <class T>
class myString :protected vector<T>
{
	T end;
public:
	myString(T _end)
	{
		end = _end;
	};
	
	size_t length() const
	{
		return this->size() - 1;
	};

	myString<T> operator+(const myString<T>& s) const
	{
		myString<T> res(end);
		res = *this;
		res.pop_back();
		for(size_t i = 0; i<s.size(); ++i)
			res.push_back(s[i]);
		return res;
	};

	void operator+=(const myString<T>& s)
	{
		this->pop_back();
		for( int i = 0; i<s.size(); ++i)
			res.push_back(s[i]);
	};

	myString<T> operator+(const T& s) const
	{
		myString res(end);
		res = *this;
		res.pop_back();
		res.push_back(s);
		res.push_back(end);
		return res;
	};

	void operator+=(const T& s)
	{
		this->pop_back();
		res.push_back(s);
		res.push_back(end);
	};

	bool operator>(const myString<T>& s) const
	{
		size_i i = 0;
		for (size_t i = 0;i < this->length();++i)
			if (s.length() == i)
				return true;
			else
				if (s[i] > *this[i])
					return false;
		return false;
	};

	bool operator>(const T& s) const
	{
		if (!(this->length())&&(s != end)) return false;
		if (*this[0] > s)	return true;
		return false;
	};

	bool operator<(const myString<T>& s) const
	{
		return s > *this;
	};

	bool operator<(const T& s) const
	{
		if (!(this->length())&&(s != end)) return true;
		if (*this[0] < s)	return true;
		return false;
	};
	bool operator==(const myString<T>& s) const
	{
		if ((*(vector<T>*)(this) ==  (vector<T>)(s)) && (this->end == s.end))
			return true;
	};

	myString<T>& operator=(const myString<T> s)
	{
		*(vector<T>*)(this) =  (vector<T>)(s);
		this->end = s.end;
		return *this;
	};

	myString<T>& operator=(const T* s)
	{
		this->clear();
		if (*s == 0)	return *this;
		
		do
		this->push_back(*s);
		while (*(++s) != end);
		return *this;
	};

	T& operator[](const size_t s) const
	{
		if (s < this->length()) return (*((vector<T>*)this))[s];
		T _end = end;
		return _end;
	};

	T& operator[](const size_t s)
	{
		if (s < this->length()) return (*((vector<T>*)this))[s];
		T _end = end;
		return _end;
	};


	int pos(const myString<T>& s)
	{
		size_t i = 0;
		while (i < this->length() - s.lenght())
		{
			size_t j = 0;
			while (j < s.length())
				if (s[j] != *this[i+j])
					continue ;
			return i;
		};
		return -1;
	};

	int pos(const T& s)
	{
		size_t i = 0;
		while (i < this->length() - s.length())
		{
			if (s[i] == *this[i])				
			return i;
		};
		return -1;
	};

	myString<T> subString(size_t _begin, size_t _end)
	{
		myString<T> res(end);
		for(int i = _begin; (i < _end)&&(i < this->length()); ++i)
			res.push_back(*this[i]);
		res.push_back(end);
	};

	void insert(const myString<T>& s, size_t pos)
	{
		*this = this->subString(0,pos) + s + this->subString(pos,this->size());
	};

	void del(size_t _begin, size_t _end)
	{
		*this = this->subString(0,_begin) + subString(_end,this->length());
	};

};
