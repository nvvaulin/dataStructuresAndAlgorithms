#include "BinTree.h"

enum RBColor
{
	RED = true,
	BLACK = false
};

template <class T>
struct RBnode
{
	RBnode<T>*  parent;
	RBnode<T>*  left;
	RBnode<T>*  right;
	static RBnode<T> nil;
	RBColor color;
	T key;
	RBnode()
	{
		parent = left = right = &nil; 
		color = BLACK; 
	}

	RBnode(T v, RBnode<T>* p = &nil) 
	{ 
		left = right = &nil;
		key = v; 
		parent = p; 
		color = BLACK; 
	}	
};

template <class T, class TC = StdComp<T> >
class RBTree : public BinTree<T,TC,RBnode<T> >
{
private:

	void rLeft(RBnode<T> *);
	void rRight(RBnode<T> *);
	void insert_fixup(RBnode<T> *);
	void remove_fixup(RBnode<T> *);
	RBnode<T>* next(RBnode<T>*);
	RBnode<T>* prev(RBnode<T>*);
	RBnode<T>* max(RBnode<T>*);
	RBnode<T>* min(RBnode<T>*);

public:
	
	RBTree() : BinTree() 
	{
		root = &(RBnode<T>::nil);
	};
	
	RBnode<T>* remove(RBnode<T>* p,T k, RBnode<T>* &res)
	{
		res = find(p,k);
		if (!res)
			return p;
		RBnode<T>* z = res;
		RBnode<T>* y;
		RBnode<T>* x;
		if (z->left==&(RBnode<T>::nil) || z->right==&(RBnode<T>::nil))
			y=z;
		else
			y=next(z);
		if (y->left!=&(RBnode<T>::nil))
			x=y->left;
		else
			x=y->right;
		x->parent=y->parent;
		if (y->parent==&(RBnode<T>::nil))
			p=x;
		else
			if (y==y->parent->left)
				y->parent->left=x;
			else
				y->parent->right=x;
		if (y!=z)
		{
			T temp = z->key;
			z->key=y->key;
			y->key = temp;
		};
		if (y->color==BLACK)
			remove_fixup(x);
		res = y;
		return p;
	};

	RBnode<T>* find(RBnode<T>* p,T k)
	{
		if (p == &(RBnode<T>::nil))
			return 0;
		if (compare(k,p->key) == 1)
			return find(p->left,k);
		else if (compare(k,p->key) == -1)
			return find(p->right,k);	
		 else  
			return p;
	};

	void insert(T k)
	{
		RBnode<T>* z=new RBnode<T>(k);
		RBnode<T>* y=&(RBnode<T>::nil);
		RBnode<T>* x=root;
		while (x!=&(RBnode<T>::nil)){
			y=x;
			if (compare(z->key,x->key) < 0)
				x=x->left;
			else
				x=x->right;
		};
		
		z->parent=y;
		if (y==&(RBnode<T>::nil))
			root=z;
		else
			if (compare(z->key , y->key) < 0)
				y->left=z;
			else
				y->right=z;
		z->left=&(RBnode<T>::nil);
		z->right=&(RBnode<T>::nil);
		z->color=RED;
		insert_fixup(z);
		
	}
};

template <class T>
RBnode<T> RBnode<T>::nil = RBnode<T>();

