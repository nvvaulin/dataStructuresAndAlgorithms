#pragma once

template <class T>
struct AVLnode
{ 
	AVLnode<T>* parent;
	AVLnode<T>* left;
	AVLnode<T>* right;
	AVLnode<T>* next;
	AVLnode<T>* prev;
	char height;
	T key;
	
	AVLnode();
	AVLnode(T v, AVLnode<T>* p = 0);
	void take_parents();
	~AVLnode();
};

template <class T>
AVLnode<T>::AVLnode()
{
	parent = left = right = 0;
}

template <class T>
AVLnode<T>::AVLnode(T v, AVLnode<T>* p = 0) 
{
	left = right = 0;
	key = v; 
	parent = p;
};

template <class T>
void AVLnode<T>::take_parents()
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

template <class T>
AVLnode<T>::~AVLnode()
{
	if(left)
		delete left;
	if (right)
		delete right;
};