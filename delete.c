#include "addressbook.h"


int del_user(char *fpc) 
{
    contacts cont;      //structure to hold the contact details
    char searching_name[50];      //array to hold the name to be deleted 
    int found = 0;        //variable to tell that the contact is present in the file

    //open the original file in reading mode
    FILE *fp = fopen(fpc, "r");        
    if (fp == NULL) 
    {
        FILE_ERROR(fpc);
        return 2;
    }

   //open the temporary file in writing mode
    FILE *ftemp = fopen("temp.csv", "w+");

    if (ftemp == NULL) 
    {
        printf("Could not open temporary file.\n");
        fclose(fp);
        return 2;
    }

   
    int num = 0;
    fscanf(fp, "%d\n", &num);


    // Ask user for the name of the contact to delete
    printf("Enter name of the contact to delete: ");
    scanf("\n%[^\n]s", searching_name);

    int new_num = 0; //variable to hold the updated number of contacts
    int serial_no = 0;
    int choice = 1;

    //  print all matching contacts with their serial numbers
    for (int i = 0; i < num; i++) 
    {
        fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n", cont.name, cont.phNo, cont.emailId, cont.address);

        if (strcmp(cont.name, searching_name) == 0)
        {
            printf("%d. contact: %s, %s, %s, %s\n", ++serial_no, cont.name, cont.phNo, cont.emailId, cont.address);
        }
    }

    //  If there are multiple contacts, ask the user for the serial number of the contact to be deleted
    if (serial_no > 1) 
    {
        printf("%d contacts found. Enter the serial number of the contact to delete: ", serial_no);
        scanf("%d", &choice);

        //if user enters an invalid serial number ask user to enter a valid serial number
        while (choice < 1 || choice > serial_no) 
        {
            printf("Enter a valid serial number to delete: ");
            scanf("%d", &choice);
        }
    }

    // Rewind the file pointer    
    rewind(fp);
    fscanf(fp, "%d\n", &num);
    serial_no = 0;


    // to Copy all contacts except the one chosen to delete into the temporary file
    for (int i = 0; i < num; i++)
    {
        fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n", cont.name, cont.phNo, cont.emailId, cont.address);
        if (strcmp(cont.name, searching_name) == 0)
        {
            serial_no++;

            if (serial_no == choice)
            {
                printf("Deleting contact: %s, %s, %s, %s\n", cont.name,cont.phNo,cont.emailId,cont.address);
                found = 1;
                continue;  // to Skip this contact
            }
        }

        // Write all other contacts to the temporary file
        fprintf(ftemp, "%s,%s,%s,%s\n", cont.name, cont.phNo, cont.emailId, cont.address);
        new_num++;
    }

   
    fclose(fp);
    fclose(ftemp);

    //if the contact to be deleted is found
    if (found)
    {
        fp = fopen(fpc, "w");    //open the original file in writing mode

        if (fp == NULL) 
        {
            FILE_ERROR(fpc);
            return 2;
        }

       
        fprintf(fp, "%d\n", new_num); //print the updated number of contacts 

       
        ftemp = fopen("temp.csv", "r"); //open the temporary file in reading mode

        //copy the cntacts from the temporary file to the original file
        while (fscanf(ftemp, "%[^,],%[^,],%[^,],%[^\n]\n", cont.name, cont.phNo, cont.emailId, cont.address) == 4) 
        {
            fprintf(fp, "%s,%s,%s,%s\n", cont.name, cont.phNo, cont.emailId, cont.address);
        }

       
        fclose(fp);
        fclose(ftemp);
       
        remove("temp.csv");     //remove the temporarily created file

        printf("Contact successfully deleted.\n");
    } 
    else //if the uder entered contactis not present in the file display contact not found
    {
        printf("Contact not found.\n");
        remove("temp.csv");  
    }

    return 1;
}


