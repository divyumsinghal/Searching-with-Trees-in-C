# Binary Search Tree (BST) Implementation in C

## Introduction

A **Binary Search Tree (BST)** is a tree data structure that is sorted, making data storage, search, and retrieval fast. 
Each node in a BST has at most two children, following these properties:

- The **left child** contains nodes with values **less** than the parent node.
- The **right child** contains nodes with values **greater** than the parent node.

This implementation uses character data and provides fundamental operations for managing a BST.

## Features

- `void tree_insert(Tree_Node** root, char data)` : **Insertion** of elements into the BST.
- `Tree_Node* create_bst(char data[])` : **Creation** of a BST from a character array.
- `Tree_Node* tree_search(Tree_Node* root, char data)` : **Search** for specific elements.
- `void tree_print_sorted(Tree_Node* root)` : **In-order Traversal** for printing elements in sorted order.
- `void tree_delete(Tree_Node* root)` : **Deletion** of nodes, with memory management.


## Example Output

```c
Sorted Tree:
A
C
F
H
I
L
N
O
P
T
U
Found node with data: C
Node with data Z not found.
Tree deleted successfully.
```

## Key Concepts

- **In-Order Traversal**: This traversal method visits nodes in the order of left subtree, root, and right subtree, making it printing sorted elements.
- **BST Properties**: The BST maintains a sorted structure, optimizing search operations with an average time complexity of O(log n).

# Task 2

In this task, I replaced an inefficient linked list-based document database with a Binary Search Tree (BST) for better performance. The document database stores book records and supports efficient querying.

### Features

**Unique Document ID Generation**: 
- Generates unique identifiers for documents using a custom strategy to maintain tree balance.
- This was done in two ways implemented in `bstdb.C` and `bstdb2.C`.
- One if them is faster (~O(1)) but uses more memory (~O(n)) overhead.
- The other one is slower (~O(logn n)) but uses no memeory overhead.


## Node Structure

Each node (`Tree_Node`) in the BST includes:
- `doc_id`: Unique identifier for the document.
- `name`: Title of the book.
- `author`: Author of the book.
- `word_count`: Number of words in the book.
- `left`, `right`: Pointers to child nodes.
- `parent`: Pointer to the parent node (unused).

## Functions

### 1. `bstdb_init()`
- Initializes the BST database. 

### 2. `bstdb_add(char* name, int word_count, char* author)`
- Adds a book to the BST with the specified details. 
- Returns a unique document ID.

### 3. `bstdb_get_word_count(int doc_id)`
- Returns the word count for the book with the given document ID. 

### 4. `bstdb_get_name(int doc_id)`
- Returns the book title for the given document ID. 

### 5. `bstdb_quit()`
- Cleans up the database by freeing all allocated memory.

### 6. `bstdb_stat()`
Displays performance metrics:
- Tree balance status.
- Total nodes and average depth.
- Average comparisons per search.

## Performance and Results

The BST-based implementation was tested with about 100,000 book entries and 10,000 search queries. 
Here are the key performance metrics:

```
Generating 97825 books... OK

Profiling listdb
-------------------------------------------

Total Inserts                :        97825
Num Insert Errors            :            0
Avg Insert Time              :   0.000001 s
Var Insert Time              :   0.000023 s
Total Insert Time            :   0.077609 s

Total Title Searches         :         9782
Num Title Search Errors      :            0
Avg Title Search Time        :   0.002939 s
Var Title Search Time        :   0.013991 s
Total Title Search Time      :  28.749181 s

Total Word Count Searches    :         9782
Num Word Count Search Errors :            0
Avg Word Count Search Time   :   0.002864 s
Var Word Count Search Time   :   0.014191 s
Total Word Count Search Time :  28.022498 s

STAT
Avg comparisons per search  -> 81374.004140
List size matches expected? -> Y

Profiling bstdb
-------------------------------------------

Total Inserts                :        97825
Num Insert Errors            :            0
Avg Insert Time              :   0.000001 s
Var Insert Time              :   0.000002 s
Total Insert Time            :   0.084848 s

Total Title Searches         :         9782
Num Title Search Errors      :            0
Avg Title Search Time        :   0.000001 s
Var Title Search Time        :   0.000000 s
Total Title Search Time      :   0.006861 s

Total Word Count Searches    :         9782
Num Word Count Search Errors :            1
Avg Word Count Search Time   :   0.000000 s
Var Word Count Search Time   :   0.000000 s
Total Word Count Search Time :   0.005597 s

STAT
Tree is well balanced.
Number of nodes in the tree: 97825
Average depth of the tree: 15.83
Avg comparisons per search  -> 15.506696
List size matches expected? -> Y

Profiling bstdb2
-------------------------------------------

Total Inserts                :        97825
Num Insert Errors            :            0
Avg Insert Time              :   0.000001 s
Var Insert Time              :   0.000039 s
Total Insert Time            :   0.092884 s

Total Title Searches         :         9782
Num Title Search Errors      :            0
Avg Title Search Time        :   0.000001 s
Var Title Search Time        :   0.000000 s
Total Title Search Time      :   0.007334 s

Total Word Count Searches    :         9782
Num Word Count Search Errors :            1
Avg Word Count Search Time   :   0.000001 s
Var Word Count Search Time   :   0.000000 s
Total Word Count Search Time :   0.005833 s

STAT
Tree is well balanced.
Number of nodes in the tree: 97825
Average depth of the tree: 15.83
No duplicate document IDs found.
Avg comparisons per search  -> 15.506696
List size matches expected? -> Y
Press Enter to quit...
```


The results demonstrate a significant improvement in search performance with the BST-based implementation.

## Conclusion

- This project highlights the efficiency gains from using a Binary Search Tree (BST) over a linked list for database operations. 
- The BST implementation offers faster search times, making it suitable for handling larger datasets. 
- The results confirmed that the BST-based database was much faster than the linked list version for search operations.
- The results showed that the BST-based database was slower than the linked list version for insertion operations.

