#include <iostream>
#include <vector> 
#include <stack>
#include <set>
#include <cstring>
#include <algorithm>
using namespace std;

struct Edge
{
	int endPoint1;
	int endPoint2;

	Edge( int node1 = 0, int node2 = 0 )
	{
		endPoint1 = node1;
		endPoint2 = node2;
	}

	int operator!=( Edge right )
	{
		return ( endPoint1 != right.endPoint1 || endPoint2 != right.endPoint2 );
	}
};

const int N = 50005;
int d[ N ];
int low[ N ];
int parent[ N ];            // parent[ u ] is the parent if u
int numChildren;            // the number of children of the root, i.e., node 1
int dfsTime;
int numBcc;                 // the total number of biconnected components of the given graph
bool isCutPoint[ N ];       // isCutPoint[ u ] is true iff node u is a cut point
vector< int > adjList[ N ]; // the adjacency list of the given graph
set< int > bcc[ N ];        // bcc[ i ] contains all nodes in i-th biconnected component
stack< Edge > edgeStack;    // a stack of edges
long long miniNumber;       // the minimum number of escape shafts
long long numWays;          // the total number of ways in which
							// miniNumber escape shafts can be installed

// implement Tarjan's biconnected component algorithm
// put all nodes in i-th biconnected component into bcc[ i ]
void tarjanBCC( int u )
{
	dfsTime = dfsTime + 1;
	d[ u ] = dfsTime;
	low[ u ] = dfsTime;
	for( auto&v : adjList[ u ] ) {
		if( d[ v ] == 0 ) {
			parent[ v ] = u;
			edgeStack.push(Edge(u, v));
			if (parent[u] == 0)  
				++numChildren;
			tarjanBCC( v );
			low[ u ] = min( low[ u ], low[ v ] );
			if( low[ v ] >= d[ u ] ) {
				//start new component
				Edge buffer;
				if (u != 1)
					isCutPoint[u] = true;
				++numBcc;
				do {
					buffer = edgeStack.top();
					edgeStack.pop();
					bcc[numBcc].insert(buffer.endPoint1);
					bcc[numBcc].insert(buffer.endPoint2);
					
				} while(buffer != Edge(u, v));

			}
			else if( d[ v ] < d[ u ] && v != parent[ u ] ) {
				edgeStack.push(Edge(u, v));
				low[ u ] = min( low[ u ], d[ v ] );
			}
		}
	}
}

// computes miniNumber and numWays
void solve()
{
	int count, nodeCount = -1;
	miniNumber = 0;
	numWays = 1;
	bool cut = false;

	for( int i = 0; i < numBcc; i++ ) {
		/*if( !isCutPoint[ i ] )
			miniNumber = isCutPoint[ i ];*/  //delete
		count = 0;
		for (int s : bcc[i]) {
			if (isCutPoint[s])
				++count;
			nodeCount = max(nodeCount, s);
		}
		if (count == 1) {
			cut = true;
			numWays *= (bcc[i].size() - 1);
			++miniNumber;
		}
	}
	if (!cut) {
		miniNumber = 2;
		numWays = ((long long)nodeCount * (nodeCount - 1) / 2);
	}
}

int main()
{
	int numCases = 0;
	int N;
	cin >> N;
	while( N != 0 )
	{
		int s, t, maxNodeID = 0;
		for( int i = 0; i < N; i++ )
		{
			cin >> s >> t;
			adjList[ s ].push_back( t );
			adjList[ t ].push_back( s );
			maxNodeID = max( maxNodeID, s );
			maxNodeID = max( maxNodeID, t );
		}

		memset( d, 0, sizeof( d ) );
		memset( parent, 0, sizeof( parent ) );
		memset( isCutPoint, false, sizeof( isCutPoint ) );
		dfsTime = numBcc = 0;
		numChildren = 0;
		tarjanBCC( 1 ); // put all nodes in i-th biconnected component into bcc[ i ]

		if( numChildren > 1 )
			isCutPoint[ 1 ] = true;

		solve(); // computes miniNumber and numWays

		cout << "Case " << ++numCases << ": " << miniNumber << " " << numWays << "\n";

		for( int i = 1; i <= maxNodeID; i++ )
			adjList[ i ].clear();

		for( int i = 1; i <= numBcc; i++ )
			bcc[ i ].clear();

		cin >> N;
	}

	system( "pause" );
}