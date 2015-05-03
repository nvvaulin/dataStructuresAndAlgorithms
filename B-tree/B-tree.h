#pragma once
#include "binary.h"
#include "file.h"

template<class TK,class TV, class TC = less<TK> >
class BTree
{
public:
	struct T
	{
		TK key;
		TV value;
		T() {};
		T(const TK& k,TV v) : value(v), key(k){};
		bool operator<(const T x) const
		{
			return TC()(this->key,x.key);
		};
		bool operator>(const T& x)const
		{
			return TC()(x.key,this->key);
		};
		bool operator==(const T& x)const
		{
			TC c;
			return !(c(this->key,x.key) || c(x.key,this->key));
		};
	};
	static const size_t deg = ((64*1024 - 6 - sizeof(Tpos))) / (2*(8*(sizeof(T) + sizeof(Tpos))+1)) - 1;
	class node
	{
	public:	
		size_t cap;			
		bool leaf;
		T key[2*deg+2];
		char del[(2*deg+2)/8+1];
		Tpos child[2*deg+2];	
		Tpos position;
		bool operator<(node& n){
			return position < n.position;
		};
		bool operator>(node& n){
			return n < *this;
		};
		bool operator==(node& n)
		{
			return position == n.position;
		};
		node()
		{
			for (size_t i = 0; i< (2*deg+2)/8+1; ++i)
				del[i] = 0;
			cap = 0;
		};

	};

	char* copy_str(const char* s)
	{
		char* res =(char*)malloc( strlen(s)+1 );
		memcpy(res,s,strlen(s)+1);
		return res;
	};
	File<node> fBTree;
	AVLTree<node> kash;
	fstream info;
	char* nameT;
	char* nameI;
	Tpos posRoot;
	Tpos eot;//end of tree
	node root;
	size_t cap;
	size_t deleted;
	void alloc_node(node& n)
	{
		fBTree.insert(n,eot);
		n.position = getnode();
		if (kash.size() == kash.max_cup)
				fBTree.insert(kash.frist->prev->key,kash.frist->prev->key.position);
		kash.push(n);
		n.cap = 0;
	};

	void alloc_node(node& n,Tpos pos)
	{
		n.position =  pos;
		node* t = kash.find(n);
		if (t)
		{
			n = *t;
			if(n.position != pos)
				cout<<'e';
		}
		else
		{
			n = fBTree[pos];
			n.position =  pos;
			if (kash.size() == kash.max_cup)
				fBTree.insert(kash.frist->prev->key,kash.frist->prev->key.position);
			kash.push(n);
		};
	};

	void write(node& n){
		AVLTree<node>::Iterator  t = kash.find(n);
		if (t != kash.end() ){
			t = n;
		}
		else
			fBTree.insert(n,n.position);	
	};

	Tpos getnode(){
		return eot++;
	};

	
	void split(node& x,int i,node& y)//x.child[i] = y.position
	{
		node z;
		alloc_node(z);
		z.leaf = y.leaf;
		z.cap = deg - 1;
		for(size_t j = 1; j <= deg - 1; ++j)
			z.key[j] = y.key[deg + j];
		if (!y.leaf)
			for(size_t j = 1; j <= deg; ++j)
				z.child[j] = y.child[deg + j];
		y.cap = deg - 1;
		for(size_t j = x.cap+1; j >= i+1; --j)
			x.child[j+1] = x.child[j];
		x.child[i+1] = z.position;
		for(size_t j = x.cap; j >= i; --j)
			x.key[j+1] = x.key[j];
		x.key[i] = y.key[deg];
		++x.cap;
		write(x);
		write(y);
		write(z);
	};

	void insert_not_full(node& x,T k)
	{
		int i = x.cap;
		if (x.leaf)
		{
			while (i >= 1  && k < x.key[i])
			{
				x.key[i+1] = x.key[i];
				--i;
			};
			x.key[++i] = k;
			++x.cap;
			write(x);
		}
		else
		{
			while( i >= 1 && k < x.key[i])
				--i;
			++i;
			node c;
			alloc_node(c,x.child[i]);
			if ( c.cap == 2*deg - 1)
			{
				split(x,i,c);
				if (k > x.key[i])
					++i;
			};
			alloc_node(c,x.child[i]);
			insert_not_full(c,k);
		};
	};

	bool del(node& x,T& k)
	{
		size_t i = 1;
		while(i <= x.cap && k > x.key[i])
			++i;
		if (i <= x.cap)
			if (k==x.key[i])
			{
				k.value = x.key[i].value;
				x.del[i<<3] &= 255 - (1<<(i%8));
				deleted++;
				if (2*deleted > cap)
					rebuild();
				return true;
			};
		if (x.leaf)
			return false;
		else
		{
			node t;
			alloc_node(t,x.child[i]);
			return search(t,k);
		};
	};

	void insert(T k)
	{
		if (root.cap == 2*deg - 1)
		{
			node r = root;
			alloc_node(root);
			root.leaf = false;
			root.cap = 0;
			root.child[1] = r.position;
			split(root,1,r);
			insert_not_full(r,k);
		}
		else
			insert_not_full(root,k);
	};

	bool search(node& x,T& k)
	{
		size_t i = 1;
		while(i <= x.cap && k > x.key[i])
			++i;
		if (i <= x.cap)
			if (k==x.key[i])
			{
				k.value = x.key[i].value;
				return true;
			};
		if (x.leaf)
			return false;
		else
		{
			node t;
			alloc_node(t,x.child[i]);
			return search(t,k);
		};
	};

public:

	BTree(char* tree, char* inf,size_t buf_size) : fBTree(tree), kash(buf_size/sizeof(node) + 2)
	{
		deleted = 0;
		cap = 0;
		nameI = copy_str(inf);
		nameT = copy_str(tree);
		eot = 0;
		posRoot= 0;
		root.cap = 0;
		root.leaf = true;
		alloc_node(root);
		write(root);
	
	};

	~BTree()
	{
		info.open(nameI,std::fstream::in);
		char t[512];
		info<<nameT;
		info<<eot;
		info<<root.position;
		info<<cap;
		info<<deleted;
		write(root);
		info.close();	
		AVLnode<node>* p = kash.frist;
		do
		{
			fBTree.insert(p->key,(p->key).position);
			p = p->next;
		}while (p != kash.frist);
	};

	void insert(const TK& k,const TV& v)
	{
		insert(T(k,v));
		++cap;
		//write(root);
	};
		
	bool del(TK& k,TV& v )
	{
		bool res;
		T t(k,v);
		res = del(root,t);
		v = t.value;
		return res;
	};

	bool find(const TK& k,TV& v)
	{
		T x;
		x.key = k;
		if (search(root,x))
		{
			v = x.value;
			return true;
		};
		return false;
	};
	void rebuild()
	{
		fBTree.close();
		info.close();
		rename(nameT,"temp.btree");
		rename(nameI,"temp.inf");
		File tempf("temp.btree");
		if (1)
		{
			BTree<TK,TV,TC> tempt(nameI);
			node n;
			for(Tpos i = 0; i<eot; ++i)
			{
				n = tempf[i];
				for(size_t j = 0; j < n.cap;++j)
					if (! (n.del[j<<3] & (255 - (1<<(j%8))) ) )
						tempt.insert(n.key[i].key,n.key[i].value);
			};
			cap = tempt.cap;
			posRoot = tempt.posRoot;
			root = tempt.root;
			eot = tempt.eot;
		};
		fBTree.open();
	};
	size_t size(){
		return cap;
	};

};

	