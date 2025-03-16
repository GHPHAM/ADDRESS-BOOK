#include "addressbook.h"
#include <stdio.h>

int main() {
    struct AddressBook myBook;
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

    return 0;
}