#include "graph.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
#include <Windows.h>


graph createGraph(size_t n,size_t w,double p)
{
	srand(time(0)*rand());
	graph g(n,p);
	for(size_t a = 0; a+1 < n; ++a)
		for(size_t b = a+1; b < n; ++b)
			if ((size_t)(p*RAND_MAX) >= rand())
				g.insert_edge(a,b,rand() % w);
		return g;
};

void take_one_experiment(bool preflow, size_t n,size_t w,size_t& noPaths, size_t& sumFlow,double p)
{
	int t;
		if(preflow)
			t  = createGraph(n,w,p).preFlow(0,1);
		else
			t = createGraph(n,w,p).ford_falkerson(0,1);
		if (t<0)
			++noPaths;
		else
			sumFlow += t;
};

void take_experements(bool preflow, size_t n,size_t w,size_t& i,size_t& noPaths, size_t& sumFlow,double p, bool& stop)
{
	while(i--)
	{
		if ( ( GetKeyState(VK_LCONTROL) || GetKeyState(VK_RCONTROL) ) && GetKeyState(81) || stop ) // stop if ctrl+q pressed
		{
			stop = true;
			return ;
		};
		take_one_experiment(preflow,n,w,noPaths,sumFlow,p);		
	};
};

// it shows an approximate count of iterations
void take_experements_cout(bool preflow, size_t n,size_t w,size_t& i,size_t& noPaths, size_t& sumFlow,double p,size_t all_iter, bool& stop)
{
	while(i--)
	{
		if ( ( GetKeyState(VK_LCONTROL) || GetKeyState(VK_RCONTROL) ) && GetKeyState(81) || stop ) // stop if ctrl+q pressed
		{
			stop = true;
			return ;
		};
		take_one_experiment(preflow,n,w,noPaths,sumFlow,p);
		std::cout<<"~ "<<all_iter - i*4<<" experiments done\r";
	};
};


int main(int arg,char** argc)
{
	size_t n = 0,w = 0, all_iter;
	size_t iter[4] = {0,0,0,0};
	size_t noPaths[4] = {0,0,0,0};
	size_t sumFlow[4] = {0,0,0,0};
	bool preflow = false;
	double p;
	srand(time(0));	

	for(int i = 1; i < arg; ++i)//argc[0] = path to the application
	{
		switch (argc[i][1])
		{
			case 'i' : all_iter = stoi(argc[++i]);
					iter[0] = iter[1] = iter[2] = all_iter / 4;
					iter[3] = all_iter - (all_iter/4)*3;
					break;
			case 'w' : w = stoi(argc[++i]); break;
			case 'n' : n = stoi(argc[++i]); break;
			case 'p' : p = stof(argc[++i]); break;
			case 'o' : if (argc[++i][0] == 'p') 
					preflow = true;
					break;
			default: std::cout<<"incorrect input"<<endl;
				return 0;
		   
		}
	};

	if(n == 0 || p < 0)
	{
		std::cout<<"incorrect input"<<endl;
		return 1;
	};

	std::cout<<"press ctrl+q to stop the process\n";   

	bool stop = false;//stop the process

#pragma omp parallel sections num_threads(4) shared(stop) 
	{	
	#pragma omp section
		take_experements(preflow,n,w,iter[0],noPaths[0],sumFlow[0],p,stop); 
	#pragma omp section
		take_experements(preflow,n,w,iter[1],noPaths[1],sumFlow[1],p,stop);
	#pragma omp section
		take_experements(preflow,n,w,iter[2],noPaths[2],sumFlow[2],p,stop);
	#pragma omp section
		take_experements_cout(preflow,n,w,iter[3],noPaths[3],sumFlow[3],p,all_iter,stop);
	};

	for(int i = 1; i < 4; ++i)
	{
		iter[0] += iter[i];
		noPaths[0] += noPaths[i];
		sumFlow[0] += sumFlow[i];
	};

	all_iter -= iter[0] + 4;

	std::cout<<all_iter<<" experiments done                            \n";
	std::cout<< "middle flow = " << sumFlow[0] / (all_iter-noPaths[0]);
	std::cout<< "\nnumber of graphs without paths = " << noPaths[0]; 
	return 0;
};