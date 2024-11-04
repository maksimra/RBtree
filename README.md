# RED-BLACK-TREE
## Description
A red-black tree is a type of self-balancing binary search tree that maintains its balance through specific properties associated with the colors of its nodes. Each node in a red-black tree is colored either red or black, and these colors help ensure that the tree remains approximately balanced during insertions and deletions, leading to efficient search operations.
## Key Characteristics
1) **Node Color**: Each node is colored either red or black.
2) **Root Property**: The root node is always black.
3) **Red Property**: Red nodes cannot have red children (i.e., no two consecutive red nodes are allowed).
4) **Black Property**: Every path from a node to its descendant leaves must have the same number of black nodes. This is often referred to as the "black height" of the tree.
5) **Leaf Nodes**: Leaf nodes (NIL) are considered to be black. They serve as sentinels to simplify the tree operations.

***


# PROJECT DESCRIPTION
## Input
- The program receives keys and queries from standard input.
- Each query consists of a pair of keys (two possible values).
- A query is valid only if the second key is greater than the first one; otherwise, the result for that query is zero.
## Output
For each query, the program should count the number of keys in the tree that lie strictly within the left and right boundaries of the query (inclusive).
## Example
### *Input*
```
k 10 k 20 q 8 31 q 6 9 k 30 k 40 q 15 40
```
### *Output*
```
2 0 3
```

***

## Build and Run

1) To compile, type:
```
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
```
```
cmake --build build
```
2) To run the project:

```
build/source/RBtree
```
*Tests*
```
build/tests/tree_tests
```
