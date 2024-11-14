#include "bstdb2.h"

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

typedef struct Tree_Node_2
{
	int                 doc_id;      // unique identifier for the document
	char                name[50];    // file name of the document
	char                author[50];  // name of the author
	int                 word_count;  // number of words in the document
	struct Tree_Node_2* left;        // pointer to the left node in the bst
	struct Tree_Node_2* right;       // pointer to the right node in the bst
	struct Tree_Node_2* parent;      // pointer to the parent node in the bst
} Tree_Node_2;

int          g_this_id_2;  // ID of the next document to be added
Tree_Node_2* g_bst_2;      // database storage

int bst_num_comps_2    = 0;
int bst_num_searches_2 = 0;

int size_inserted_2 = 0;
int size_asked_2    = 0;

int end_2       = 8388608;
int step_size_2 = 0;

int memo[8388608] = {0};

int bstdb_exist_2 (int doc_id)
{
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL
	// or 0 bst_num_searches++;
	Tree_Node_2* dummy = g_bst_2;

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

int bstdb_generate_2 ()
{
again:

	if (g_this_id_2 + step_size_2 >= end_2)
	{
		step_size_2 /= 2;
		g_this_id_2 = step_size_2;
	}
	else
	{
		while (memo[g_this_id_2] !=
		       0)  // while (bstdb_exist(g_this_id) != 0)
			g_this_id_2 += step_size_2;
	}

	if (g_this_id_2 + step_size_2 >= end_2)
	{
		goto again;
	}

	memo[g_this_id_2] = 1;
	return g_this_id_2;
}

int bstdb_init_2 (void)
{
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize
	// some globals if you need to. Function should return 1 if
	// initialization was successful and 0 if something went wrong.

	g_bst_2 = (Tree_Node_2*) malloc (sizeof (Tree_Node_2));
	g_bst_2 = NULL;

	g_this_id_2 = 0;
	srand (time (0));
	step_size_2 = end_2 / 2;

	return 1;
}

int bstdb_add_2 (char* name, int word_count, char* author)
{
	// This function should create a new node in the binary search tree,
	// populate it with the name, word_count and author of the arguments and
	// store the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// How you generate this ID is up to you, but it must be an integer.
	// Note that this ID should also form the keys of the nodes in your BST,
	// so try to generate them in a way that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node

	size_asked_2++;

	int doc_id = bstdb_generate_2 ();

	Tree_Node_2* newNode = (Tree_Node_2*) malloc (sizeof (Tree_Node_2));

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

	Tree_Node_2* parent  = NULL;
	Tree_Node_2* current = g_bst_2;

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
		g_bst_2 = newNode;
	else if (doc_id < parent->doc_id)
		parent->left = newNode;
	else
		parent->right = newNode;

	size_inserted_2++;
	return doc_id;
}

int bstdb_get_word_count_2 (int doc_id)
{
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
	bst_num_searches_2++;
	Tree_Node_2* dummy = g_bst_2;

	while (dummy != NULL)
	{
		bst_num_comps_2++;

		if (dummy->doc_id == doc_id)
			return dummy->word_count;
		else if (dummy->doc_id > doc_id)
			dummy = dummy->left;
		else
			dummy = dummy->right;
	}

	return -1;
}

char* bstdb_get_name_2 (int doc_id)
{
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL
	// or 0
	bst_num_searches_2++;
	Tree_Node_2* dummy = g_bst_2;

	while (dummy != NULL)
	{
		bst_num_comps_2++;

		if (dummy->doc_id == doc_id)
			return dummy->name;
		else if (dummy->doc_id > doc_id)
			dummy = dummy->left;
		else
			dummy = dummy->right;
	}

	return 0;
}

void tree_delete_2 (Tree_Node_2* root)
{
	if (root != NULL)
	{
		tree_delete_2 (root->left);
		tree_delete_2 (root->right);
		free (root);
		root = NULL;
	}
}

void bstdb_quit_2 (void)
{
	// This function will run once (and only once) when the program ends.
	// Use it to free any memory you allocated in the course of operating
	// the database.

	tree_delete_2 (g_bst_2);
}

int tree_height_2 (Tree_Node_2* node)
{
	if (node == NULL)
	{
		return 0;
	}
	int left_height  = tree_height_2 (node->left);
	int right_height = tree_height_2 (node->right);
	return (left_height > right_height ? left_height : right_height) + 1;
}

int is_balanced_2 (Tree_Node_2* node)
{
	if (node == NULL)
	{
		return 1;
	}

	int left_height  = tree_height_2 (node->left);
	int right_height = tree_height_2 (node->right);
	int height_diff  = left_height - right_height;

	return (height_diff >= -30 && height_diff <= 30) &&
	       is_balanced_2 (node->left) && is_balanced_2 (node->right);
}

int count_nodes_2 (Tree_Node_2* node)
{
	if (node == NULL)
	{
		return 0;
	}
	return count_nodes_2 (node->left) + count_nodes_2 (node->right) + 1;
}

void calculate_avg_depth_2 (Tree_Node_2* node, int depth, int* total_depth, int* total_nodes)
{
	if (node == NULL)
	{
		return;
	}
	*total_depth += depth;
	(*total_nodes)++;
	calculate_avg_depth_2 (node->left, depth + 1, total_depth, total_nodes);
	calculate_avg_depth_2 (node->right, depth + 1, total_depth, total_nodes);
}

void bstdb_stat_2 (void)
{
	// Use this function to show off! It will be called once after the
	// profiler ends. The profiler checks for execution time and simple
	// errors, but you should use this function to demonstrate your own
	// innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This
	// function counts for marks so make sure it does something interesting
	// or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to
	//  find
	//    a search result?
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?

	printf ("STAT\n");

	int balanced = is_balanced_2 (g_bst_2);
	printf ("Tree is %sbalanced.\n", balanced ? "well " : "not ");

	int node_count = count_nodes_2 (g_bst_2);
	printf ("Number of nodes in the tree: %d\n", node_count);

	int total_depth = 0;
	int total_nodes = 0;
	calculate_avg_depth_2 (g_bst_2, 0, &total_depth, &total_nodes);
	double avg_depth =
	    total_nodes == 0 ? 0 : (double) total_depth / total_nodes;
	printf ("Average depth of the tree: %.2f\n", avg_depth);

	int duplicate_found = 0;
	for (int i = 0; i < 120000 && !duplicate_found; i++)
	{
		if (memo[i] > 1)
		{
			duplicate_found = 1;
			printf ("Duplicate document ID found: %d\n", i);
		}
	}
	if (!duplicate_found)
	{
		printf ("No duplicate document IDs found.\n");
	}

	printf ("Avg comparisons per search  -> %lf\n",
	        (double) bst_num_comps_2 / bst_num_searches_2);
	printf ("List size matches expected? -> %c\n",
	        ((size_inserted_2 == size_asked_2) ? 'Y' : 'N'));
}
