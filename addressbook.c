#include <stdlib.h>
#include <stdio.h>
#include "AddressBook.h"

void AddressBook_init(struct AddressBook* book)
{
    book->head = NULL;
}

void AddressBook_init_with_entry(struct AddressBook* book, char* name, char* email, short int phoneNumber)
{
    book->head = NULL;
    AddressBook_add(book, name, email, phoneNumber);
}

void AddressBook_add(struct AddressBook* book, char* name, char* email, short int phoneNumber)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->name = name;
    node->email = email;
    node->phoneNumber = phoneNumber;
    node->next = NULL;

    // New node is either first, or must be added to the front I.E the first name in the alphabetical order
    if (book->head == NULL || strcmp(name, book->head->name) < 0)
    {
        node->next = book->head;
        book->head = node;
        return;
    }

    // New node is not the first, so must find the correct place for it
    // if name is identical, tack it to the end of the existing
    struct Node* current = book->head;
    while (current->next != NULL && strcmp(current->next->name, name) < 0)
        current = current->next;

    // Insert the new node
    node->next = current->next;
    current->next = node;
}

void AddressBook_search(struct AddressBook* book, char* name, char* email, short int phoneNumber)
{
    struct Node* node = book->head;
    while(current != NULL)
        {
            if((name && strcmp(current->name, name) == 0) ||
                (email && strcmp(current->email, email) == 0) ||
                (phoneNumber != -1 && current->phoneNumber == phoneNumber))
            {
                return current;
            }
            current = current->next;
        }
    return NULL;
}

void AddressBook_free(struct AddressBook* book)
{
    struct Node* current = book->head;
    struct Node* temp;
    while(current != NULL)
        {
            temp = current;
            current = current->next;
            free(temp->name);
            free(temp->email);
            free(temp);
        }
    book->head = NULL;
}

void AddressBook_edit(struct AddressBook* book, char* name, char* email, short int phoneNumber)
{
    struct Node* node = AddressBook_search(book, name);
        if(node != NULL)
        {
            free(node->email);
            node->email = strdup(new_email);
            node->phoneNumber = new_phoneNumber;
        }
        else
        {
            printf("Entry not found: %s\n", name);
        }
}

void AddressBook_print(struct AddressBook* book) {
    struct Node* current = book->head;
    printf("Address Book Entries:\n");
    printf("--------------------\n");

    if (current == NULL) {
        printf("(Empty address book)\n");
        return;
    }

    while (current != NULL) {
        printf("Name: %s\n", current->name);
        printf("Email: %s\n", current->email);
        printf("Phone: %d\n", current->phoneNumber);
        printf("--------------------\n");
        current = current->next;
    }
}

/* ultility */

/* Since we can't use the library cstring, we have to implement it ourselves.
 * We basically go through the character array, comparing each character.
 * If the characters are different, we return the difference.
 */
int strcmp(const char* str1, const char* str2)
{
    if (str1 == str2)
        return 0; /* If same memory address then is identical */

    long int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        /* if the characters are literally the same, there's literally no reason to compare. move on. */
        if (str1[i] != str2[i])
        {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
        i++;
    }
    return (unsigned char)str1[i] - (unsigned char)str2[i];
}
