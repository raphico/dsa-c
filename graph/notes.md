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

Bread-first search explores vertices level by level, visiting all neighbors before moving deeper. So we first visit all vertices 1 edge away, then all vertices 2 edges away, and so on. Implemented using a queue. It is used to find the shortest path in an unweighted graph, level-order traversal

**Running time:**
In an adjacency list, BFS visits each vertex and edge once. So the running time is O(V + E)
In an adjacency matrix, you check every possible edge per vertex. So the running time is O(V^2)

## Shortest path

We use BFS to find the shortest path in an unweighted graph, because BFS visits vertices level by level, so BFS explores in order of increasing edges; therefore, when you first see the target, you must have found the minimum number of edges needed to get there

For an unweighted graph, we need a different algorithm that takes those weights into account:

### Dijkstra’s Algorithm

Dijkstra's algorithm is a greedy algorithm that is used to find the shortest path in a weighted graph. It works by repeatedly choosing the vertex with the smallest known distance to the source.

We keep an array of distances to track the best length found so far, and a predecessor array that records which vertices led us to this point. Once the algorithm finish, we reconstruct the shortest path to the target by walking backwards through the predecessor array

For each vertex `v` we visit, we relax its neighbors. That means for each neighbor `u` of `v`:

- we check whether going through `v` will give a smaller distance to `u` than the currently known distance of `u`. So we check if `dist[v] + weight(v, u) < dist[u]`
- If yes, we update the distance of `u` `dist[u] = dist[v] + weight(v, u)`
- We set `v` as the predecessor of `u`

For a example, lets look at a graph with vertices: A, B, C, D. And edges with weights

```mathematica
A → B = 2
A → C = 5
B → C = 1
B → D = 4
C → D = 2
```

Step 0: initialization

| Vertex | Distance from A | Predecessor |
| ------ | --------------- | ----------- |
| A      | 0               | -           |
| B      | ∞               | -           |
| C      | ∞               | -           |
| D      | ∞               | -           |

min-heap: [A]

Step 1: We pick a source A and visit it

- Neighbors of A are B (weight 2) and C (weight 5)
- Relax B: `0 + 2 < ∞` -> update dist[B] = 2, predecessor[B] = A
- Relax C: `0 + 5 < ∞` -> update dist[C] = 5, predecessor[C] = A

| Vertex | Distance from A | Predecessor |
| ------ | --------------- | ----------- |
| A      | 0               | -           |
| B      | 2               | A           |
| C      | 5               | A           |
| D      | ∞               | -           |

min-heap: [B, C]

step 2: visit B

- Neighbors of B are C (weight 1) and D (weight 4)
- Relax C: `2 + 1 < 5 = 3 < 5` -> update dist[C] = 3, predecessor[C] = B
- Relax D: `2 + 4 < ∞` -> update dist[D] = 6, predecessor[D] = B

| Vertex | Distance from A | Predecessor |
| ------ | --------------- | ----------- |
| A      | 0               | -           |
| B      | 2               | A           |
| C      | 3               | B           |
| D      | 6               | B           |

min-heap: [C, D]

step 3: Visit C

- C just has one neighbor D (weight of 2)
- Relax D: `2 + 3 < 6 = 5 < 6` -> update dist[D] = 5, predecessor[D] = C

| Vertex | Distance | Predecessor |
| ------ | -------- | ----------- |
| A      | 0        | -           |
| B      | 2        | A           |
| C      | 3        | B           |
| D      | 5        | C           |

min-heap: [D]

step 4: Visit D

- D has no neighbors
- Algorithm done

shortest part from A -> D: A -> B -> C -> D, distance = 5

In a weighted graph `dist[i]` is the total weight of the shortest path from the source to i. While in an unweighted graph, it is the total number of edges in the shortest path

For unweighted graph, BFS is a better choice, because

- it is simpler to implement (no need for relaxation math and priority queues).
- Run at O(V + E)
- Dijkstra's (with a priority queue) runs in about O((V + E)log V)

## Spanning tree

A spanning tree of a graph is a subgraph that includes all vertices and the minimum number of edges needed to keep the graph connected, which is `V-1` edges (where `V` is the number of vertices). By definition, a spanning tree doesn't contain cycles. A graph can have many different spanning trees. In a weighted graph, the minimum spanning tree (MST) is the spanning tree with the smallest total edge weight

### Intuition

Imagine a map with cities (vertices) and roads (edges), and you want to connect every city without creating loops, and using a few roads as possible. That's a spanning tree

### Prim's algorithm

Prim’s algorithm is a greedy algorithm that builds the minimum spanning tree (MST) by repeatedly choosing the smallest edge that connects a vertex inside the MST to a vertex outside the MST. It grows the MST one vertex at a time.

**Steps:**

1. Start with an arbitrary vertex
2. Pick the smallest weight edge that connects a vertex in the MST to a vertex that is not yet in the MST
3. Add the vertex and edge to the MST
4. repeat until all vertices are included

**Implementation details:**

- uses a priority queue (min-heap) to efficiently get the smallest edge to a new vertex
- The heap stores vertices along with their current best-known connecting edge weight

**Running time:**

- Heap has at most V vertices
- Each edge may update a vertex’s key in the heap, which takes O(log V)
- Total: O(E log V) with adjacency lists and a heap

### Kruskal's algorithm

Kruskal's algorithm is also a greedy algorithm used to build a MST by repeatedly choosing the smallest edge that does not form a cycle. Instead of growing from one vertex, it grows a forest (a set of trees) that eventually becomes a spanning tree

**Steps:**

1. Sort all edges by weight (smallest to largest)
2. Start with each vertex in its own set (disjoint-set / union-find).
3. For each edge in order:
   - If the edge connects two different sets (no cycle), include it in the MST and union the sets.
   - Otherwise, skip it.
4. Stop when you have V – 1 edges in the MST.

**Implementation details:**

- Uses disjoint-set (union-find) to quickly check if two vertices are in the same set.
- Sorting edges dominates the runtime.

**Running time:**

- Sorting edges: O(E log E) ≈ O(E log V) (since E ≤ V²).
- Union-Find operations: nearly O(1) each (with path compression + union by rank).
- Total: O(E log V).
