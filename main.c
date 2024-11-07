/*
NAME : PRAVEEN B R
DESCRIPTION : ADDRESSBOOK PROJECT 
*/


#include "addressbook.h"

int main(int argc, char *argv[])
{
    //check the required number of CLA's are passed
	if(argc == 2)		
    {
		printf("ADDRESS BOOK\n");
	        
		if( strcmp(strstr(argv[1] , "." ), ".csv") == 0)       //to check .csv file is passed, if not ask user to pass .csv file     
        {  
            FILE *f = fopen(argv[1] , "r" );   //open the file in reading mode
            char res;                       //variable to hold the yes /no option passed by user to continue

            if(f == NULL)
            {
                printf("file %s not present in directory\n", argv[1]); //if file is not present in directory  print error
                return 0;
            }
            
            fclose(f);

		do
		{
			
			char *fpc = argv[1];   //file pointer for the input file

			//to display options to user
			printf("select options:\n1. Add a contact\n2. Search a contact\n3. Edit a contact\n4. Delete a contact\n5. print all users\n6. Exit application\n"); 
		
			//user response
			printf("enter your option: ");
			int option;
			scanf("%d", &option);
		    
            					
			switch(option)
			{
				case 1:     //if user chooses to add a contact
						add_user(fpc);
						break;
				case 2:     //if user chooses to search a contact
						search_user(fpc);
						break;
				case 3:     //if user chooses to edit  a contact
						edit_user(fpc);
						break;
				case 4:     //if user chooses to delete a contact
						del_user(fpc);
						break;
				case 5:       //if user chooses to print the contacts
						print_user(fpc);
						break;
				case 6:        //if user chooses to exit
						exit(7);
						break;
				default:       //if user chooses an invalid option
                        INVALID_OPTION;
						break;
			}

			printf("do you want to continue? y/n: ");
			scanf("\n%c", &res);

		} while(res != 'n');        //loop until user passes 'n'

		return 0;
		}

		else          //if .csv file is not passed
        {
			printf("pass a file with .csv extension \n");
		}

	}
	else		//if required argument not passed
	{
        printf("error: please pass the file\n  try: ./a.out <filename>\n");	
        exit(1);
	}
}



