#include "RBTree.h"

template <class T,class TC>
void RBTree<T,TC>::rLeft(RBnode<T>* x){
	RBnode<T>* y=x->right;
	x->right=y->left;

	if (y->left!=&(RBnode<T>::nil))
		y->left->parent=x;

	y->parent=x->parent;
	if (x->parent==&(RBnode<T>::nil))
		root=y;
	else
		if (x==x->parent->left)
			y->parent->left=y;
		else
			y->parent->right=y;

	y->left=x;
	x->parent=y;
};

template <class T,class TC>
void RBTree<T,TC>::rRight(RBnode<T>* x){
	RBnode<T>* y=x->left;
	x->left=y->right;

	if (y->right!=&(RBnode<T>::nil))
		y->right->parent=x;

	y->parent=x->parent;
	if (x->parent==&(RBnode<T>::nil))
		root=y;
	else
		if (x==x->parent->left)
			y->parent->left=y;
		else
			y->parent->right=y;

	y->right=x;
	x->parent=y;
}
template <class T,class TC>
void RBTree<T,TC>::insert_fixup(RBnode<T> * z){
    while (z->parent->color==RED)
		if (z->parent==z->parent->parent->left){
			RBnode<T>* y=z->parent->parent->right;
			if (y->color==RED){
				z->parent->color=BLACK;
				y->color=BLACK;
				z->parent->parent->color=RED;
				z=z->parent->parent;
			}
			else {
				if (z==z->parent->right){
					z=z->parent;
					rLeft(z);
				}
				z->parent->color=BLACK;
				z->parent->parent->color=RED;
				rRight(z->parent->parent);
			}
		}
		else {
			RBnode<T>* y=z->parent->parent->left;
			if (y->color==RED){
				z->parent->color=BLACK;
				y->color=BLACK;
				z->parent->parent->color=RED;
				z=z->parent->parent;
			}
			else {
				if (z==z->parent->left){
					z=z->parent;
					rRight(z);
				}
				z->parent->color=BLACK;
				z->parent->parent->color=RED;
				rLeft(z->parent->parent);
			}
		}
    root->color=BLACK;
}

template <class T,class TC>
RBnode<T>* RBTree<T,TC>::min(RBnode<T>* x){
	while(x->left!=&(RBnode<T>::nil))
		x=x->left;
	return x;
};

template <class T,class TC>
RBnode<T>* RBTree<T,TC>::max(RBnode<T>* x){
	while(x->right!=&(RBnode<T>::nil))
		x=x->right;
	return x;
};

template <class T,class TC>
RBnode<T>* RBTree<T,TC>::next(RBnode<T>* x){
	if (x->right!=&(RBnode<T>::nil))
		return min(x->right);
	RBnode<T>* y=x->parent;
	while(y!=&(RBnode<T>::nil) && x==y->right){
		x=y;
		y=y->parent;
    }
    return y;
};

template <class T,class TC>
RBnode<T>* RBTree<T,TC>::prev(RBnode<T>* x){
	if (x->left!=&(RBnode<T>::nil))
		return max(x->right);
	RBnode<T>* y=x->parent;
	while(y!=&(RBnode<T>::nil) && x==y->left){
		x=y;
		y=y->parent;
	}
	return y;
};

template <class T,class TC>
void RBTree<T,TC>::remove_fixup(RBnode<T> * x)
{ 
    while (x!=root && x->color==BLACK){
		if (x==x->parent->left){
			RBnode<T>* w=x->parent->right;
			if (w->color==RED){
				w->color=BLACK;
				x->parent->color=RED;
				rLeft(x->parent);
				w=x->parent->right;
			}
			if (w->left->color==BLACK && w->right->color==BLACK){
				w->color=RED;
				x=x->parent;
			}
			else{
				if (w->right->color==BLACK){
					w->left->color=BLACK;
					w->color=RED;
					rRight(w);
					w=x->parent->right;
				}
				w->color=x->parent->color;
				x->parent->color=BLACK;
				w->right->color=BLACK;
				rLeft(x->parent);
				x=root;
			}
		}
		else{
			RBnode<T>* w=x->parent->left;
			if (w->color==RED){
				w->color=BLACK;
				x->parent->color=RED;
				rRight(x->parent);
				w=x->parent->left;
			}
			if (w->right->color==BLACK && w->left->color==BLACK){
				w->color=RED;
				x=x->parent;
			}
			else{
				if (w->left->color==BLACK){
					w->right->color=BLACK;
					w->color=RED;
					rLeft(w);
					w=x->parent->left;
				}
				w->color=x->parent->color;
				x->parent->color=BLACK;
				w->left->color=BLACK;
				rRight(x->parent);
				x=root;
			}
		}
	}
	x->color=BLACK;
};

template <class T,class TC>
std::istream& operator>>(std::istream &s, RBTree<T,TC> &t)
{
	T x;
	s>>x;
	t.push(x);
	return s;
};




