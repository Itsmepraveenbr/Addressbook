#include "addressbook.h"

int print_user(char *fpc) 
{
    contacts cont;  //structure to hold the contact details

    //open the file in reading mode
    FILE *fp = fopen(fpc, "r");

    if (fp == NULL)
    {
        FILE_ERROR(fpc);
        return 2;
    }

    int num = 0;
    
    //if the file is empty
    if(fscanf(fp, "%d\n", &num) != 1)
    {
        printf("the file is empty Failed to read the number of contacts.\n");
        fclose(fp);
        return 2;
    }
    
    //if no contacts are present in the file
    if (num == 0) 
    {
        printf("No contacts to display.\n");
        fclose(fp);
        return 0;
    }
    printf("No of contacts: %d\n",num); //to print the total number of contacts in the file
    
    printf("List of Contacts:\n");
    printf("Name,Phone Number,Email ID,Address\n");

    // Iterate through all contacts and print their details
    for (int i = 0; i < num; i++) 
    {
        if (fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n", cont.name, cont.phNo, cont.emailId, cont.address) == 4)
        {
            printf("%s,%s,%s,%s\n", cont.name, cont.phNo, cont.emailId, cont.address);
        }
        else 
        {
            printf("Error reading contact data.\n");
        }

    }

    // Close the file
    fclose(fp);
    return 0;
}

