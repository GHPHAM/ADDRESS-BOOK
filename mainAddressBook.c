#include "addressbook.h"
#include "LinkedList.h"
#include "unity.h"
#include <stdio.h>

void menu(struct AddressBook* book) {
    char choice;
    printf("WELCOME TO THE ADDRESS BOOK PROGRAM\n");
    printf("l: load new contact\ns: save contact\na: add new contact\nr: remove contact\ne: edit contact\nf: find contact\np: print all contacts\nq: quit\nh: help\n");

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

                AddressBook_load(book, fileBuffer); // uncomment when implemented
                break;
            case 's':
                printf("Enter file name/directory: ");
                fgets(fileBuffer, sizeof(fileBuffer), stdin);
                fileBuffer[strcspn(fileBuffer, "\n")] = '\0';  // Remove newline

                AddressBook_save(book, fileBuffer); // uncomment when implemented
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

                AddressBook_delete(book, nameBuffer, emailBuffer, phoneNumber);
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

                short int phoneNumberEdited;
                char nameBufferEdited[128];
                char emailBufferEdited[128];

                printf("Enter edited name: ");
                //scanf("%s", &nameBuffer); // BAD BECAUSE IT WILL ONLY READ UNTIL SPACE
                fgets(nameBufferEdited, sizeof(nameBufferEdited), stdin);
                nameBufferEdited[strcspn(nameBufferEdited, "\n")] = '\0';  // Remove newline

                printf("Enter edited email: ");
                fgets(emailBufferEdited, sizeof(emailBufferEdited), stdin);
                emailBufferEdited[strcspn(emailBufferEdited, "\n")] = '\0';  // Remove newline

                printf("Enter edited phone number: ");
                scanf("%d", &phoneNumberEdited); // d stands for decimal

                AddressBook_edit(book, nameBuffer, emailBuffer, phoneNumber, nameBufferEdited, emailBufferEdited, phoneNumberEdited);
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

                node = AddressBook_search(book, nameBuffer, emailBuffer, phoneNumber);

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

/*
 * UNITY TEST
 */

struct AddressBook testBook;

// Init and free
// This will run before each test
void setUp()
{
    AddressBook_init(&testBook); // Initialize a fresh address book
}

// This will run after each test
void tearDown()
{
    AddressBook_free(&testBook); // Clean up
}

// Test the initialization function
void test_AddressBook_init()
{
    TEST_ASSERT_TRUE(AddressBook_isEmpty(&testBook));
}

void test_AddressBook_init_with_entry()
{
    struct AddressBook argBook;

    // Init with args
    AddressBook_init_with_entry(&argBook, "Rainbow Dash", "RD@equestria.horse", 9012);

    // Check if empty, should be false
    TEST_ASSERT_FALSE(AddressBook_isEmpty(&argBook));

    // Search for the added contact
    struct Node* node = AddressBook_search(&argBook, "Rainbow Dash", "RD@equestria.horse", 9012);

    // Verify node exists
    TEST_ASSERT_NOT_NULL(node);

    // Verify all fields match expected values
    TEST_ASSERT_EQUAL_STRING("Rainbow Dash", node->name);
    TEST_ASSERT_EQUAL_STRING("RD@equestria.horse", node->email);
    TEST_ASSERT_EQUAL_INT(9012, node->phoneNumber);

    AddressBook_free(&argBook);
}

void test_AddressBook_add_and_edit()
{
    // Add a test contact
    AddressBook_add(&testBook, "EditMe", "EditMe@example.com", 1337);

    // Edit contact
    AddressBook_edit(&testBook, "EditMe", "EditMe@example.com", 1337, "EDITED", "EDITED@example.com", 7331);

    // Search for the added contact
    struct Node* node = AddressBook_search(&testBook, "EDITED", "EDITED@example.com", 7331);
    // Verify node exists
    TEST_ASSERT_NOT_NULL(node);

    // Verify all fields match expected values
    TEST_ASSERT_EQUAL_STRING("EDITED", node->name);
    TEST_ASSERT_EQUAL_STRING("EDITED@example.com", node->email);
    TEST_ASSERT_EQUAL_INT(7331, node->phoneNumber);

    AddressBook_free(&testBook);
}

// Test adding and finding a contact
void test_AddressBook_add_and_find(void)
{
    AddressBook_add(&testBook, "Test Name", "test@example.com", 1234);

    // Search for the contact we just added
    struct Node* node = AddressBook_search(&testBook, "Test Name", "test@example.com", 1234);

    // Assert that the contact was found
    TEST_ASSERT_NOT_NULL(node);

    // Test finding a non-existent contact
    node = AddressBook_search(&testBook, "Not Exist", "none@example.com", 5678);
    TEST_ASSERT_NULL(node);

    AddressBook_free(&testBook);
}

// Test load and finding a contact
void test_AddressBook_load_and_find(void)
{
    AddressBook_load(&testBook, "input.csv");

    // Search for the contact we just added
    struct Node* node = AddressBook_search(&testBook, "Pinkie Pie", "Ponka@equestria.horse", 1234);

    // Assert that the contact was found
    TEST_ASSERT_NOT_NULL(node);

    // Verify all fields match expected values
    TEST_ASSERT_EQUAL_STRING("Pinkie Pie", node->name);
    TEST_ASSERT_EQUAL_STRING("Ponka@equestria.horse", node->email);
    TEST_ASSERT_EQUAL_INT(1234, node->phoneNumber);

    AddressBook_free(&testBook);
}

// Test load and clearing the book
void test_AddressBook_load_and_clear(void)
{
    AddressBook_load(&testBook, "input.csv");

    // Search for the contact we just added
    struct Node* node = AddressBook_search(&testBook, "Pinkie Pie", "Ponka@equestria.horse", 1234);

    // Assert that the contact was found
    TEST_ASSERT_NOT_NULL(node);

    AddressBook_free(&testBook);

    TEST_ASSERT_TRUE(AddressBook_isEmpty(&testBook));
}

// Test adding and removing
void test_AddressBook_add_and_remove()
{
    // Test the newly initialized AddressBook to be empty
    TEST_ASSERT_TRUE(AddressBook_isEmpty(&testBook));

    AddressBook_init_with_entry(&testBook, "Test Remove", "removeMe@example.com", 1234);

    // Test it to not be empty after adding
    TEST_ASSERT_FALSE(AddressBook_isEmpty(&testBook));

    AddressBook_delete(&testBook, "Test Remove", "removeMe@example.com", 1234);

    // Assert that the list is empty after deleting the only contact in that list
    TEST_ASSERT_TRUE(AddressBook_isEmpty(&testBook));

    AddressBook_free(&testBook);
}

void UnityTest()
{
    UNITY_BEGIN();

    RUN_TEST(test_AddressBook_init);
    RUN_TEST(test_AddressBook_init_with_entry);
    RUN_TEST(test_AddressBook_add_and_find);
    RUN_TEST(test_AddressBook_add_and_edit);
    RUN_TEST(test_AddressBook_add_and_remove);
    RUN_TEST(test_AddressBook_load_and_find);
    RUN_TEST(test_AddressBook_load_and_clear);

    UNITY_END();
}


/*
 * END OF UNITY TEST
 */

int main() {
    char choice;
    printf("WELCOME TO THE ADDRESS BOOK PROGRAM\n");
    printf("Unit Test? (y/n): ");
    scanf(" %c", &choice); // leading space to ignore whitespace
    while (getchar() != '\n');  // Clear input buffer, space before `%c` skips leading whitespace

    if (choice == 'y')
    {
        UnityTest();
        AddressBook_free(&testBook);
    }
    else // MENU INTERFACE, UNUSED IF WE ARE UNIT TESTING
    {
        struct AddressBook myBook;
        menu(&myBook); // feed address
        AddressBook_free(&myBook); // free memory
    }




    // Legacy code used for testing
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