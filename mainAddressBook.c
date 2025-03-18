#include "addressbook.h"
#include "LinkedList.h"
#include <stdio.h>

void menu(struct AddressBook* book) {
    char choice;
    printf("WELCOME TO THE ADDRESS BOOK PROGRAM\n");
    printf("l: load new contact\ns: save contact\na: add new contact\nr: remove contact\nf: find contact\np: print all contacts\nq: quit\nh: help\n");

    while (true)
    {
        printf("Enter your choice: ");
        scanf(" %c", &choice); // leading space to ignore whitespace
        while (getchar() != '\n');  // Clear input buffer, space before `%c` skips leading whitespace
        char fileBuffer[128];
        char nameBuffer[128];
        char emailBuffer[128];
        short int phoneNumber;
        struct Node* node;

        switch (choice)
        {
            case 'l':
                printf("Enter file name/directory: ");
                fgets(fileBuffer, sizeof(fileBuffer), stdin);
                fileBuffer[strcspn(fileBuffer, "\n")] = '\0';  // Remove newline

                //AddressBook_load(book, fileBuffer); // uncomment when implemented
                break;
            case 's':
                printf("Enter file name/directory: ");
                fgets(fileBuffer, sizeof(fileBuffer), stdin);
                fileBuffer[strcspn(fileBuffer, "\n")] = '\0';  // Remove newline

                //AddressBook_save(book, fileBuffer); // uncomment when implemented
                break;
            case 'a':
                printf("Enter name: ");
                //scanf("%s", &nameBuffer); // BAD BECAUSE IT WILL ONLY READ UNTIL SPACE
                fgets(nameBuffer, sizeof(nameBuffer), stdin);
                nameBuffer[strcspn(nameBuffer, "\n")] = '\0';  // Remove newline

                printf("Enter email: ");
                fgets(emailBuffer, sizeof(emailBuffer), stdin);
                emailBuffer[strcspn(emailBuffer, "\n")] = '\0';  // Remove newline

                printf("Enter phone number: ");
                scanf("%d", &phoneNumber); // d stands for decimal

                if(AddressBook_isEmpty(book))
                {
                    printf("Address Book is empty, initializing a new contact book\n");
                    AddressBook_init_with_entry(book, nameBuffer, emailBuffer, phoneNumber);
                }
                else
                {
                    AddressBook_add(book, nameBuffer, emailBuffer, phoneNumber);
                }
                break;
            case 'r':
                printf("Enter name: ");
                //scanf("%s", &nameBuffer); // BAD BECAUSE IT WILL ONLY READ UNTIL SPACE
                fgets(nameBuffer, sizeof(nameBuffer), stdin);
                nameBuffer[strcspn(nameBuffer, "\n")] = '\0';  // Remove newline

                printf("Enter email: ");
                fgets(emailBuffer, sizeof(emailBuffer), stdin);
                emailBuffer[strcspn(emailBuffer, "\n")] = '\0';  // Remove newline

                printf("Enter phone number: ");
                scanf("%d", &phoneNumber); // d stands for decimal

                AddressBook_remove(book, nameBuffer, emailBuffer, phoneNumber);
                break;
            case 'f':
                printf("Enter name: ");
                //scanf("%s", &nameBuffer); // BAD BECAUSE IT WILL ONLY READ UNTIL SPACE
                fgets(nameBuffer, sizeof(nameBuffer), stdin);
                nameBuffer[strcspn(nameBuffer, "\n")] = '\0';  // Remove newline

                printf("Enter email: ");
                fgets(emailBuffer, sizeof(emailBuffer), stdin);
                emailBuffer[strcspn(emailBuffer, "\n")] = '\0';  // Remove newline

                printf("Enter phone number: ");
                scanf("%d", &phoneNumber); // d stands for decimal

                node = AddressBook_find(book, nameBuffer, emailBuffer, phoneNumber);

                if (node != NULL)
                {
                    printf("Name: %s\n", node->name);
                    printf("Email: %s\n", node->email);
                    printf("Phone: %d\n", node->phoneNumber);
                }
                else
                {
                    printf("Contact not found\n");
                }
                break;
            case 'e':
                printf("Enter name: ");
                fgets(nameBuffer, sizeof(nameBuffer), stdin);
                nameBuffer[strcspn(nameBuffer, "\n")] = '\0';  // Remove newline

                printf("Enter email: ");
                fgets(emailBuffer, sizeof(emailBuffer), stdin);
                emailBuffer[strcspn(emailBuffer, "\n")] = '\0';  // Remove newline

                printf("Enter phone number: ");
                scanf("%d", &phoneNumber); // d stands for decimal

                node = AddressBook_find(book, nameBuffer, emailBuffer, phoneNumber);

                if (node != NULL)
                {
                    printf("Name: %s\n", node->name);
                    printf("Email: %s\n", node->email);
                    printf("Phone: %d\n", node->phoneNumber);
                }
                else
                {
                    printf("Contact not found\n");
                    break;
                }
                break;
            case 'p':
                AddressBook_print(book);
                break;
            case 'q':
                printf("Have a nice day :)\n\n");
                AddressBook_free(book);
                return;
            case 'h':
                printf("l: load new contact\ns: save contact\na: add new contact\nr: remove contact\np: print all contacts\nq: quit\nh: help\n");\
                break;
            default:
                printf("Invalid choice, try a different input\n");
                break;
        }
    }
}

int main() {
    struct AddressBook myBook;

    menu(&myBook); // feed address
    /*
    AddressBook_init(&myBook);

    AddressBook_add(&myBook, "Rainbow Dash", "RD@equestria.horse", 9012);
    AddressBook_add(&myBook, "Pinkie Pie", "Ponka@equestria.horse", 1234);
    AddressBook_add(&myBook, "Celestia", "Celestia@Canterlot.gov", 5678);


    // Print first address book
    AddressBook_print(&myBook);

    // Address book 2
    struct AddressBook anotherBook;
    AddressBook_init_with_entry(&anotherBook, "Applejack", "Applejack@apple.family", 3456);

    AddressBook_add(&anotherBook, "Rarity", "Rarity@carouselboutique.com", 7890);
    AddressBook_add(&anotherBook, "Twilight Sparkle", "TwilightSparkle@Canterlot.gov", 1011);
    AddressBook_add(&anotherBook, "Fluttershy", "TwilightSparkle@Canterlot.gov", 1213);

    // print the second adddress book
    printf("\nSecond Address Book:\n");
    AddressBook_print(&anotherBook);

    // Run a cleanup function here, keep it memory safe
    */
    return 0;
}