#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node Node;

struct node {
  int data;
  Node* next;
};

Node* initList(){
  Node* head = (Node*)malloc(sizeof(Node));
  if(!head){return NULL;}

  head->data = 1;
  head->next = NULL;
  return head;
}

bool addNode(Node** head, int data){
  Node* newNode = (Node*)malloc(sizeof(Node));
  if(!newNode){return false;}

  newNode->data = data;
  newNode->next = *head;
  *head = newNode;
  return true;
}

void traverseList(Node* head){
  Node* curr = head;
  printf("%s: ", "Traversing");
  while(curr){
    printf("%d, ", curr->data);
    curr = curr->next;
  }
  printf("\n \n");
}