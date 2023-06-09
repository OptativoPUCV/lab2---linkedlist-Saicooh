#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node 
{
  void *data;
  Node *next;
  Node *prev;
};

struct List 
{
  Node *head;
  Node *tail;
  Node *current;
};

typedef List List;

Node *createNode(void *data) 
{
    Node *new = (Node *) malloc(sizeof(Node));
    assert (new != NULL);
    new -> data = data;
    new -> prev = NULL;
    new -> next = NULL;
    return new;
}

List *createList()
{
  List *list = (List *) malloc (sizeof(List));

  if (list == NULL) return NULL;
  
  list -> head = NULL;
  list -> tail = NULL;
  
  return list;
}

void *firstList(List *list) 
{
  if (list -> head == NULL || list == NULL ) return NULL;
  
  list -> current = list -> head;
  
  return list -> current -> data;
}

void *nextList(List *list) 
{
  if (list -> current == NULL || list == NULL || list -> current -> next == NULL) return NULL;
  
  list -> current = list -> current -> next;
  
  return list -> current -> data;
}

void *lastList(List *list)
{
  if (list == NULL || list -> tail == NULL) return NULL;
  
  while (list -> current -> next != NULL) list -> current = list -> current -> next;
  
  list -> current = list -> tail;
  
  return list -> tail -> data;
}

void *prevList(List *list) 
{
  if(list -> current == NULL || list -> current -> prev == NULL) return NULL;
  
  list -> current = list -> current -> prev;
  
  if (list -> current == NULL) return NULL;
  
  return list -> current-> data;
}

void pushFront(List *list, void *data) 
{
  Node *nuevoDato = createNode(data);
  
  if (list -> head == NULL)
  {
    list -> head = nuevoDato;
    
    list -> tail = nuevoDato;
  }
  else
  {
    nuevoDato -> next = list -> head;
    
    list -> head -> prev = nuevoDato;
    
    list -> head = nuevoDato;
  }
}

void pushBack(List *list, void *data) 
{
    list->current = list -> tail;
  
    pushCurrent(list,data);
}

void pushCurrent(List *list, void *data) 
{
  Node *nuevoDato = createNode(data);

  if (list -> head == NULL)
  {
    list -> head = nuevoDato;
    
    list -> tail = nuevoDato;
    
    return;
  }
  
  if(list -> current -> next == NULL)
  {
    nuevoDato -> prev = list -> current;

    list -> current -> next = nuevoDato;
    
    list -> tail = nuevoDato;
  }
  else
  {
    nuevoDato -> prev = list -> current;
    list -> current -> next -> prev = nuevoDato;
    nuevoDato -> next = list -> current->next;
    list -> current -> next = nuevoDato;
  }
}

void *popFront(List *list) 
{
  list->current = list->head;
  return popCurrent(list);
}

void *popBack(List *list) 
{
  list->current = list->tail;
  return popCurrent(list);
}

void *popCurrent(List *list) 
{
  
  if (list -> head == NULL) return NULL;
  
  void *aux = list -> current -> data;

  if (list -> head == list -> current)
  {
    list -> current -> next -> prev = NULL;
    list -> head = list -> current -> next;
  }
  else if (list -> tail == list -> current)
  {
    list -> current -> prev -> next = NULL;
    list -> tail = list -> current -> prev;
  }
  else
  {
    list -> current -> prev -> next = list -> current -> next;
    list -> current -> next -> prev = list -> current -> prev;
  }

  free(list -> current);
  
  return aux;
}

void cleanList(List *list) 
{
  while (list->head != NULL) 
  {
    popFront(list);
  }
}