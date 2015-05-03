#include <iostream>



//standart comparator
template<class T>
 class StdComp
 {
 public:
	 int operator()(T a,T b)
	 {
		 if (a>b)
			 return 1;
		 if (a<b)
			 return -1;
		 return 0;
	 };
 };



template <class T,class TC,class node,class Ta = std::allocator<T> >
class BinTree 
{
protected:	
	Ta alloc;
	size_t cup;//capasity
	
	
	TC compare;
	virtual void insert(T k) = 0;
	virtual node* remove(node* p, T k,node* &res) = 0;//return root; res - excluded element	
	node* find(node* p,T k)//find key K in tree p
	{
		if (!p)
			return 0;
		if (compare(k,p->key) > 0)
			return find(p->left,k);
		else if (compare(k,p->key) < 0)
			return find(p->right,k);	
		 else  
			return p;
	};

public:
	node* root;
	size_t max_cup;
	node* frist;
	class Iterator
	{		
	public:
		node* value;
		Iterator(node* p = 0){
			value = p;
		};
		Iterator operator--(int){
			Iterator res = *this;
			--*this;
			return res;
		};
		Iterator& operator++(int){
			Iterator res = *this;
			++*this;
			return res;
		};
		Iterator& operator=(node* p){
			value = p;
			return *this;
		};
		Iterator& operator=(T x){
			value->key = x;
			return *this;
		};
		bool operator==(Iterator& x){
			return x.value == value;
		};
		bool operator!=(Iterator& x){
			return x.value != value;
		};
		operator T(){
			return value->key;
		};

		operator T*(){
			if (value)
			return &(value->key);
			return 0;
		};

		Iterator&  operator--(){
			if (value->parent)
				value = value->parent;
			else{
				value = 0;
				retirn *this;
			};
		};
		Iterator&  operator++(){
			if (value->left)
				value = value->left;
			else 
				if (value->right)
					value = value->right;
				else{
					if (value->parent)
						while (value->parent->left != value)
						{
							value = value->parent;
							if (!value->parent){
								value = 0;
								return *this;
							};
						}
					else{
							value = 0;
							return *this;
						};							
					value = value->right;
				};
			return *this;
		};

		bool operator==(Iterator i){
			return i.value == value;
		};
		
	};
	BinTree(size_t m_cup)
	{
		frist = 0;
		root = 0;
		cup= 0;
		max_cup = m_cup;
	};

	void swap(Iterator x1,Iterator x2)
	{
		if (x1.value->parent->left == x1.value)		 
			x1.value->parent->left = x2.value;
		else
			x1.value->parent->right = x2.value;
		if (x2.value->parent->left == x2.value)		 
			x2.value->parent->left = x1.value;
		else
			x2.value->parent->right = x1.value;

		x1.value->parent->take_parents();
		x2.value->parent->take_parents();
	};

	void push(T k)
	{
		insert(k);
		++cup;
		if (cup > max_cup)
			del(frist->prev->key);
		
			
	};

	Iterator find(T k)
	{
		node* res = find(root,k);
		if (!res)
			return end();
		else
		{
			if (res != frist)
			{
				res->prev->next = res->next;
				res->next->prev = res->prev;						
				res->next = frist;
				res->prev = frist->prev;
				frist->prev->next = res;
				frist->prev = res;
				frist = res;
			};
			return Iterator(res);
		};
	};

	T* pop(T k)
	{
		node* res;
		root = remove(root,k,res);
		
		if (res)
		{
			--cup;
			T* t = new(res->value);
			delete res;
			return t;
		};
		return 0;
	};
	Iterator end(){
		return Iterator(0);
	}
	Iterator begin(){
		return Iterator(root);
	}
	void del(T k)
	{
		node* res;
		root = remove(root,k,res);		
		if (res)
		{
			--cup;
			res->left = 0;
			res->right = 0;
			delete res;
		};
	};

	BinTree<T,TC,node>& operator<<(T k)
	{
		push(k);
		return *this;
	};

	BinTree<T,TC,node>& operator>>(T* &k)
	{
		k = pop(k);
		return *this;
	};

	Iterator operator[](T k){
		return find(k);
	};

	size_t size()
	{
		return cup;
	};
	
};


template <class T,class TC,class node>
std::istream& operator>>(std::istream &s, BinTree<T,TC,node> &t)
{
	T x;
	s>>x;
	t.push(x);
	return s;
};

