//
// Created by divyu on 8/11/2024.
//

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int main ()
{
	char       data[] = "FLOCCINAUCINIHILIPILIFICATION";
	Tree_Node* root   = create_bst (data);

	tree_insert (&root, 'Q');
	tree_insert (&root, 'N');

	printf ("Sorted Tree: \n");
	tree_print_sorted (root);

	char       searchKey = 'C';
	Tree_Node* result    = tree_search (root, searchKey);

	if (result != NULL)
	{
		printf ("Found node with data: %c\n", result->data);
	}
	else
	{
		printf ("Node with data %c not found.\n", searchKey);
	}

	searchKey = 'Z';
	result    = tree_search (root, searchKey);

	if (result != NULL)
	{
		printf ("Found node with data: %c\n", result->data);
	}
	else
	{
		printf ("Node with data %c not found.\n", searchKey);
	}

	tree_delete (root);
	printf ("Tree deleted successfully.\n");

	return 0;
}
