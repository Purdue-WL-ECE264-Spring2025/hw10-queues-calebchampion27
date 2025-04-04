#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
  struct list_node *node = malloc(sizeof(struct list_node));

  if (node == NULL) {  //malloc fails
    return NULL;
  }

  //initialize with value & point to null
  node->value = value;
  node->next = NULL;
  
  return node;
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node *node = new_node(value);  //make a new node point to NULL
  if (node == NULL) {return 0;}

  node->next = list->head;  //point new node to the current beginning
  list->head = node;  //change new head to new node

}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node *node = new_node(value);  //make a new node point to NULL
  if (node == NULL) {return;}

  if (list->head == NULL) {  //if list is empty
    list->head = node;
  }

  //find end of linked list, then insert "node" at the end
  struct list_node *cur = list->head;  //make new node cur to track
  while (cur->next != NULL) {  //while the current node++ isnt equal to the end
    cur = cur->next;
  }
  cur = cur->next;

}

size_t remove_from_head(struct linked_list *list) {
  if (list->head == NULL) {return 0;}  //there is nothing to delete

  struct list_node *temp = list->head;  //temp as new head
  size_t value = temp->value;

  list->head = temp->next;  //new head

  free(temp);  //free the past node

  return 0;
}

size_t remove_from_tail(struct linked_list *list) {
  if (list->head == NULL) {return 0;}  //nothing to delete

  struct list_node *temp = list->head;  //temporary
  size_t value = temp->value;
  size_t next = temp->next;

  if (next == NULL) {  //only 1 node in lists
    free(temp);
    list->head = NULL;
    return 0;
  }

  while (temp->next->next != NULL) {  //move on 1 by 1 till the end
    temp = temp->next;
  }

  size_t value = temp->next->value;
  free(temp->next);
  temp->next = NULL;
  
  return 0;
}

void free_list(struct linked_list list) {
  struct list_node *cur = list.head;
  
  while (cur != NULL) {  //free each node in list
    struct list_node *temp = cur;
    cur = cur->next;
    free(temp);
  }

}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
