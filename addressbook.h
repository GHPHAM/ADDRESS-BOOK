#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "LinkedList.h"

/* Address Book structure */
struct AddressBook {
    struct Node* head;
};

/* We can technically feed it struct Node** head instead of struct AddressBook* book,
 * but I think abstraction would be good here
*/

// init
void AddressBook_init(struct AddressBook* book);
void AddressBook_init_with_entry(struct AddressBook* book, char* name, char* email, short int phoneNumber);

// add
void AddressBook_add(struct AddressBook* book, char* name, char* email, short int phoneNumber);

/* remove
 * At first I wanted to only look for name, but then there are some people with the same name,
 * so I think a phone number works better
*/
void AddressBook_remove(struct AddressBook* book, short int phoneNumber);

/* find
 * If there's more people with the name name, just print them all!
*/
void AddressBook_find(struct AddressBook* book, char* name);

// print
void AddressBook_print(struct AddressBook* book);

// cleanup
void AddressBook_cleanup(struct AddressBook* book);

#endif