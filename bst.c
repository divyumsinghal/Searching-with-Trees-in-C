//
// Created by divyu on 8/11/2024.
//

#include "bst.h"

#include <stdio.h>
#include <stdlib.h>

void tree_insert (Tree_Node** root, char data)
{
	Tree_Node* newNode = (Tree_Node*) malloc (sizeof (Tree_Node));
	newNode->data      = data;
	newNode->left      = NULL;
	newNode->right     = NULL;
	newNode->parent    = NULL;

	Tree_Node* parent  = NULL;
	Tree_Node* current = *root;

	while (current != NULL)
	{
		parent = current;
		if (data < current->data)
			current = current->left;
		else if (data == current->data)
			return;
		else
			current = current->right;
	}

	newNode->parent = parent;

	if (parent == NULL)
		*root = newNode;
	else if (data < parent->data)
		parent->left = newNode;
	else
		parent->right = newNode;
}

Tree_Node* create_bst (char data[])
{
	Tree_Node* root = NULL;

	for (char* i = data; *i != '\0'; i++)
	{
		tree_insert (&root, *i);
	}

	return root;
}

Tree_Node* tree_search (Tree_Node* root, char data)
{
	Tree_Node* dummy = root;

	while (dummy != NULL)
	{
		if (dummy->data == data)
			return dummy;
		else if (dummy->data > data)
			dummy = dummy->left;
		else
			dummy = dummy->right;
	}

	return NULL;
}

void tree_print_sorted (Tree_Node* root)
{
	if (root != NULL)
	{
		tree_print_sorted (root->left);
		printf ("%c\n", root->data);
		tree_print_sorted (root->right);
	}
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
