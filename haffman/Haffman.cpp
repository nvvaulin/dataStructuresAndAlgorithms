#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <fstream>
//#define T int
using namespace std;


///////////////////////////////////////////////////////////////////////////
//
//	struct of file :
//		size_t (4 bytes) - count of symbols
//		size_t (4 bytes) - count of alphabit
//		blocks with symbol ,char (1 byte) - length of code word
//
//////////////////////////////////////////////////////////////////////////
template<class T>
class HaffmanCode
{

	//tree for coding symbols
	struct nodeTree
	{
		bool value;
		size_t occurance;
		nodeTree *parent;
		nodeTree(size_t o) : occurance(o), parent(0) {};
	};
	
	//symbol with link to nodeTree
	struct nodeAlphabit
	{
		T symbol;
		nodeTree* link;
		nodeAlphabit(T s,nodeTree* l) : symbol(s), link(l){};
	};

	//code of the symbol
	struct nodeCode
	{
		vector<bool> code;
		nodeCode(nodeTree* link)//link from the alphabit
		{			
			while (link->parent){
				code.push_back(link->value);
				link = link->parent;
			};
		}
		void write(vector<bool> &v)//write code into v
		{
			for(int i = code.size() - 1; i>=0;--i)
				v.push_back(code[i]);
		}
	};
	//tree for decoding symbol : left = 0; right = 1
	struct readTree
	{
		T* symbol;
		readTree *left,*right;
		readTree()
		{
			left = right = 0;
			symbol = 0;
		};
		
		readTree(vector<bool>::iterator &v, char l, T s)//read code(with length l) of  symbol s
		{
			
			left = right = 0;
			if (!l)//if it reads all code - it is list 
			{			
				symbol = new T(s);
			}
			else//it is link
			{
				symbol = 0;
				read(v,l,s);
			};
		};
		//decode symbol
		T read(vector<bool>::iterator &v)
		{
			if (symbol)
				return *symbol; 
			if (*(v++))
				return right->read(v);
			else
				return left->read(v);
		};
		//read code of symbol
		void read(vector<bool>::iterator &v, char l,T s)//read code(with length l) of  symbol s
		{
			--l;
			if (*(v++))
				if (right)
					right->read(v,l,s);
				else
					right = new readTree(v,l,s);
			else
				if (left)
					left->read(v,l,s);
				else
					left = new readTree(v,l,s);
		};
		~readTree()
		{
			if (left)
				delete left;
			if (right)
				delete right;
			if (symbol)
				delete symbol;
		};
	};
	//compare for queue
	struct comp{
		bool operator()(nodeTree* x1,nodeTree* x2)
		{
			return x1->occurance > x2->occurance;
		};
	};

	//write data block to vector<bool>
	void writeBlock(vector<bool> &v,const void* data,size_t size )
	{
		char* c = (char*)data;
		for(size_t j = 0; j<size; ++j)
		{
			for(int i = 0; i<8;++i)
				v.push_back( *c & (1<<i));
			++c;
		};
	};

	//read data block from vector<bool>
	void readBlock(vector<bool>::iterator &v, void* data, size_t size)
	{
		char* c = (char*)data;
		for(size_t j = 0; j<size; ++j)
		{
			*c = 0;
			for(int i = 0; i<8;++i)
				if (*(v++))
					*c = *c | (1<<i);
				++c;
		};
	};

public:
	//coding
	vector<bool> code(vector<T> &text)
	{
		size_t length = text.size();
		map<T,size_t> symbol;//symbols with their weight  order by symbol

		//init symbols
		for (int i= 0;i<length;++i)
			++(symbol[text[i]]);

		priority_queue<nodeTree*,vector<nodeTree*>, comp> Tree;//symbols with their weight  order by weight
		vector<nodeAlphabit> Alphabit;//symbols whith link to list of tree
		vector<nodeTree*> nodes; //iterator for Tree

		//put weight into queue(Tree), symbols into alphabit and delete map
		map<T,size_t>::iterator iter = symbol.begin();
		while (!symbol.empty())
		{
			iter = symbol.begin();
			nodeTree* node = new nodeTree(iter->second);
			nodes.push_back(node);
			Tree.push(node);
			Alphabit.push_back(nodeAlphabit(iter->first,node));		
			symbol.erase(iter);			
		}
	
		//init Tree	
		while (Tree.size() != 1)
		{
			nodeTree* left  = Tree.top();
			Tree.pop();
			nodeTree* right  = Tree.top();
			Tree.pop();
			nodeTree* node = new nodeTree(left->occurance+right->occurance);
			nodes.push_back(node);
			Tree.push(node);		
			left->parent = node;
			left->value = 0;
			right->parent =  node;
			right->value = 1;
		};

		//create code of alphabit
		map<T,nodeCode> Code;//symbol with code
		for(auto i : Alphabit)
			Code.insert(pair<T,nodeCode>(i.symbol,nodeCode(i.link)));

		//clear not using values
		Alphabit.clear();
		for(auto i : nodes)
			delete i;
		nodes.clear();

		vector<bool> newText;
		//write key
		size_t count = Code.size();
		writeBlock(newText,&length,sizeof(length));
		writeBlock(newText,&count,sizeof(count));

		for(auto i : Code)
		{
			writeBlock(newText,&(i.first),sizeof(i.first));
			char temp = (char)(i.second.code.size());
			writeBlock(newText,&(temp),sizeof(char));
			i.second.write(newText);
		};
		//write text
		for(auto i = 0; i<length;++i)
			Code.find(text[i])->second.write(newText);

		return newText;
	};

	vector<T> decode(vector<bool> Code)
	{
		vector<T> res;
		size_t length;
		size_t lAlphabit;
		vector<bool>::iterator iterCode = Code.begin();
		readBlock(iterCode,&length,sizeof(length));
		readBlock(iterCode,&lAlphabit,sizeof(lAlphabit));
		readTree* Tree = new readTree;
		for(size_t i = 0; i<lAlphabit;++i)
		{
			T symbol;
			readBlock(iterCode,&symbol,sizeof(T));
			char l;
			readBlock(iterCode,&l,sizeof(l));
			Tree->read(iterCode,l,symbol);
		};
		for(size_t i = 0; i < length; ++i)
			res.push_back(Tree->read(iterCode));
		return res;
	};
	
};


void main()
{
	vector<char> v;
	HaffmanCode<char> h;
	std::fstream f("1.txt");
	while(!f.eof())
	{
		char t;
		f>>t;
		v.push_back(t);
	};
	vector<bool> code = h.code(v);
	std::cout<<v.size()<<'\n';
	std::cout<<code.size()/8<<'\n';
	vector<char> decode = h.decode(code);
	for(int i = 0; i<v.size();++i)
	{
		if (decode[i] != v[i])
			std::cout<<"error";
	};
	std::cin>>v[0];
};