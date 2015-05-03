

template <class _Ty>
struct list
{
	list();
	list<_Ty>* left;
	list<_Ty>* right;
	list<_Ty>* parent;
	_Ty a;
};

template <class _Ty>
list<_Ty>::list()
{
	left=0;
	right=0;
	parent=0;
};

 template<typename _Ty> 
class tree
{
public:
	
	tree(int (*c)(_Ty x,_Ty y));	
	_Ty* get(_Ty elem);
	void insert(_Ty elem);

private:

	int (* compare)(_Ty elem1,_Ty elem2);//1>2=1 1=2 = 0 1<2 = -1
	list<_Ty> a;
	list<_Ty>* find(_Ty elem);
};

template<typename _Ty> 
tree<_Ty>::tree(int(* c)(_Ty x,_Ty y))
{
	compare = c;
	a.parent = &a;
};

 template<typename _Ty> 
list<_Ty>* tree<_Ty>::find(_Ty elem)
{
	list<_Ty>* i = &a;

	while (i != 0)
	{
		switch (compare(elem,i->a))
		{
			case -1: 
				{
					if (i->right == 0) return i;  
					i = i->right;
					break;
				}
			case 1:  
				{
					if (i->left == 0) return i;   
					i = i->left;
					break;
				};
			case 0: return i;
		};	
	};
};

template<typename _Ty> 
void tree< _Ty >::insert(_Ty elem)
{
	if (a.parent == &a) 
	{
		a.a = elem;
		a.parent = 0;
		a.left = 0;
	    a.right = 0;
		return ;
	};
	
	list<_Ty>* i = find(elem);
	
	switch (compare(elem,i->a))
		{
		case -1: {
					 i->right = new(list<_Ty>);
					 i->right->a = elem;
					 i->right->parent = i;
					 break;
				 };

		case  0: {
					 i->a = elem;
					 break;
				 };

		case  1: {
					 i->left = new(list<_Ty>);
					 i->left->a = elem;
					 i->left->parent = i;
					 break;
				 };
		};

};

 template<typename _Ty> 
_Ty* tree<_Ty>::get(_Ty elem)
{
	list<_Ty>* p = find(elem);

	if (compare(elem,p->a) == 0) 
		{
			return &(p->a);
		}
	else
		return 0;
};
