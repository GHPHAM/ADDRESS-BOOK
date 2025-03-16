#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <iostream>
#include "LinkedList.h"

struct AddressBook {
    Node* head;
    AddressBook()
    {
        head = nullptr;
    }
    AddressBook(char* name, char* email, short int phoneNumber)
    {
        head = nullptr;
        add(name, email, phoneNumber);
    }
    void add(char* name, char* email, short int phoneNumber)
    {
        Node* node = new Node();
        node->name = name;
        node->email = email;
        node->phoneNumber = phoneNumber;
        node->next = nullptr;

        // New node is either first, or must be added to the front I.E the first name in the alphabetical order
        if (head == nullptr || strcmp(name, head->name) < 0)
        {
            node->next = head;
            head = node;
            return;
        }

        // New node is not the first, so must find the correct place for it
        Node* current = head;
        while (current->next != nullptr && strcmp(current->next->name, name) < 0)
            current = current->next;

        // Insert the new node
        node->next = current->next;
        current->next = node;
    }

    /* Since we can't use the library cstring, we have to implement it ourselves
     * We basically go through the character array, comparing each character
     * If the characters are different, we return the difference
    */
    int strcmp(const char *str1, const char *str2)
    {
        if (str1 == str2)
            return 0; // If same memory address then is identical

        long int i = 0;
        while (str1[i] != '\0' && str2[i] != '\0')
        {
            if (str1[i] != str2[i]) // if the characters are literally the same, there's literally no reason to compare. move on.
            {
                return (unsigned char)str1[i] - (unsigned char)str2[i];
            }
            i++;
        }
        return (unsigned char)str1[i] - (unsigned char)str2[i];
    }
};


#endif