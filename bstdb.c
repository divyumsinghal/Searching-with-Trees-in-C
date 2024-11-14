#include "bstdb.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.

typedef struct Tree_Node
{
	int               doc_id;      // unique identifier for the document
	char              name[50];    // file name of the document
	char              author[50];  // name of the author
	int               word_count;  // number of words in the document
	struct Tree_Node* left;        // pointer to the left node in the bst
	struct Tree_Node* right;       // pointer to the right node in the bst
	struct Tree_Node* parent;      // pointer to the parent node in the bst
} Tree_Node;

int        g_this_id;  // ID of the next document to be added
Tree_Node* g_bst;      // database storage

int bst_num_comps    = 0;
int bst_num_searches = 0;

int size_inserted = 0;
int size_asked    = 0;

int end       = 8388608;
int step_size = 0;

// int		memo[120000] = { 0 };

int bstdb_exist (int doc_id)
{
	// This is a search function. It should traverse the binary
	// search tree and return the name of the node with the
	// corresponding doc_id.
	//
	// If the required node is not found, this function should
	// return NULL or 0 bst_num_searches++;
	Tree_Node* dummy = g_bst;

	while (dummy != NULL)
	{
		// bst_num_comps++;

		if (dummy->doc_id == doc_id)
			return 1;
		else if (dummy->doc_id > doc_id)
			dummy = dummy->left;
		else
			dummy = dummy->right;
	}

	return 0;
}

int bstdb_generate ()
{
again:

	if (g_this_id + step_size >= end)
	{
		step_size /= 2;
		g_this_id = step_size;
	}
	else
	{
		// while
		// (memo[g_this_id]
		// != 0)
		while (bstdb_exist (g_this_id) != 0) g_this_id += step_size;
	}

	if (g_this_id + step_size >= end)
	{
		goto again;
	}

	// memo[g_this_id] = 1;
	return g_this_id;
}

int bstdb_init (void)
{
	// This function will run once (and only once) when the
	// database first starts. Use it to allocate any memory you
	// want to use or initialize some globals if you need to.
	// Function should return 1 if initialization was successful
	// and 0 if something went wrong.

	g_bst = (Tree_Node*) malloc (sizeof (Tree_Node));
	g_bst = NULL;
	step_size = end / 2;

	g_this_id = 0;
	srand (time (0));

	return 1;
}

int bstdb_add (char* name, int word_count, char* author)
{
	// This function should create a new node in the binary
	// search tree, populate it with the name, word_count and
	// author of the arguments and store the result in the tree.
	//
	// This function should also generate and return an
	// identifier that is unique to this document. A user can
	// find the stored data by passing this ID to one of the two
	// search functions below.
	//
	// How you generate this ID is up to you, but it must be an
	// integer. Note that this ID should also form the keys of
	// the nodes in your BST, so try to generate them in a way
	// that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored,
	// this function should return -1. Otherwise it should
	// return the ID of the new node

	size_asked++;

	int doc_id = bstdb_generate ();

	Tree_Node* newNode = (Tree_Node*) malloc (sizeof (Tree_Node));

	if (!newNode) return -1;

	// newNode->name = (char*)malloc(sizeof(name));
	// newNode->author = (char*)malloc(sizeof(author));

	// newNode->name = NULL;
	// newNode->author = NULL;

	newNode->word_count = word_count;
	newNode->doc_id     = doc_id;
	newNode->left       = NULL;
	newNode->right      = NULL;
	newNode->parent     = NULL;

	if (name)
	{
		// printf(newNode->name);
		// printf(name);

		strcpy (newNode->name, name);
	}
	if (author)
	{
		strcpy (newNode->author, author);
	}

	Tree_Node* parent  = NULL;
	Tree_Node* current = g_bst;

	while (current != NULL)
	{
		parent = current;
		if (doc_id < current->doc_id)
			current = current->left;
		else if (doc_id == current->doc_id)
		{
			printf ("%i  ", doc_id);
			return -1;
		}
		else
			current = current->right;
	}

	newNode->parent = parent;

	if (parent == NULL)
		g_bst = newNode;
	else if (doc_id < parent->doc_id)
		parent->left = newNode;
	else
		parent->right = newNode;

	size_inserted++;
	return doc_id;
}

