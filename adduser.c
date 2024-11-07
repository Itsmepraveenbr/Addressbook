#include "addressbook.h"

int add_user(char *fpc)
{
    contacts cont,temp; //structures to hold the user entered contact and and one more used to loop and compare the enterd contact  detals with the existing contacts details

    int is_email_valid = 0;
    int at = 0; //to get the position of @ while validating emailId
    int dot = 0 ; //to get the position of . while validating emailId

    // Open the original file for reading
    FILE *fp = fopen(fpc, "r");

    if (fp == NULL) 
    {
        FILE_ERROR(fpc);    // If can't open file
        return 2;
    }

    // Open a temporary file for writing
    FILE *ftemp = fopen("temp.csv", "w+");
    
    if (ftemp == NULL) 
    {
        printf("Could not open temporary file.\n");
        fclose(fp);
        return 2;
    }

    // Read the number of contacts from the original file
    int num = 0;
    fscanf(fp, "%d\n", &num);  


    // Input new contact details
    printf("Enter name: ");
    scanf("\n%[^\n]", cont.name);
    printf("Enter phone no: ");

    //validate the phone number
    while(1)
    {
       scanf("%s",cont.phNo);
        
        if((strlen(cont.phNo) == 10))
        {        
            for(int i = 0 ; i <10 ; i++)
            {
                if(!isdigit( cont.phNo[i]))
                {
                    printf("enter a valid 10 digit number\n");
                    break;  //to come out of internal loop
                }
            }

            break;  //to come out of the external loop
        }
        else
        {
            printf("Enter a valid 10 digit number\n");
        }

    }       
   
    printf("Enter email id: ");
    
    //validate the emailId
    while(1)
    { 
        scanf("%s", cont.emailId);
    
        for(int i = 0 ; i < strlen(cont.emailId) ; i++)
        {
            if((cont.emailId[i] == '@'))          
            {
                is_email_valid++;   
                at = i;          
            }         
            else if(cont.emailId[i] == '.') 
            {
                is_email_valid++;
                dot = i;
            }  
        }
             
        if((is_email_valid >= 2) && (at < dot))
        {
            break;
        }
        else
        {
            is_email_valid = 0;
            printf("Enter a valid emailId \n ");
        }
       
    }
    printf("Enter address: ");
    scanf("\n%[^\n]", cont.address);


    //  Check for duplicate contacts in the file
    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n", temp.name, temp.phNo, temp.emailId, temp.address) == 4) 
    {
        if (strcmp(temp.phNo, cont.phNo) == 0 || strcmp(temp.emailId, cont.emailId) == 0)   //if a contact with the entered emailID or phone no is present print duplicste contact
        {
            printf("Duplicate contact found (Phone or Email already exists).\n");
            fclose(fp);
            fclose(ftemp);
            return 0;
        }
        // Write the current contact to the temporary file
        fprintf(ftemp, "%s,%s,%s,%s\n", temp.name, temp.phNo, temp.emailId, temp.address);
    }

    // if duplicate of the entered contact is not found  Add the new contact to the temporary file
    fprintf(ftemp, "%s,%s,%s,%s\n", cont.name, cont.phNo, cont.emailId, cont.address);

    num++;  //increment the count of contacts
   
    fclose(fp);

    // Reopen the original file in write mode to overwrite it with updated data
    fp = fopen(fpc, "w");

    if (fp == NULL) 
    {
        FILE_ERROR(fpc);
        fclose(ftemp);
        return 2;
    }

    fprintf(fp, "%d\n", num);
  
    rewind(ftemp);   //to make the temporary file pointer to pointr at starting of file

    //copy the contacts from the temporary file to the original file
    while (fscanf(ftemp, "%[^,],%[^,],%[^,],%[^\n]\n", cont.name, cont.phNo, cont.emailId, cont.address) == 4) 
    {
        fprintf(fp, "%s,%s,%s,%s\n", cont.name, cont.phNo, cont.emailId, cont.address);
    }

   
    fclose(fp);        
    fclose(ftemp);

   
    remove("temp.csv");     //remove the temporarily created file

    printf("Contact details successfully added.\n");
    return 0;
}

