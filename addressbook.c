#include <stdlib.h>
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