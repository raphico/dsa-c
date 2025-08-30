# Graph

A graph is a data structure used to model relationships. It consists of two things:

1. Vertices (or nodes): "points" in the graph
2. Edges: "connections" between those points

For example:

1. In a social network, each person is a vertex, and an edge represents a follow
2. On map, cities are vertices, and roads are edges
3. On the web, websites are vertices, and hyperlinks are edges

Graphs can be:

- Directed (edges have a direction)
- Undirected (edges go both ways)
- Weighted (edges carry a value, like road distances)
- Unweighted (edges are just connections)

## Key concepts:

1. Vertex: a point in a graph
2. Edge: a connection between two vertices
3. Adjacent: two vertices are adjacent if there is an edge directly connecting them
4. Degree: the number of edges connected to a vertex
   In a directed graph:
   - In-degree = number of incoming edges
   - Out-degree = number of outgoing edges
5. Path: a sequence of vertices connected by edges
6. Cycle: a path that starts and ends at the same vertex, without repeating edges/vertices in between
7. Acyclic: a graph that has no cycle
8. Connected graph: every vertex can reach every other vertex
9. Subgraph: a smaller graph formed from part of a larger one
10. Weighted edge: an edge that has a cost or value attached
11. Graph traversal: the process of visiting all vertices in a certain order
12. Dag: directed, acyclic graph

## Graph representations

There are different ways of representing graphs in a computer:

### Adjacency Matrix

An adjacency matrix is a way of representing a graph using a 2D array of size n x n, where n is the number of vertices. Each entry (i, j) indicates whether there is an edge between vertex i and vertex j. So matrix[i][j] = 1 (or weight) if there's an edge from vertex i to vertex j, otherwise 0

**Pros:**

- O(1) edge lookup
- Easy to implement

**Cons:**

- Requires O(v^2) memory
- Adding/removing vertices is expensive, because it requires resizing the array
- iterating over the neighbors of a vertex takes O(n) time

So in practice, we use an adjacency matrix for faster edge lookups or when the graph is dense (it has close to the maximum number of possible edges)

### Adjacency List

An adjacency list is a way of representing a graph where each vertex stores a list of its neighbors (vertices directly connected to it)

**Pros:**

- uses O(v + E) memory, where v is the number of vertices and E is the number of edges
- Easy to iterate over neighbors of a vertex
- Adding/removing is straightforward

**Cons:**

- slower edge lookup: O(degree) time
- more complex to implement that adjacency matrix

In practice, we use adjacency lists for sparse graph (the number of edges is much smaller than the maximum possible)

### Edge List

An edge list is a way of representing a graph by storing all edges as pairs (or triples if weighted)

## Searching/Traversing a Graph

There are two main algorithms used to search or traverse a graph:

### Depth-First Search

Depth-first search explores as far as possible along a path before backtracking. Implemented using a stack, either an explicit one or through recursion. It is useful for detecting cycles

**Running time:**
In an adjacency list, DFS visits each vertex and edge once. So the running time is O(V + E)
In an adjacency matrix, you check every possible edge per vertex. So the running time is O(V^2)

### Breadth-First Search

Bread-first search explores vertices level by level, visiting all neighbors before moving deeper. Implemented using a queue. It is used to find the shortest path in an unweighted graph, level-order traversal

**Running time:**
In an adjacency list, BFS visits each vertex and edge once. So the running time is O(V + E)
In an adjacency matrix, you check every possible edge per vertex. So the running time is O(V^2)
