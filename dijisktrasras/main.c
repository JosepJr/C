#define MAXVERTICES     6     /* only for this example */
#define MAXLINKS        5     /* only for this example */
#define Minimum(X,Y)    ((X) < (Y)) ? (X) : (Y)
enum StatusType {intree, fringe, unseen} StatusType;

// See the Code Vault for a full implementation of this algorithm

//-------------------------------------------
// ShortestPath()
//
// Find shortest path from node v to
//   node w using Dijkstra's shortest
//   path algorithm.
// Returns total number of units in shortest
//   path
//-------------------------------------------
int ShortestPath(Node AdjacencyList[], int n, int v, int w)
{
	// AdjacencyList -- adjacency list of nodes in graph
	// n -- number of nodes in the graph (6)
	// v -- number of the starting vertex (1..6)
	// w -- number of the destination vertex (1..6)
	int		MinDistance;
	int		ShortestDist[MAXVERTICES];
	int		W[MAXVERTICES];
	int		nextWIdx = 0;
	int		i;
	int		wNode;		// Index of node being considered
	int		tempIdx;	// Temporary use index
	StatusType	status[MAXVERTICES];

	// -------------------- INITIALIZATION SECTION --------------------
	for(i = 0; i < MAXVERTICES; i++)
	{
		W[i] = -1;                   // Init W to empty
		ShortestDist[i] = MAXINT;    // Init shortest dists to infinity
		status[i] = unseen;          // Init all nodes to unseen
	}
	// ------------------------ SETUP SECTION -------------------------
	W[nextWIdx] = v;         // Add first node to W
	nextWIdx++;              // Increment index into W
	ShortestDist[v-1] = 0;   // Set shortest dist from v to v
	status[v-1] = intree;    // Set status of v in W

	// Set shortest distance and status from v to all nodes adjacent to it
	for(i = 0; i < MAXLINKS; i++)
	{
		ShortestDist[AdjacencyList[v-1].links[i].link - 1] =
			AdjacencyList[v-1].links[i].weight;
		status[AdjacencyList[v-1].links[i].link - 1] = fringe;
	}
	// ---------------------- MAIN lOOP SECTION -----------------------
	// Repeatedly enlarge W until it includes all vertices in the graph
	while(nextWIdx < MAXVERTICES)
	{
		// Find the vertex n in V - W at the minimum distance from v
		MinDistance = MAXINT;
		for(i = 0; i < MAXVERTICES; i++)
		{
			if(status[i] == fringe)
			{
				if(ShortestDist[i] < MinDistance)
				{
					MinDistance = ShortestDist[i];
					wNode = i + 1;	// Convert index to node number
				}
			}
		}

		// Add w to W
		W[nextWIdx] = wNode;
		status[wNode - 1] = intree;
		nextWIdx++;

		// Update the shortest distances to vertices in V - W
		for(i = 0; i < MAXLINKS; i++)
		{
			tempIdx = AdjacencyList[wNode -1].links[i].link - 1;
			ShortestDist[tempIdx] = Minimum(ShortestDist[tempIdx],
				ShortestDist[wNode - 1] + AdjacencyList[wNode - 1].links[i].weight);
			status[tempIdx] = fringe;
		}
	} // End while
	return(ShortestDist[w - 1]);
}

