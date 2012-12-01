//George Macrae
//260401458
//COMP206
//assignment 3
//2012

//include libraries and other c files.
#include<stdio.h>
#include<string.h>
#include<stdlib.h>



//add function: adds name password and type to password.csv
int add(char username[50], char password[50], char  type[50])
{
	FILE *pFile;
        char name[50];
	char pass[50];
	char t[50];

//open password.csv to readable
        pFile = fopen ("Members.csv" , "r");
        if (pFile == NULL)
        {   

           //	printf("\nCANT OPEN password.csv!\n");
		return EXIT_FAILURE;
	
        }    
        else
        {   
                while(!feof(pFile))
                {   
                        fscanf(pFile, "%[^,], %[^,],%s\n", name, pass, t);
			if( strcmp(name,username)==0)
                        {   
                                fclose(pFile);
                                return EXIT_FAILURE;
                        }   
    
                } 
		fclose(pFile);
		pFile = fopen ("Members.csv" , "a");
		fprintf(pFile,"%s, %s, %s\n",username,password,type);	  
                fclose(pFile);
		return EXIT_SUCCESS;
        }
}
//Delete method, takes a username to delete as input
int del(char username[50])
{
	char name[50];
	char pass[50];
	char t[50];
	int p=0;
//opens password.csv
	FILE *pFile = fopen("Members.csv", "r");
		if (pFile == NULL ) {
		//	printf("Could not open file!");
			return EXIT_FAILURE;
		}
//creates a temperary file, password2.csv
	FILE *tFile = fopen("password2.csv", "w");
		if (tFile == NULL ) {
		//	printf("Could not open file!");
			return EXIT_FAILURE;
		}
	while (!feof(pFile)) {
		fscanf(pFile, "%[^,], %[^,],%s\n", name, pass, t);
			if (strcmp(name,username)) {
				fprintf(tFile, "%s, %s, %s\n", name, pass, t);
			}
			else{
				p=1;
			}
	}
	fclose(pFile);
	fclose(tFile);
	system("mv password2.csv Members.csv");
	if(p==1){
		return EXIT_SUCCESS;
	}
	else{
		return EXIT_FAILURE;
	}
}
//edit function takes in 6 inputs
//the first 3 are the name password and type that exist in password.csv you want to edit
//the next 3 are the name password and type you want to change the old into
int edit(char ousername[50], char opassword[50], char otype[50], char nuser[50],char npass[50] ,char ntype[50])
{
	if(verify(nuser, npass)==0)
	{
	//	printf("\nreplacement name exists already\n");
		return EXIT_FAILURE;
	}
	if(verify(ousername, opassword)==0)
	{
		if(del(ousername)==0)
		{
			if(add(nuser,npass,ntype)==0)
			{
				return EXIT_SUCCESS;
			}
			else
			{//if add doesnt work form some reason return failure
				return EXIT_FAILURE;
			}
		}
		else
		{//if delete doesnt work for some reason return failure
			return EXIT_FAILURE;
		}
	}
	else
	{//if username doesn't exist in password.csv return failure
		return EXIT_FAILURE;
	}
}
//verify checks if a username and password match a username and password in password.csv
int verify(char username[50], char password[50])
{
        FILE *pFile;
        char name[50];
        char pass[50];
        char type[50];
	
//open password.csv
        pFile = fopen ("Members.csv" , "r");
        if (pFile == NULL)
        {   
              //   perror("error opening file");
                 return EXIT_FAILURE;
        }    
        else
        {   
//scan password.csv
//if username and password matches the arguments, close the file and return success
                while(!feof(pFile))
                {   
                        fscanf(pFile, "%[^,], %[^,],%s\n", name, pass, type);
                        if( strcmp(name,username)==0 && strcmp(pass,password)==0)
                        {   
				fclose(pFile);
                                return EXIT_SUCCESS;
                        }   
    
                }   
        } 
//if not close password.csv and return failure
	fclose(pFile);
        return EXIT_FAILURE;

}
//main method
//takes number of arguments/switches entered in commandline and an array of the arguments/switches entered in commandline
int main(int argc, char *argv[])
{
	int success=2;
	FILE *File= fopen("Members.csv" , "r");

	if(File == NULL)
	{
		File= fopen("Members.csv" , "w");
	}
	fclose(File);

//error message describing proper syntax
	char *error="Syntax Error";
	
//	"<br/><center><b><font size=\"10\">Syntax Error!</b></font><br /><b>ALL</b> and <b>ONLY</b> the selected feilds must be filled!</center><br /><a href=\"http://www.cs.mcgill.ca/~gmacra/homepage\">HOME</a>";
        if(argc<3)
        {
              // printf("%s",error);
               return EXIT_FAILURE;
        }

	else if(*argv[1]!='-')
	{
		//printf("%s", error);
		return EXIT_FAILURE;
	}
	
	else
	{
	//-add switch
		 if(strcmp(argv[1],"-add")==0)	
		{
	//if there are not enough arguments, print error statement return EXIT_FAILURE)
	//else run the add function 
			if(argc<5)
			{
		//		printf("%s",error);
				return EXIT_FAILURE;
			}
			success=add(argv[2],argv[3],argv[4]);
		}
	//-del switch, similar to add switch
		else if(strcmp(argv[1],"-del")==0)
		{
			if(argc<3)
			{
		//		printf("%s",error);
				return EXIT_FAILURE;
			}

			success=del(argv[2]);
		}
	//-edit switch, similar to add switch
		else if(strcmp(argv[1],"-edit")==0)
		{
			if(argc<8)
                        {   
                  //              printf("%s",error);
                                return EXIT_FAILURE;
                        }   
			success=edit(argv[2],argv[3],argv[4],argv[5],argv[6],argv[7]);
		}
	//-verify switch, similar to add switch
		else if(strcmp(argv[1],"-verify")==0)
		{
			if(argc<4)
                        {   
                    //            printf("%s",error);
                                return EXIT_FAILURE;
                        }   
			success=verify(argv[2],argv[3]);
			
		}
		else
	//if a switch that doesn't exist is called the error message is displayed 
		{
//		printf("%s",error);
		return EXIT_FAILURE;
		}
	}
	//success is returned if there are syntax errors
	if(success==2){
	//	printf("error");
		return EXIT_FAILURE;
	}
	return success;
}

