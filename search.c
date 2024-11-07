#include "addressbook.h"

int search_user(char *fpc) 
{
    contacts cont;  //structure to hold the contact details
    char searching_term[50];  //array to hold the name to be searched
    int found = 0;   //variable to tell that the contact is present in the file

    // Open the file for reading
    FILE *fp = fopen(fpc, "r");
    if (fp == NULL) {
        FILE_ERROR(fpc);
        return 2;
    }

    // Read the number of contacts in the file
    int num = 0;
    fscanf(fp, "%d\n", &num);

    // Ask user what they want to search by
    int option;
    printf("Search by:\n1. Name\n2. Phone Number\n3. Email ID\n");
    printf("Enter your option: ");
    scanf("%d", &option);

   
    switch (option)
    {
        case 1:    //if user want to search by name
            printf("Enter name: ");
            scanf("%s", searching_term);        
            break;
        case 2:     //if user want to search by phone number
            printf("Enter phone number: ");
            scanf("%s", searching_term);
            break;
        case 3:      //if user want to search by  emailID
            printf("Enter email ID: ");
            scanf("%s", searching_term);
            break;
        default:     //if user enters an invalid option
            INVALID_OPTION;
            fclose(fp);
            return 1;
    }

    // Search for the contact in the file
    for (int i = 0; i < num; i++)
    {
        fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n", cont.name, cont.phNo, cont.emailId, cont.address);

        if ((option == 1 && strcmp(cont.name, searching_term) == 0) ||
            (option == 2 && strcmp(cont.phNo, searching_term) == 0) ||
            (option == 3 && strcmp(cont.emailId, searching_term) == 0)) 
        {
            // Print the matching contact
            printf("Contact Found:\n");
            printf("Name: %s\nPhone Number: %s\nEmail ID: %s\nAddress: %s\n", cont.name, cont.phNo, cont.emailId, cont.address);
            found = 1;
          //  break;
        }
    }

    if (!found) {
        printf("Contact not found.\n");
    }

    // Close the file
    fclose(fp);

    return 0;
}

