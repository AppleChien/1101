#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxNumNodes = 2005;
vector< int > adjList[ maxNumNodes ]; // the adjacency list of the given graph
int d[ maxNumNodes ];
int low[ maxNumNodes ];
int dfsTime;
stack< int > nodeStack;      // a stack of nodes
bool inStack[ maxNumNodes ]; // inStack[ u ] is true if and only if node u is in nodeStack
int numSCCs;                 // the numbers of strongly connected components of the given graph

// implement Tarjan's strongly component algorithm
// compute numSCCs
void tarjanSCC( int u )
{
	dfsTime = dfsTime + 1;
	d[ u ] = dfsTime;
	low[ u ] = dfsTime;
	nodeStack.push( u );
	inStack[u] = true;
	for( auto&v : adjList[ u ] ) {
		if( d[ v ] == 0 ) {
			tarjanSCC( v );
			low[ u ] = min( low[ u ], low[ v ] );
			
		}
		else if( inStack[ v ] ) {
			low[ u ] = min( low[ u ], d[ v ] );
		}
	}

	if (low[u] == d[u]) {
		//start a new component
		numSCCs++;
		int a;
		do {
			a = nodeStack.top();
			nodeStack.pop();
			inStack[a] = false;
		} while (a != u);
	}
}

void restart(int u)
{
	for (int i = 1; i <= u; i++)
	{
		d[i] = 0;
		low[i] = 0;
		inStack[i] = false;
	}

	while (!nodeStack.empty())
	{
		nodeStack.pop();
	}

	dfsTime = 0;
	numSCCs = 0;
}


int main() {
	int node, edge;
	int n1, n2;
	cin >> node >> edge;


	while( node != 0 && edge != 0 ) {

		restart(node);
		for (int h = 1; h <= node; h++)
		{
			adjList[h].clear();
		}

		for( int i = 0; i < edge; i++ )
		{
			cin >> n1 >> n2 >> numSCCs;
			if( numSCCs == 1 ) {
				adjList[ n1 ].push_back( n2 );
			}
			else if( numSCCs == 2 ) {
				adjList[ n1 ].push_back( n2 );
				adjList[ n2 ].push_back( n1 );
			}
		}


		dfsTime = 0;

		bool judge = true;
		for (int k = 1; k <= node; k++)
		{
			tarjanSCC(k);
			if (numSCCs > 1)
			{
				judge = false;
				break;
			}
			restart(node);
		}

		if (judge)
		{
			numSCCs = 0;
			for (int l = 1; l <= node; l++)
			{
				if (!d[l])
				{
					tarjanSCC(l);
				}
			}

			if (numSCCs > 1) 
				judge = false;
		}

		if( judge)cout << "1";
		else cout << "0";

	}
	system( "pause" );
}