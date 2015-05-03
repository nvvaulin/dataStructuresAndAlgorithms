#define sizet   unsigned int 


template<class _Ty>
class deque;
	
template<class _Ty>
struct link
{
public:
	link* prev;
	link* next;
	_Ty value;
};
template<class _Ty>
struct deque_first
{
	deque<_Ty>* d;
	deque_first<_Ty> operator>>(_Ty &x);
	deque_first<_Ty> operator<<(_Ty x);
};

template<class _Ty>
struct deque_last
{
	deque<_Ty>* d;
	deque_last<_Ty> operator>>(_Ty &x);
	deque_last<_Ty> operator<<( _Ty x);
};
template<class _Ty>
class deque
{
public:
	deque_first<_Ty> begin;
	deque_last<_Ty> end;
	deque();
	sizet length;
	link<_Ty>* first;
	link<_Ty>* last;
	void push_first(_Ty);
	void push_last(_Ty);
	_Ty get_first();
	_Ty get_last();
};

template<class _Ty>
deque<_Ty>::deque()
{
	begin.d = this;
	end.d = this;
	length = 0;
	first = 0;
	last = 0;
};

template<class _Ty>
void deque<_Ty>::push_first(_Ty t)
{
	++length;
	link<_Ty>* f = first;
	first = new link<_Ty>;
	memcpy(&(first->value),&t,sizeof(t));
	if (length == 1) 
	{
		last = first;
	}
	else
	{
		first->prev = 0;
		first->next = f;
		f->prev = first;
	};
};

template<class _Ty>
void deque<_Ty>::push_last(_Ty t)
{
	++length;
	link<_Ty>* f = last;
	last = new link<_Ty>;
	memcpy(&(last->value),&t,sizeof(t));
	if (length == 1) 
	{
		first = last;
	}
	else
	{
		last->prev = f;
		last->next = 0;
		f->next = last;
	};
};

template<class _Ty>
_Ty deque<_Ty>::get_first()
{
	--length;
	_Ty result = first->value;
	link<_Ty>* f = first;
	first = first->next;
	free(f);
	return result;
};

template<class _Ty>
_Ty deque<_Ty>::get_last()
{
	--length;
	_Ty result = last->value;//????
	link<_Ty>* f = last;
	last = last->prev;
	free(f);
	return result;
};

template<class _Ty>
deque_first<_Ty> deque_first<_Ty>::operator>>(_Ty &x)
	{
		x = d->get_first();
		return *this;
	};

template<class _Ty>
deque_first<_Ty> deque_first<_Ty>::operator<<(_Ty x)
	{
		d->push_first(x);
		return *this;
	};

template<class _Ty>
deque_last<_Ty> deque_last<_Ty>::operator>>(_Ty &x)
	{
		x = d->get_last();
		return *this;
	};

template<class _Ty>
deque_last<_Ty> deque_last<_Ty>::operator<<(_Ty x)
	{
		d->push_last(x);
		return *this;
	};
