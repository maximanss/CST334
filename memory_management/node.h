/** Name: Max Halbert
    Date: 3/30/2020
    Tilte: node.h
    Description: Header file for node.c
**/


#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;       // node data
    struct node *next;      // pointer to the next node
};

struct node* node_create(int data);

void node_destroy(struct node* node_ptr);

int node_get_data(struct node* node_ptr);

struct node* node_get_nextptr(struct node* node_ptr);

void node_set_nextptr(struct node* current_node, struct node* next_node);