#ifndef __BFS_H__
#define __BFS_H__

#include <iostream>
#include <list>
#include <vector>
#include <queue>

using namespace std;

class BFS
{
	public:
		BFS();
		~BFS();
		void execute(vector< list<int> > adj_list, int source, int target);
		void test();
};

#endif

