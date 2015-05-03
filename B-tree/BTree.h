#pragma once
#include "AVLTree.h"
#include <stdio.h>
#include <memory>
#include <iostream>
#define Tpos size_t
#define node_ptr  shared_ptr<node>
using namespace std;




template<class TK,class TV, class TC = less<TK> >
class BTree
{
public:
	struct T
	{
		TK key;
		Tpos pos;
		T() {};
		T(const TK& k,Tpos p) : pos(p), key(k){};
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
	static const size_t deg = 50;//(64*1024 - 2 - 4 - 2*sizeof(Tpos))/(2*(sizeof(T)+2*sizeof(Tpos)));
	static const size_t length_page = ((8*(64*1024-4))/(8*sizeof(TV)+8*sizeof(TK)+1))/8;
	class node
	{
		node(node&);
	public:				
		bool leaf;
		bool temp;
		T key[2*deg];
		Tpos child[2*deg];	
		Tpos parent;
		Tpos position;
		size_t cup;
		BTree<TK,TV,TC> *tree;
		TC compare;
		node(Tpos pos)
		{
			cup = 0;
			temp = true;
			position = pos;
		};
		node(BTree<TK,TV,TC> *_tree, Tpos pos)
		{
			cup = 0;
			temp = false;
			fseek(_tree->fBTree,sizeof(node)*pos,SEEK_SET);
			fread(this,sizeof(node),1,_tree->fBTree);
			position =  pos;
			tree = _tree;
		};
		node(BTree<TK,TV,TC>* _tree)
		{
			temp = false;
			position = _tree->getnode();
			tree = _tree;
			cup = 0;

		};
		void write()
		{
			fseek(tree->fBTree,sizeof(node)*position,SEEK_SET);
			fwrite(this,sizeof(node),1,tree->fBTree);
			fflush(tree->fBTree);
		};

		~node()
		{
			if (!temp)
			{
				fseek(tree->fBTree,sizeof(node)*position,SEEK_SET);
				fwrite(this,sizeof(node),1,tree->fBTree);
				fflush(tree->fBTree);
			};
		};
	};

	class comp
	{
	public:
		int operator()(const shared_ptr<node> x,const shared_ptr<node> y)const
		{
			if (x->position > y->position)
				return 1;
			if (y->position > x->position)
				return -1;
			return 0;
		};
	};

	char* copy_str(const char* s)
	{
		char* res =(char*)malloc( strlen(s)+1 );
		memcpy(res,s,strlen(s)+1);
		return res;
	};
	AVLTree<shared_ptr<node> ,comp> kash;
	FILE* fBTree;
	FILE* fData;
	FILE* info;
	char* nameT;
	char* nameD;
	char* nameI;
	Tpos posRoot;
	Tpos eod;//end of data
	Tpos eot;//end of tree
	shared_ptr<node> root;
	size_t cup;
	shared_ptr<node> alloc_node(Tpos pos)
	{
		shared_ptr<node> res(new node(this,pos));
		return res;
	};

	shared_ptr<node> alloc_node()
	{
		shared_ptr<node> res(new node(this));
		return res;
	};

	Tpos getnode()
	{
		return eot++;
	};

	
	void split(node_ptr x,int i,node_ptr y)//x->child[i] = y->position
	{
		node_ptr z(new node(this));
		z->leaf = y->leaf;
		z->cup = deg - 1;
		for(size_t j = 0; j < deg - 1; ++j)
			z->key[j] = y->key[deg - 1 + j];
		if (!z->leaf)
			for(size_t j = 0; j < deg; ++j)
				z->child[j] = y->child[deg+j];
		y->cup = deg - 1;
		for(size_t j = x->cup; j < i; --j)
			x->child[j+1] = x->child[j];
		x->child[i] = z->position;
		for(size_t j = x->cup-1; j > i; --j)
			x->key[j+1] = x->key[j];
		x->key[i-1] = y->key[deg-1];
		++x->cup;
		x->write();
		y->write();
		z->write();
	};

