#ifndef LINKEDLIST_H
#define LINKEDLIST_H
struct Node {
  short int phoneNumber;
  // Why char*? We are going to create a char array, and pass its address there, so we don't have to allocate memory on runtime
  char* name;
  char* email;
  struct Node* next;
};

#endif