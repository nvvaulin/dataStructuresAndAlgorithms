#include "BinTree.h"


template <class T>
struct AVLnode
{ 
	AVLnode<T>* parent;
	AVLnode<T>* left;
	AVLnode<T>* right;
	char height;
	T key;
	
	AVLnode()
	{
		parent = left = right = 0;
	}
	AVLnode(T v, AVLnode<T>* p = 0) {left = right = 0; key = v; parent = p;};
	void take_parents()
	{
		if (left)
			if (left->parent != this)
			{
				left->parent = this;
				left->take_parents();
			};
		if (right)
			if (right->parent != this)
			{
				right->parent = this;
				right->take_parents();
			};
	};
};


template <class T, class TC = StdComp<T> >
class AVLTree : public BinTree<T,TC,AVLnode<T> >
{
	void getHeight(AVLnode<T>* p);
	AVLnode<T>* rRight(AVLnode<T>* p);
	AVLnode<T>* rLeft(AVLnode<T>* q);
	char height(AVLnode<T>* p);
	AVLnode<T>* balance(AVLnode<T>* p);
	int bfactor(AVLnode<T>* p);

	AVLnode<T>* findmin(AVLnode<T>* p) // поиск узла с минимальным ключом в дереве p 
	{
		return p->left?findmin(p->left):p;
	};

	AVLnode<T>* remove(AVLnode<T>* p, T k, AVLnode<T>* &res) // удаление ключа k из дерева p
	{
		if( !p ) return 0;
		if(compare(k,p->key) >= 1)
			p->left = remove(p->left,k,res);
		else if(compare(k,p->key) <= -1)
			p->right = remove(p->right,k,res);	
		 else //  k == p->key 
		{
			AVLnode<T>* q = p->left;
			AVLnode<T>* r = p->right;
			res = p;
			if( !r ) return q;
			AVLnode<T>* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			min->take_parents();
			return balance(min);
		};
		
		return balance(p);
	}

	AVLnode<T>* removemin(AVLnode<T>* p) // удаление узла с минимальным ключом из дерева p
	{
		if( p->left==0 )
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	AVLnode<T>* insert(AVLnode<T>* parent, AVLnode<T>* p, T k) // вставка ключа k
	{
		if( !p ) 
		{ 
			AVLnode<T>* res = new AVLnode<T> (k,parent);
			res->height = 0;
			return res;
			
		};
		if (compare(k,p->key) > 0)
			p->left = insert(p,p->left,k);
		else
			p->right = insert(p,p->right,k);
		return balance(p);
	}

	void insert(T k)
	{
		root = insert(0,root,k);
	};

};

template <class T, class TC>
void AVLTree<T,TC>::getHeight(AVLnode<T>* p)//определяем высоту
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
	int bfactor(AVLnode<T>* p);
};

template <class T, class TC>
AVLnode<T>* AVLTree<T,TC>::rRight(AVLnode<T>* p) // правый поворот
{
	AVLnode<T>* q = p->left;
	p->left = q->right;
	q->right = p;
	getHeight(p);
    getHeight(q);
	return q;
};

template <class T, class TC>
AVLnode<T>* AVLTree<T,TC>::rLeft(AVLnode<T>* q) // левый поворот
{
    AVLnode<T>* p = q->right;	
    q->right = p->left;
	p->left = q;		
    getHeight(q);
    getHeight(p);	
    return p;
};

template <class T, class TC>
char AVLTree<T,TC>::height(AVLnode<T>* p) //высота 0 дерева 0
{
    return p?p->height:0;
};

template <class T, class TC>
int AVLTree<T,TC>::bfactor(AVLnode<T>* p)//берем балас
{
    return height(p->right)-height(p->left);
};

template <class T, class TC>
AVLnode<T>* AVLTree<T,TC>::balance(AVLnode<T>* p)//баласируем
{
    getHeight(p);
    if( bfactor(p)==2 )
    {
		AVLnode<T>* par = p->parent;
        if( bfactor(p->right) < 0 )
		{			
            p->right = rRight(p->right);
			
		};
		p = rLeft(p);
		p->take_parents();
		p->parent = par;
        return p;
    }
    if( bfactor(p)==-2 )
    {
		AVLnode<T>* par = p->parent;
        if( bfactor(p->left) > 0  )
		{		
			p->left = rLeft(p->left);
			
		};
		p = rRight(p);
		p->take_parents();
		p->parent = par;
        return p;
    }
    return p; 
};

