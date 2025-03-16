#ifndef LINKEDLIST_H
#define LINKEDLIST_H
struct Node {
  short int phoneNumber;
  // Why char*? We are going to create a char array, and pass its address there, so we don't have to allocate memory on runtime
  char* name;
  char* email;

  // Pointer to the next node
  Node* next;
};

// Probably not going to be used
struct LinkedList {
    Node* head;
    LinkedList() {
        head = nullptr;
    }
    LinkedList(Node* node)
    {
        head = node;
    }

    void add(Node* node)
    {
        if (head == nullptr)
        {
            head = node;
        }
        else
        {
            Node* temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = node;
        }
    }
};

#endif