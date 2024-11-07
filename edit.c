#include "addressbook.h"

int edit_user(char *fpc)
{
    contacts cont;      //structure to hold the contact details
    char search_name[50];  //array to hold the name to be edited 
    int found = 0;       //variable to tell that the contact is present in the file

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
    printf("Enter name of the contact to edit: ");
    scanf("\n%[^\n]s", search_name);
    
    int serial_no = 0;
    int choice = 1;

    //to print the cotact matching with user input
    for(int i = 0 ; i < num ; i++)
    {
        fscanf(fp,"%[^,],%[^,],%[^,],%[^\n]\n", cont.name, cont.phNo, cont.emailId, cont.address);
        if(strcmp(cont.name, search_name) == 0)
         {
             printf("contact Found\n");
            printf("%d. %s, %s, %s, %s\n", ++serial_no, cont.name, cont.phNo, cont.emailId, cont.address);           
         }
     }
    
    //if multiple contacts are present asking the user to enter the serial no of the contact to edit
    if(serial_no > 1)
    {
       printf("Enter the serial number of the contact you want to edit\n");
       scanf("%d",&choice);

        //if user enters an invalid serial number ask user to enter a valid serial number
            while(choice < -1 || choice > serial_no)
            {
                printf("enter a valid choice\n");
                scanf("%d",&choice);
            }
    } 
       
       
   int new_num = 0;  //variable to hold the updated number of contacts
   
   // Rewind the file pointer
   rewind(fp);
   fscanf(fp,"%d\n",&num);
   serial_no = 0; 

   //editing the contact with given serial no by skipping other contacts
    for (int i = 0; i < num; i++) 
    {
        fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n", cont.name, cont.phNo, cont.emailId, cont.address);

        if (strcmp(cont.name, search_name) == 0) //if the name in file and the user entered name matches
        {
            serial_no++;
           if(choice == serial_no)   //if there are multiple contacts and the user entered serial number contact is found
           {
            printf("Edit the contact: %s, %s, %s, %s\n", cont.name, cont.phNo, cont.emailId, cont.address);      //display the existing details of the contact to be edited

            int edit_option;     //variable to hold the edit option
            printf("What would you like to edit?\n");
            printf("1. Name\n2. Phone Number\n3. Email ID\n4. Address\n"); //asking user what the wants to edit
            printf("Enter your option: ");
            scanf("%d", &edit_option);

           
            switch (edit_option) {
                case 1:     //if user wants to edit name
                    printf("Enter new name: ");
                    scanf("\n%[^\n]", cont.name);
                    break;
                case 2:    //if user wants to edit phone number
                    printf("Enter new phone number: ");
                    scanf("%s", cont.phNo);
                    break;
                case 3:     //if uder wants to edit emailid
                    printf("Enter new email ID: ");
                    scanf("%s", cont.emailId);
                    break;
                case 4:       //if user wants to edit address
                    printf("Enter new address: ");
                    scanf("%s", cont.address);
                    break;
                default:   //if user chooses an invalid option
                    INVALID_OPTION;
                    fclose(fp);
                    fclose(ftemp);
                    return 1;
            }
            }
            //printf("Contact details updated.\n");
            found = 1;  //if the user entered contact was found in the file make found =1
        }

        //printing the details to a temporary file
        fprintf(ftemp, "%s,%s,%s,%s\n", cont.name, cont.phNo, cont.emailId, cont.address);
        new_num++;  
    }

    
    fclose(fp);
    fclose(ftemp);

    //if the contact to be deleted is found
    if (found)
    {
       
        fp = fopen(fpc, "w"); //open the original file in writing mode
        if (fp == NULL) {
            FILE_ERROR(fpc);
            return 2;
        }

       
        fprintf(fp, "%d\n", new_num);  //print the updated number of contacts

       
        ftemp = fopen("temp.csv", "r");  //open the temporary file in reading mode

        //copy the cntacts from the temporary file to the original file
        while (fscanf(ftemp, "%[^,],%[^,],%[^,],%[^\n]\n", cont.name, cont.phNo, cont.emailId, cont.address) == 4) {
            fprintf(fp, "%s,%s,%s,%s\n", cont.name, cont.phNo, cont.emailId, cont.address);
        }

        
        fclose(fp);
        fclose(ftemp);

        
        remove("temp.csv");  //remove the temporarily created file

        printf("Contact successfully updated.\n");
    } 
    else   //if the uder entered contactis not present in the file display contact not found
    {
        printf("Contact not found.\n");
      
        remove("temp.csv");
    }

    return found; 
}

