#include <stdlib.h>
#include <stdio.h>
#include "AddressBook.h"

void AddressBook_init(struct AddressBook* book)
{
    book->head = NULL;
}

void AddressBook_init_with_entry(struct AddressBook* book, char* name, char* email, int phoneNumber)
{
    book->head = NULL;
    AddressBook_add(book, name, email, phoneNumber);
}

void AddressBook_add(struct AddressBook* book, char* name, char* email, int phoneNumber)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->name = strdup(name);
    node->email = strdup(email);
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

struct Node* AddressBook_search(struct AddressBook* book, char* name, char* email, int phoneNumber)
{
    struct Node* current = book->head;
    while(current != NULL)
        {
            // This will not work if there's more than one person with the same name
            if((!name || strcmp(current->name, name) == 0) &&
                (!email || strcmp(current->email, email) == 0) &&
                (phoneNumber == -1 && current->phoneNumber == phoneNumber))
            {
                return current;
            }
            current = current->next;
        }
    return NULL;
}

void AddressBook_edit(struct AddressBook* book, char* name, char* email, int phoneNumber,char* newName, char* newEmail, int newPhoneNumber)
{
    struct Node* node = AddressBook_search(book, name, email, phoneNumber);
        if(node != NULL)
        {
            node->name = strdup(newName);
            node->email = strdup(newEmail);
            node->phoneNumber = newPhoneNumber;
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

bool AddressBook_isEmpty(struct AddressBook* book)
{
    if (book->head == NULL)
        return true;
    return false;
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

// compiler expects long long unsigned int, but we can just use size_t since it's the biggest, and also the same
size_t strcspn(const char *s, const char *reject) {
    size_t i, j;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = 0; reject[j] != '\0'; j++) {
            if (s[i] == reject[j]) {
                return i;
            }
        }
    }

    return i;
}

char *strdup(char *src)
{
    char *str;
    char *p;
    int len = 0;

    while (src[len])
        len++;
    str = malloc(len + 1);
    p = str;
    while (*src)
        *p++ = *src++;
    *p = '\0';
    return str;
}
