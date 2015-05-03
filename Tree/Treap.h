#include "BinTree.h"
#include <time.h>
#include <stdio.h>

template<class T>
struct XYnode
{
	T key;
	char y;
	XYnode<T>* right;
	XYnode<T>* left;
	XYnode<T>* parent;

	XYnode()
	{
		parent = left = right = 0;
	};

	XYnode(T k,XYnode<T>* p = 0)
	{
		srand(time(0)*rand());
		y = rand() % 0xFF;
		parent = p;
		right = left = 0;
		key = k;
	};
};


template<class T,class TC = StdComp<T> >
class Treap : public BinTree<T,TC ,XYnode<T> >
{

	void split(XYnode<T>* a,XYnode<T>* &L, XYnode<T>* &R, T k)
	{
		if (!a)
		{
			L = R = 0;
			return ;
		};
		if (compare(k,a->key) <= 0)
		{
			L = a;
			split(a->right,L->right,R,k);
			if (L->right)
				L->right->parent = L;
		}
		else
		{
			R = a;
			split(a->left,L,R->left,k);
			if (R->left)
				R->left->parent = R;
		}
	};

	XYnode<T>*  merge(XYnode<T>* L, XYnode<T>* R)
	{
		if (!L)
			return R;
		if (!R)
			return L;
		if (L->y > R->y)
		{
			L->right = merge(L->right,R);
			if (L->right)
				L->right->parent = L;
			return L;
		}
		else
		{
			R->left = merge(L,R->left);
			if(R->left)
				R->left->parent = R;
			return R;
		};
	}

	void insert(T k)
	{
		XYnode<T>* E = new XYnode<T>(k);
		XYnode<T> *L, *R;
		split(root,L,R,k);
		L = merge(L,E);
		root = merge(L,R);
	};

	XYnode<T>* remove(XYnode<T>* p, T k,XYnode<T>* &res)
	{
		XYnode<T> *L, *R, *M;
		split(p,L,R,k);
		if (L)
			if (compare(L->key,k)==0)
			{
				res = L;
				M = L->right;
				L = L->left;
				L = merge(L,M);
				return merge(L,R);
			};
		res = 0;
		return merge(L,R);
	};
};

