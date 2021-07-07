/** Name: Max Halbert
    Date: 3/30/2020
    Tilte: node.c
    Description: Create and Destroy node
**/

#include "node.h"

// Function to create a new node
struct node* node_create(int data)
{
    // allocate memory for the new node
    struct node* newnode = (struct node*) malloc(sizeof(struct node)); 
    newnode->data = data;   // store data to the new node
    newnode->next = NULL;   // initialize pointer to next node to NULL
    return newnode;
}

// Function to destroy the node
void node_destroy(struct node* node_ptr)
{
    free(node_ptr);
}

// Function to return the data in the node
int node_get_data(struct node* node_ptr)
{
    return node_ptr->data;
}

// Function to return the pointer to next node
struct node* node_get_nextptr(struct node* node_ptr)
{
    return node_ptr->next;
}

// Function to set the next node pointer
void node_set_nextptr(struct node* current_node, struct node* next_node)
{
    current_node->next = next_node;
}


