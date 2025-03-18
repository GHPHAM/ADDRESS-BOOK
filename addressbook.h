#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "LinkedList.h"
#include <stdbool.h> // bool is not included by default

/* Address Book structure */
struct AddressBook {
    struct Node* head;
};

/* We can technically feed it struct Node** head instead of struct AddressBook* book,
 * but I think abstraction would be good here
*/

// init
void AddressBook_init(struct AddressBook* book);
void AddressBook_init_with_entry(struct AddressBook* book, char* name, char* email, int phoneNumber);

// add
void AddressBook_add(struct AddressBook* book, char* name, char* email, int phoneNumber);

/* remove
 * At first I wanted to only look for name, but then there are some people with the same name,
 * so I think a phone number works better
*/
void AddressBook_remove(struct AddressBook* book, char* name, char* email, int phoneNumber);

/* find
 * If there's more people with the name name, just print them all!
*/
struct Node* AddressBook_search(struct AddressBook* book, char* name, char* email, int phoneNumber);

// print
void AddressBook_print(struct AddressBook* book);

// edit
void AddressBook_edit(struct AddressBook* book, char* name, char* email, int phoneNumber,char* newName, char* newEmail, int newPhoneNumber);

// cleanup
void AddressBook_free(struct AddressBook* book);

bool AddressBook_isEmpty(struct AddressBook* book);

// Load and Save
void AddressBook_load(struct AddressBook *book, char* fileName);
void AddressBook_save(struct AddressBook *book, char* fileName);


// Ultilities
int strcmp(const char* str1, const char* str2);
long long unsigned int strcspn(const char *s, const char *reject);
char *strdup(char *src);

#endif