//#include <boost/test/unit_test.hpp>
//#include "graph.h"
//
//#define BOOST_TEST_MODULE graphTest
//
//bool find_set(set<size_t> x, vector<set<size_t> > v)
//{
//	for(auto i : v)
//		if(i == x)
//			return true;
//	return false;
//};
//
//graph g_fing_sccg()
//{
//	graph g(14);
//	size_t X[] = {1,2,3,2,3,4,8,8,4,6,5,10,12,13,13};
//	size_t Y[] = {2,3,1,5,4,8,4,7,5,7,6,11,13,12,13};
//	
//	for(int i = 0; i<14; ++i)
//		g.insert_edge(X[i],Y[i]);
//	return g;
//};
//
//BOOST_AUTO_TEST_CASE(Test_FIND_CSSG_group_with_two_vertexes_and_more)
//{
//	set<size_t> a,b,c;
//	a.insert(1);
//	a.insert(2);
//	a.insert(3);
//	b.insert(13);
//	b.insert(12);
//	c.insert(4);
//	c.insert(8);
//	graph g = g_fing_sccg();
//	auto v = g.find_sccg();
//	BOOST_CHECK(find_set(a,v) && find_set(b,v) && find_set(c,v));
//};
//
//BOOST_AUTO_TEST_CASE(Test_FIND_CSSG_group_with_one_vertex)
//{
//	set<size_t> a,b,c;
//	a.insert(7);
//	b.insert(10);	
//	c.insert(9);
//	graph g = g_fing_sccg();
//	auto v = g.find_sccg();
//	BOOST_CHECK(find_set(a,v) && find_set(b,v) && find_set(c,v));
//};
//
