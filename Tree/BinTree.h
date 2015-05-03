#include <iostream>
#include "Iterator.h"


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



template <class T,class TC,class node>
class BinTree 
{
protected:	
	
	size_t cup;//capasity
	node* root;
	TC compare;
	virtual void insert(T k) = 0;// return root
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
	class Iterator
	{
	protected:
		 node* value;
	public:
		Iterator(node* p = 0){
			value = p;
		};
		Iterator& operator--(int){
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
			value->value = x;
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
	BinTree()
	{
		root = 0;
		cup= 0;
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
	};

	Iterator find(T k)
	{
		node* res = find(root,k);
		if (!res)
			return end();
		else
			return Iterator(res);
	};

	T* pop(T k)
	{
		T* temp = 0;
		node* res;
		root = remove(root,k,res);
		
		if (res)
		{
			--cup;
			temp = new(T);
			*temp  = res->key;
			delete res;
		};
		return temp;
	};
	Iterator end(){
		return Iterator(0);
	}
	Iterator begin(){
		return Iterator(root);
	}
	void del(T k)
	{
		pop(k);
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