int bstdb_get_word_count (int doc_id)
{
	// This is a search function. It should traverse the binary
	// search tree and return the word_count of the node with
	// the corresponding doc_id.
	//
	// If the required node is not found, this function should
	// return -1
	bst_num_searches++;
	Tree_Node* dummy = g_bst;

	while (dummy != NULL)
	{
		bst_num_comps++;

		if (dummy->doc_id == doc_id)
			return dummy->word_count;
		else if (dummy->doc_id > doc_id)
			dummy = dummy->left;
		else
			dummy = dummy->right;
	}

	return -1;
}

char* bstdb_get_name (int doc_id)
{
	// This is a search function. It should traverse the binary
	// search tree and return the name of the node with the
	// corresponding doc_id.
	//
	// If the required node is not found, this function should
	// return NULL or 0
	bst_num_searches++;
	Tree_Node* dummy = g_bst;

	while (dummy != NULL)
	{
		bst_num_comps++;

		if (dummy->doc_id == doc_id)
			return dummy->name;
		else if (dummy->doc_id > doc_id)
			dummy = dummy->left;
		else
			dummy = dummy->right;
	}

	return 0;
}

void tree_delete (Tree_Node* root)
{
	if (root != NULL)
	{
		tree_delete (root->left);
		tree_delete (root->right);
		free (root);
		root = NULL;
	}
}

void bstdb_quit (void)
{
	// This function will run once (and only once) when the
	// program ends. Use it to free any memory you allocated in
	// the course of operating the database.

	tree_delete (g_bst);
}

int tree_height (Tree_Node* node)
{
	if (node == NULL)
	{
		return 0;
	}
	int left_height  = tree_height (node->left);
	int right_height = tree_height (node->right);
	return (left_height > right_height ? left_height : right_height) + 1;
}

int is_balanced (Tree_Node* node)
{
	if (node == NULL)
	{
		return 1;
	}

	int left_height  = tree_height (node->left);
	int right_height = tree_height (node->right);
	int height_diff  = left_height - right_height;

	return (height_diff >= -30 && height_diff <= 30) && is_balanced (node->left) &&
	       is_balanced (node->right);
}

int count_nodes (Tree_Node* node)
{
	if (node == NULL)
	{
		return 0;
	}
	return count_nodes (node->left) + count_nodes (node->right) + 1;
}

void calculate_avg_depth (Tree_Node* node, int depth, int* total_depth, int* total_nodes)
{
	if (node == NULL)
	{
		return;
	}
	*total_depth += depth;
	(*total_nodes)++;
	calculate_avg_depth (node->left, depth + 1, total_depth, total_nodes);
	calculate_avg_depth (node->right, depth + 1, total_depth, total_nodes);
}

void bstdb_stat (void)
{
	// Use this function to show off! It will be called once
	// after the profiler ends. The profiler checks for
	// execution time and simple errors, but you should use this
	// function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are
	// given below, but in general what you choose to show here
	// is up to you. This function counts for marks so make sure
	// it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number
	//  you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in
	//  order to find
	//    a search result?
	//
	//  + Can you prove that there are no accidental duplicate
	//  document IDs
	//    in the tree?

	printf ("STAT\n");

	int balanced = is_balanced (g_bst);
	printf ("Tree is %sbalanced.\n", balanced ? "well " : "not ");

	int node_count = count_nodes (g_bst);
	printf ("Number of nodes in the tree: %d\n", node_count);

	int total_depth = 0;
	int total_nodes = 0;
	calculate_avg_depth (g_bst, 0, &total_depth, &total_nodes);
	double avg_depth = total_nodes == 0 ? 0 : (double) total_depth / total_nodes;
	printf ("Average depth of the tree: %.2f\n", avg_depth);


	printf ("Avg comparisons per search  -> %lf\n", (double) bst_num_comps / bst_num_searches);
	printf ("List size matches expected? -> %c\n", ((size_inserted == size_asked) ? 'Y' : 'N'));
}

