## Graph Algorithms

### Prim's Algorithm/Jarnik's Algorithm

Prim's algorithm helps you find the minimum spanning tree(MST) of a graph.

**Conditions**

There must be no cycle. That is, if A links to B and B links to C, C cannot link to A again because that would make a cycle. Edges is also commonly referred to as *cost*. One of the goals of Prim’s algorithm is to get the minimum cost tree that covers the vertices in the graph without leaving any of them behind.

**Keep in mind during the implementation**

* all the vertices of the graph must be included
* the vertex with the minimum weight must be selected first. You’ll also hear some people refer to that weight as distance, but let’s keep calling it weight.
* all the vertices must be connected
* there must be no cycle

Example as starting point **D** is selected:

![Initial Graph](./docs/Prim/start-graph.png)
![Initial Graph](./docs/Prim/first-res.png)
![Initial Graph](./docs/Prim/the-steps.png)
![Initial Graph](./docs/Prim/second-res.png)
![Initial Graph](./docs/Prim/third-res.png)

```
    A --2-- B
   / \     / \
  4   1   3   7
 /     \ /     \
D --2-- C --9-- E
 \     / \     /
  6   8   4   3
   \ /     \ /
    F --1-- G
```

```
    A --2-# B
     ^        
      1        
       \        
D --2-> C      E
         \     ^
          4   3
           v /
    F <-1-- G
```

```
A --2-- B --3-- C
|     / | \   / | 
4   3   1  4 5  7
| /     | /   \ |
D --2-- C --9-- E
|     / |     / |
6   6   8   4   3
| /     | /     |
F --1-- G --7-- H
```
