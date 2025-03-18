#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book) 
{

	address_book->fp = fopen(DEFAULT_FILE, "r"); // Checks file existence
    	if (address_book->fp == NULL) 
	{
		address_book->fp = fopen(DEFAULT_FILE, "w") // Creates the file if file doesn't exist
		perror("Error opening file");
		return e_fail;
	}
	else
	{
		/* Create a file for adding entries */
		address_book->fp = fopen(DEFAULT_FILE, "a") // append mode
			
		fprintf(address_book->fp, "%c, %c, %c\n", address_book->list->name[NAME_COUNT][NAME_LEN], address_book->list->phone_numbers[PHONE_NUMBER_COUNT][NUMBER_LEN], address_book->list->email_addresses[EMAIL_ID_COUNT][EMAIL_ID_LEN]);
			
		fclose(address_book->fp);
	}
	
	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");
	
	fwrite(address_book->list->name, sizeof(char), NAME_LEN, address_book->fp);
  	fwrite(address_book->list->phone_numbers, sizeof(char), NUMBER_LEN, address_book->fp);
  	fwrite(address_book->list->email_addresses, sizeof(char), EMAIL_ID_LEN, address_book->fp);

	if (address_book->fp == NULL)
	{
		perror("Error opening file");
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	fclose(address_book->fp);

	return e_success;
}
