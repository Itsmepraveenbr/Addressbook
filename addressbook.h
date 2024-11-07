//header files


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//main structure to store the contact details
typedef struct Contact
{
	char name[50];
	char  phNo[11];
	char emailId[50];
	char address[50];
}contacts;

//functions prototypes 

//function to add user
int add_user(char * fpc);

//function to search user
int search_user(char * fpc);

//function to edit user details
int edit_user(char * fpc);

//function to delete user
int del_user(char * fpc);

//function to print user
int print_user(char * fpc);


//macro to print error message when we cant open the file
#define FILE_ERROR(file_name) printf("couldn't open file: %s\n", file_name)


//macro to print as invalid choice when the user enters an invalid option
#define INVALID_OPTION printf("invalid option\nchoose a correct one\n")
