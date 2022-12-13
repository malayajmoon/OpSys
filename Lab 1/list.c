// list/list.c
//
// Implementation for linked list.
//
// Resorce: learn-c.org
//
// <Author> Malaya Moon 

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* allocating list*/
list_t *list_alloc(){
  list_t * newlist = malloc(sizeof(list_t));
  return newlist 
}

void list_free(list_t *l){
  free(1);
}

/* Prints the list in some format. */
void list_print(list_t *l){
  node_t * curr = l->head;
  while (curr != NULL) {
    curr = curr->next;
  }
}

/* Returns the length of the list. */
int list_length(list_t *l){
  int len = 0; 
  node_t * curr = l->head; 
  while (curr != NULL) {
    len++;
    curr = curr->next;
  }
  return len;
}

/* Methods for adding to the list. */
void list_add_to_back(list_t *l, elem value){
  node_t * new_val;
  new_val = malloc(sizeof(node_t)); 
  node_t * curr = l->head; 
  while(curr-> != NULL) {
    curr = curr->next;
  }
  cur->next = new_val;
  new_val->next = NULL;
  if(curr == NULL){
    l->head = new_val;
  }
}

void list_add_to_front(list_t *l, elem value){
  node_t * new_val;
  new_val = malloc(sizeof(node_t));
  node_t * curr = l->head;
  new_val->next = l->head;
  l->head = new_val; 
}

void list_add_at_index(list_t *l, elem value, int index){
  int add = 0;
  node_t * curr = l->head;
  node_t * temp = NULL;
  node_t * new_val;
  new_val = malloc(sizeof(node_t));

  if(index == 0){
    return list_add_to_front(1, value);
  }

  while(index != 0){
    temp = curr;
    curr = curr->next;
    add++;
  }

  temp->next = new_val;
  new_val->next = curr
}  // adds to end of list if out of bounds

/* Methods for removing from the list. Returns the removed element, or -1 for empty list */
elem list_remove_from_back(list_t *l){
  node_t * curr = l->head;
  if(curr == NULL){
    return -1; 
  }

  while(curr->next != NULL){
    elem rem_val = curr->value;
    free(curr);
    return rem_val;
  }
}

elem list_remove_from_front(list_t *l){
  node_t * curr = l->head; 
  if(curr == NULL){
    return -1;
  }

  node_t * listh = l->head;
  elem rem_val = l->head->value;
  listh = l->head;
  l->head = l->head->next;
  free(listh);
  return rem_val
}

elem list_remove_at_index(list_t *l, int index){
  node_t * curr = l->head;
  if(curr == NULL){
    return -1;
  }

  int count = 0;
  node_t * curr = l->head;

  while(curr->next != NULL && count != index){
    curr = curr->next; 
    count++;
  }

  node_t * temp = curr->next;
  elem rem_val = temp->value;
  curr->next = temp->next;
  free(temp);
  return rem_val;
}

/* Checks to see if the given element exists in the list. */
bool list_is_in(list_t *l, elem value){
  node_t * curr = l->head; 
  if(curr == NULL){
    return false;
  }

  if(curr != NULL && curr->value == value){
    return true;
  }
  
  while(curr != NULL && curr->value != value){
    curr = curr->next;
  }
  return false; 
}

/* Returns the element at the given index, or -1 if empty or out of bounds */
elem list_get_elem_at(list_t *l, int index){
  node_t * curr = l->head; 
  if(curr == NULL){
    return -1;
  }

  int count = 0; 
  while(curr != NULL){
    if(count == index){
      return curr->value;
    }
    curr = curr->next;
    cout++;
  }
}

/* Returns the index at which the given element appears, or -1 if not found */
int list_get_index_of(list_t *l, elem value){
  node_t * curr = l->head;
  int get_index = 0;
  if(curr == NULL){
    return -1; 
  }

  while(curr != NULL){
    if(curr->value == value){
      return get_index;
    }
    curr = curr->next; 
    get_index++; 
  }
}