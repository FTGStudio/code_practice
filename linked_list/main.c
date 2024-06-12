#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  int data;
  struct Node *next;
} Node_t;

// Create a node
Node_t* createNode(int data){
  Node_t* newNode = (Node_t*)malloc(sizeof(Node_t));
  if(newNode == NULL){
    printf("Memory allocation has failed :(\n");
    exit(1);
  }

  newNode->data = data;
  newNode->next = NULL;

  return newNode;
}

// Insert at the head
void insertAtHead(Node_t** head, int data){
  Node_t* newNode = createNode(data);
  newNode->next = *head;
  *head = newNode;
}

// Insert at the tail
void insertAtTail(Node_t** head, int data){
  Node_t* newNode = createNode(data);
  if(*head == NULL){
    *head = newNode;
    return;
  }
  Node_t* tmp = *head;
  while(tmp->next != NULL){
    tmp = tmp->next;
  }

  tmp->next = newNode;
}

// Print the list
void printList(Node_t* head){
  Node_t* tmp = head;
  if(head == NULL){
    printf("Passed in invalid Node.\n");
  }

  while(tmp != NULL){
    printf("%d\n", tmp->data);
    tmp = tmp->next;
  }
}

int main() {

  Node_t* n1 = createNode(1);
  Node_t* n2 = createNode(2);
  Node_t* n3 = createNode(3);
  Node_t* n4 = createNode(4);
  Node_t* n5 = createNode(5);


  n1->next = n2;
  n2->next = n3;
  n3->next = n4;
  n4->next = n5;

  printf("List before new head\n");
  printList(n1);
  printf("List Ater insert at head\n");
  insertAtHead(&n1, 10);
  printList(n1);
  printf("List Ater insert at tail\n");
  insertAtTail(&n1, 27);
  printList(n1);

  return 0;
}