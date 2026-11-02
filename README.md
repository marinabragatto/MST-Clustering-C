# MST-Clustering-C

A C implementation of max-spacing clustering using a minimum spanning tree (MST).

Built for the course Searching and Sorting Techniques (Técnicas de Busca e Ordenação) at UFES.

## How it works

Given a set of points in R^m and a number of clusters k, the program:

1. Computes the Euclidean distance between every pair of points.
2. Sorts the distances and builds the MST with Kruskal's algorithm, using a union-find (disjoint-set) structure.
3. Removes the k - 1 heaviest edges of the MST.
4. Treats each remaining connected component as a cluster and writes the clusters to the output file.

This produces the clustering that maximizes the minimum distance between points in different clusters.

## Complexity

For n points, the complete graph has n(n-1)/2 edges, so:

- Distance computation: O(n^2 m)
- Sorting the edges: O(n^2 log n)
- Kruskal with union-find: close to O(n^2) after sorting
- Memory: O(n^2)

## Build

```
make
```

This produces the `trab1` executable.

## Usage

```
./trab1 <input_file> <k> <output_file>
```

Example:

```
./trab1 input.txt 3 output.txt
```

The program does not read from stdin and prints nothing to the screen.

## Input format

One point per line, with comma-separated fields: a unique identifier followed by the coordinates.

```
A,3.0,7.0
B,1.0,2.0
C,7.0,3.0
D,4.0,7.0
E,1.0,1.0
F,6.0,4.0
G,4.0,6.0
H,2.0,1.0
I,6.0,3.0
J,7.0,4.0
```

## Output format

One cluster per line, with identifiers separated by commas. Identifiers within a cluster are in lexicographic order, and clusters are ordered by their first identifier. For the input above with k = 3:

```
A,D,G
B,E,H
C,F,I,J
```

## Memory check

```
valgrind --leak-check=full ./trab1 input.txt 3 output.txt
```
