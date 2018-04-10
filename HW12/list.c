/**
 * CS 2110 - Spring 2014 - Homework #12
 * Edited by: Brandon Whitehead, Andrew Wilder
 *
 * list.c: Complete the functions!
 * Author: Yuen Han CHan(Sylvia)
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

typedef unsigned short u16;

/* The node struct.  Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO*/
/* Design consideration only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION DO NOT PUT IT IN OTHER FILES */
typedef struct lnode
{
  struct lnode* prev; /* Pointer to previous node */
  struct lnode* next; /* Pointer to next node */
  void* data; /* User data */
} node;


/* Do not create any global variables here. Your linked list library should obviously work for multiple linked lists */
// This function is declared as static since you should only be calling this inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
  node* newNode = (node*)malloc(sizeof(node));
  if(newNode==NULL){
    printf("There're not enough memories to create a new Node");
    return NULL;
  }
  newNode->data = data;
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head/tail to NULL.
  *
  * @return an empty linked list
  */
list* create_list(void)
{
  list* newList = (list*)malloc(sizeof(list));
  newList->head = NULL;
  newList->tail = NULL;
  newList->size = 0;
    return newList;
}

/** push_front
  *
  * Adds the data to the front of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list* llist, void* data)
{
  node* newNode = create_node(data);
  if(newNode==NULL){
    printf("Not enought memories to allocate new Node");
    return;
  }
  if(llist->size==0){
    llist->head = newNode;
    llist->tail = newNode;
  }
  else{
    newNode->next = llist->head;
    llist->head->prev = newNode;
  }
  llist->head = newNode;
  llist->size++;
}

/** push_back
  *
  * Adds the data to the back/end of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_back(list* llist, void* data)
{
  node* newNode = create_node(data);
  if(newNode==NULL){
    printf("Not enought memories to allocate new Node");
    return;
  }
  if(llist->size==0){
    llist->head = newNode;
  }
  else{
    newNode->prev = llist->tail;
    llist->tail->next = newNode;
  }
  llist->tail = newNode;    
  llist->size++;
}
/** front
  *
  * Gets the data at the front of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the linked list or NULL.
  */
void* front(list* llist)
{
  if(llist->size==0){
    return NULL;
  }
  return llist->head->data;
    /// @todo Implement changing the return value!
    /// @note you are returning the HEAD's DATA not the head node. Remember the user should never deal with the linked list nodes.
}

/** back
  *
  * Gets the data at the "end" of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the last node in the linked list or NULL.
  */
void* back(list* llist)
{
  if(llist->size==0){
    return NULL;
  }
  return llist->tail->data;
}

/** remove_front
  *
  * Removes the node at the front of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed (which is only there are no elements) 0 if the remove succeeded.
  */
int remove_front(list* llist, list_op free_func)
{
  if(llist->size==0){
    return -1;
  }
    if(llist->size>1){
      node* headNext = llist->head->next;
      (*free_func)(llist->head->data);
      free(llist->head);
      llist->head = headNext;
      llist->size--;
  }
  else if(llist->size==1){
    (*free_func)(llist->head->data);
    free(llist->head);
    llist->head = NULL;
    llist->tail = NULL;
    llist->size--;
  }
    return 0;
}

/** remove_back
  *
  * Removes the node at the back of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_back(list* llist, list_op free_func)
{
  if(llist->size==0){
    return -1;
  }
    if(llist->size>1){
      node* tailPrev = llist->tail->prev;
      (*free_func)(llist->tail->data);
      free(llist->tail);
      llist->tail = tailPrev;
      llist->size--;
  }
  else if(llist->size==1){
    (*free_func)(llist->tail->data);
    free(llist->tail);
    llist->head = NULL;
    llist->tail = NULL;
    llist->size--;
  }
    return 0;
}

/** copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param llist A pointer to the linked list to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *        data that's being used in this linked list, allocating space for
  *        every part of that data on the heap. This is some function you must
  *        write yourself for testing, tailored specifically to whatever context
  *        you're using the linked list for in your test.
  * @return The linked list created by copying the old one
  */
list* copy_list(list* llist, list_cpy copy_func)
{
  
  if(llist->size==0 && llist->head==NULL){
    return NULL;
  }
  
  list* newList = create_list();
  node* currentHead = llist->head;

  for(int i = 0; i<(llist->size); i++){
    void* oldData = currentHead->data;
    push_back(newList, (*copy_func)(oldData));
    if(currentHead!=llist->tail){
      currentHead=currentHead->next;
    }
  }
  newList->size = llist->size;
  return newList;
}

/** size
  *
  * Gets the size of the linked list
  *
  * @param llist a pointer to the list
  * @return The size of the linked list
  */
int size(list* llist)
{
    ///@note simply return the size of the linked list.  Its that easy!
    return llist->size;
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns true
  *
  * @param llist a pointer to the list
  * @param pred_func a pointer to a function that when it returns true it will remove the element from the list and 
  * do nothing otherwise @see list_pred.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_if(list* llist, list_pred pred_func, list_op free_func)
{
  int numRemove = 0;
  node* currentHead = llist->head;
  while(currentHead!=NULL && llist->size!=0){
  	node* currentNext = currentHead->next;
    if((*pred_func)(currentHead->data)){
      if(currentHead==llist->head){
        remove_front(llist, free_func);
      }
      else if(currentHead==llist->tail){
        remove_back(llist, free_func);
      }
      else{
        currentHead->prev->next = currentHead->next;
        currentHead->next->prev = currentHead->prev;
        (*free_func)(currentHead->data);
        free(currentHead);
        llist->size--;
      }
      numRemove++;
    }
    if(currentHead!=llist->tail){
      currentHead=currentNext;
    }
    else{
      currentHead=NULL;
    }
  }
    return numRemove;
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list
  * @return 1 if the list is indeed empty 0 otherwise.
  */
int is_empty(list* llist)
{
    ///@note an empty list by the way we want you to implement it has a size of zero and head points to NULL.
    return (llist->size==0);
}

/** empty_list
  *
  * Empties the list after this is called the list should be empty.
  *
  * @param llist a pointer to a linked list.
  * @param free_func function used to free the node's data.
  */
void empty_list(list* llist, list_op free_func)
{
  u16 listSize = llist->size;
  if(!(listSize==0 && llist->head==NULL)){
    for(int i = 0; i<listSize; i++){
      remove_front(llist, free_func);
    }
  }
  llist->size=0;
  llist->head=NULL;
  llist->tail=NULL;
    /// @todo Implement
    /// @note Free all of the nodes not the linked list itself.
    /// @note do not free llist.
}

/** traverse
  *
  * Traverses the linked list calling a function on each node's data.
  *
  * @param llist a pointer to a linked list.
  * @param do_func a function that does something to each node's data.
  */
void traverse(list* llist, list_op do_func)
{
  node* currentHead = llist->head;
  for(int i =0; i<llist->size; i++){
    (*do_func)(currentHead->data);
    if(currentHead!=llist->tail){
      currentHead = currentHead->next;
    }
  }
    /// @todo Implement
}