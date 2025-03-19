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

void AddressBook_delete(struct AddressBook* book, char* name, char*email, int phoneNumber)
{
    struct Node* target = AddressBook_searh(book, name, email, phoneNumber);

    if(target == NULL)
    {
        printf("No matching contact found for deletion: %s\n", name);
        return;
    }

    struct Node* current = book->head;
    struct Node* prev = Null;

    while(current != NULL)
    {
        if(current == target)
        {
            if(prev == NULL)
            {
                book->head = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            free(current->name);
            free(current->email);
            free(current);
            printf("Deleted contact: %s\n", name);
            return;
        }    
        prev = current;
        current = current->net;
    }
}

void AddressBook_print(struct AddressBook* book) {
    if (AddressBook_isEmpty(book))
    {
        printf("Address Book is empty\n");
        return;
    }
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

void AddressBook_load(struct AddressBook *book, char* fileName)
{
    printf("READING FILE...\n");
	FILE *fp = fopen(fileName, "r"); // Checks file existence
    if (fp == NULL)
	{
        fp = fopen(fileName, "w"); // Creates the file if file doesn't exist
        fclose(fp); // Close the file, since the file is newly created, and thus has no data
        printf("NO FILE UNDER THE NAME OF %s DETECTED. NEW FILE CREATED.", fileName);
        return; // Promptly return, duh.
	}

    // Read the file
    char buffer[256];
    char name[100];
    char email[100];
    char phoneNumber[20];

    // I'll not parse with functions from <String.h>
    // Loop through the file and use AddressBook_add
    while (fgets(buffer, sizeof(buffer), fp))
    {
        short int field_index = 0;
        int i = 0, j = 0;

        // Initialize fields
        name[0] = '\0';
        email[0] = '\0';
        phoneNumber[0] = '\0';

        char *currentField = name; // Start with name field
        while (buffer[i] != '\0' && buffer[i] != '\n' && buffer[i] != '\r')
        {
            if (buffer[i] == ',')
            {
                // End of field
                currentField[j] = '\0';
                j = 0;
                ++field_index;

                // Switch to next field
                if (field_index == 1)
                    currentField = email;
                else if (field_index == 2)
                    currentField = phoneNumber;
            }
            else
            {
                currentField[j] = buffer[i];
                ++j;
            }

            ++i;
        }

        // Make sure the last field is null-terminated
        currentField[j] = '\0';

        // BUG: PHONE NUMBER ISN'T PARSED CORRECTLY
        // Add the contact to the address book
        if(AddressBook_isEmpty(book))
            AddressBook_init_with_entry(book, name, email, atoi(phoneNumber));
        else
            AddressBook_add(book, name, email, atoi(phoneNumber));
    }

    fclose(fp);
}

void AddressBook_save(struct AddressBook *book, char* fileName)
{
	FILE *fp = fopen(fileName, "w");
    if (fp == NULL)
    {
        printf("ERROR OPENING FILE\n");
        return;
    }
    struct Node* current = book->head;
    if (AddressBook_isEmpty(book)) {
        printf("(Empty address book)\n");
        fclose(fp); // Close the file since we can't write anything
        return;
    }

    while (current != NULL)
    {
        fprintf(fp, "%s,", current->name);
        fprintf(fp, "%s,", current->email);
        fprintf(fp, "%d\n", current->phoneNumber);

        current = current->next;
    }

    fclose(fp);
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
