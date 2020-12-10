#include <assert.h>
#include "linked-list.c"

// 1. Count
int count(Node* head){
  Node* curr = head;
  int counter       = 0;
  while(curr){
    counter++;
    curr = curr->next;
  }
  return counter;
}

// 2. getNth
int getNth(Node* head, int pos){
  int len = count(head);
  assert(pos < len);

  Node* curr = head;
  int idx = 0;

  while(idx++ < pos){
    curr = curr->next;
  }

  return curr->data;
}

// 3. deleteList
void deleteList(Node** head){
  Node* curr = *head;
  while(curr){
    Node* tmp = curr->next;
    free(curr);
    curr = tmp;
  }
  *head = NULL;
}

// 4. pop
int pop(Node** head){
  assert(*head != NULL);
  int headData = (*head)->data;
  Node* oldHead = *head;
  
  *head = (*head)->next;
  free(oldHead);
  return headData;
}

// 5. insertNth
void insertNth(Node** head, int pos, int data){
  int len = count(*head);
  assert(pos >= 0 && pos <= len);

  int idx    = 0;
  Node* curr = *head;
  Node* prev = NULL;
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = data;

  while(curr && idx++ != pos){
    prev = curr;
    curr = curr->next;
  }

  if(!prev){ // list was empty
    newNode->next = *head;
    *head = newNode;
  }
  else{
    if(!curr){ //add to last node.
      prev->next = newNode;
      newNode->next = NULL;
    }
    else{ // not "edge"
      prev->next = newNode;
      newNode->next = curr;
    }
  }

}

// 6. sortedInsert - list needs to be in ASC order.
void sortedInsert(Node** head, Node* newNode){
  Node* curr = *head;
  Node* prev = NULL;

  while(curr && curr->data < newNode->data){
    prev = curr;
    curr = curr->next;
  }

  if(!prev){ // list was empty
    newNode->next = *head;
    *head = newNode;
  }
  else{
    if(!curr){ //add to last node.
      prev->next = newNode;
      newNode->next = NULL;
    }
    else{ // not "edge"
      prev->next = newNode;
      newNode->next = curr;
    }
  }

}

// 7. insertSort - list needs to be in ASC order.
void insertSort(Node** head){
  Node* sortedList = NULL;
  Node* curr = *head;

  while(curr){
    Node* tmp = curr->next;
    sortedInsert(&sortedList, curr);
    curr = tmp;
  }

  *head = sortedList;
}

// 8. Append
void append(Node** a, Node** b){
  if(!*a){
    *a = *b;
  }
  else{
    Node* curr = *a;
    while(curr->next){
      curr = curr->next;
    }
    curr->next = *b;
  }
  *b = NULL;
}

// 9. frontBackSplit
void frontBackSplit(Node** source, Node** front, Node** back){
  if(!*source){
    return;
  }
  
  Node* slow = *source;
  Node* fast = slow->next;
  
  while(fast && fast->next){
    slow = slow->next;
    fast = fast->next->next;
  }
  
  Node* tmp  = slow->next;
  slow->next = NULL;
  *front     = *source;
  *back      = tmp;
}

// 10. removeDuplicates - list needs to be in ASC order.
void removeDuplicates(Node* head){
  Node* curr = head;

  while(curr){
    Node* nextNode = curr->next;
    while(nextNode && nextNode->data == curr->data){
      Node* tmp = nextNode->next;
      free(nextNode);
      nextNode = tmp;
    }
    curr->next = nextNode;
    curr = curr->next;
  }
}

// 11. moveNode
void moveNode(Node** dest, Node** source){
  assert(source != NULL);

  Node* tmp = (*source)->next;
  (*source)->next = *dest;
  *dest = *source;
  *source = tmp;
}

// 12. alternatingSplit
void alternatingSplit(Node** source, Node** evens, Node** odds){
  if(!*source){
    return;
  }

  bool odd = true;
  Node* curr = *source;

  while(curr){
    Node* tmp = curr->next;
    if(odd){
      moveNode(odds, source);
    }
    else{
      moveNode(evens, source);
    }
    curr = tmp;
    odd = !odd;
  }

}

// 13. shuffleMerge
Node* shuffleMerge(Node* a, Node* b){
  Node dummy;
  dummy.next = NULL;
  Node* curr = &dummy;

  while(a && b){
    curr->next = a;
    curr = a;
    a = a->next;

    curr->next = b;
    curr = b;
    b = b->next;
  }

  if(!a){
    curr->next = b;
  }

  if(!b){
    curr->next = a;
  }

  return dummy.next;
}

// 14. sortedMerge
Node* sortedMerge(Node* a, Node* b){
  Node d;
  d.next     = NULL;
  Node* curr = &d;

  while(a && b){
    if(a->data < b->data){
      curr->next = a;
      curr = a;
      a = a->next;
    }
    else{
      curr->next = b;
      curr = b;
      b = b->next;
    }
  }

  if(!a){
    curr->next = b;
  }

  if(!b){
    curr->next = a;
  }

  return d.next;
}

// 15. mergeSort
void mergeSort(Node** head){
  if(!*head || !(*head)->next){
    return;
  }
  Node* a, *b;
  frontBackSplit(&(*head), &a, &b);
  mergeSort(&a);
  mergeSort(&b);
  (*head) = sortedMerge(a, b);
}

// 16. sortedIntersect
Node* sortedIntersect(Node* a, Node* b){
  Node d = {-1, NULL};
  Node* curr = &d;
  while(a && b){
    if(a->data < b->data){
      a = a->next;
    }
    else if(b->data < a->data){
      b = b->next;
    }
    else{
      Node* newNode = (Node*)malloc(sizeof(Node));
      newNode->data = a->data;
      newNode->next = NULL;
      curr->next    = newNode;
      curr = newNode;
      a    = a->next;
      b    = b->next;
    }
  }
  return d.next;
}

// 17. reverse
void reverse(Node** head){
  if(!*head){
    return;
  }
  Node* prev = NULL; 
  Node *curr = *head;

  while(curr){
    Node* tmp = curr->next;
    curr->next = prev;
    prev = curr;
    curr = tmp;
  }
  *head = prev;
}

// 18. recursiveReverse
void recursiveReverse(Node** head){
  if(!*head || !(*head)->next){
    return;
  }

  Node* tmp = (*head)->next;

  recursiveReverse(&tmp);
  (*head)->next->next = *head;
  (*head)->next = NULL;

  *head = tmp;
}

int main(){
  Node* head = NULL;
  addNode(&head, 6);
  addNode(&head, 5);
  addNode(&head, 4);
  addNode(&head, 3);
  addNode(&head, 2);

  // insertNth(&head, 0, 0);

  // === test for #6 ====
  // Node* newNode = (Node*)malloc(sizeof(Node));
  // newNode->data = 0;
  // newNode->next = NULL;
  // sortedInsert(&head, newNode3);

  traverseList(head);

  deleteList(&head);
}