	void insert_not_full(node_ptr x,T k)
	{
		int i = x->cup-1;
		if (x->leaf)
		{
			while (i >= 0  && k < x->key[i])//???????????????
			{
				x->key[i+1] = x->key[i];
				--i;
				if (i<0)
					break;
			};
			x->key[++i] = k;
			++x->cup;
			x->write();
		}
		else
		{
			--i;
			while(k < x->key[i--])
				if (i < 0)
					break;
			++i;
			node_ptr c = alloc_node(x->child[i]);
			if ( c->cup == 2*deg - 1)
			{
				split(x,i,c);
				if (k > x->key[i])
					++i;
			};
			insert_not_full(c,k);
		};
	};

	void insert(T k)
	{
		node_ptr r = root;
		if (r->cup == 2*deg - 1)
		{
			root = alloc_node();
			root->leaf = false;
			root->cup = 1;
			root->child[0] = r->position;
			split(root,1,r);
			insert_not_full(r,k);
		}
		else
			insert_not_full(r,k);
	};

	bool search(node_ptr x,T& k)
	{
		size_t i = 0;
		while(i < x->cup && k > x->key[i])
			++i;
		if (i < x->cup)
			if (k==x->key[i])
			{
				k->pos = x->key[i].pos;
				return true;
			};
		if (x->leaf)
			return false;
		else
			return search(alloc_node(x->child[i]),k);
	};

	node_ptr search_max(node_ptr x)
	{
		if (x->leaf)
			return x;
		else
			return search_max(alloc_node(x->child[x->cup-1]));
	};

	node_ptr search_min(node_ptr x)
	{
		if (x->leaf)
			return x;
		else
			return search_max(alloc_node(x->child[0]));
	};

public:

	BTree(const char* data,const char* tree,const char* inf, size_t max_size) : kash(max_size), eot(0)
	{
		cup = 0;
		nameT = copy_str(tree);
		nameD = copy_str(data);
		nameI = copy_str(inf);
		fBTree = fopen(nameT,"w+");
		fData = fopen(nameD,"w+");
		eot = 0;
		eod = 0;
		posRoot= 0;
		root = shared_ptr<node>(new node(this));	
		root->leaf = true;
		kash.push(root);
	};

	BTree(char* inf,size_t max_size) : kash(max_size)
	{
		nameI = copy_str(inf);
		info = fopen(nameI,"r");
		char t[512];
		fread(t,1,512,info);
		nameD = copy_str(t);
		fread(&eod,4,1,info);
		fread(t,1,512,info);
		nameT = copy_str(t);
		fread(&eot,4,1,info);
		fread(&posRoot,4,1,info);
		fread(&cup,4,1,info);
		fclose(info);
		fBTree = fopen(nameT,"r+");
		fData = fopen(nameD,"r+");		
		root = shared_ptr<node>(new node(this,posRoot));
		root->leaf = true;
		kash.push(root);
	};

	~BTree()
	{
		info = fopen(nameI,"w");
		char t[512];
		size_t i;
		memcpy(t,nameD,strlen(nameD)+1);
		fwrite(t,1,512,info);
		fwrite(&eod,4,1,info);
		memcpy(&t,nameT,strlen(nameD)+1);
		fwrite(&t,1,512,info);
		fwrite(&eot,4,1,info);
		fwrite(&root->position,4,1,info);
		fwrite(&cup,4,1,info);
		kash.~AVLTree<shared_ptr<node>,comp>();
		root = 0;
		fclose(info);
		fclose(fBTree);
		fclose(fData);
		kash.root = 0;
		
	};

	void insert(const TK& k,const TV& v)
	{
		insert(T(k,k+1));
		++cup;
	};


	bool find(const TK& k,TV& v)
	{
		T x;
		x.key = k;
		if (search(root,x))
		{
			return true;
		};
		return false;
	};
};
