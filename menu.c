#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);

	char *data = getenv("QUERY_STRING");
        if(data == NULL)
	{
		printf("Error, could not read from login.c");
		exit(EXIT_FAILURE);
	}
	char type[50];
	char SYS[10]="SYSTEM";
	char USE[10]="USE";
	sscanf(data,"type=%[^&]&", type);
	printf("%s,%s<br />",data,type);	
	
	if (!strcmp(type,SYS))
	{
		sys(data);
	}
	else if(!strcmp(type,USE))
	{
		user(data);
	}
	else
	{
		printf("UNDEFINED USER TYPE");
		exit(EXIT_FAILURE);
	}

}
int user(char *data)
{
	char option;
	char newpass[50];
	char user[50];
	char oldpass[50];
	char type[50] = "user";
	char command[150];
	sscanf(data,"user=%[^&]&oldpass=%[^&]&option=%c&newpass=%s", user, oldpass, &option, newpass);
	if(option == 'H') {
		printf("%s%c%c\n","Content-Type:text/html;charset= iso-8859-1",13,10);
		printf("<html>");	
		printf("<head><title>Purchases</title></head>");	
		printf("<body>Here is your purchase history.<br><br>");
		FILE *fp = fopen("log.csv", "r");
		if (fp == NULL ) {
			printf("Could not open file!<br><br>");
			return EXIT_FAILURE;
		}
		char username[50];
		char itemname[50];
		int itemcode;
		int quantity;
		float price;
		//printf("User from query_string = ^%s^ <br><br>", user);
		
		while(!feof(fp)){
			fscanf(fp, "%[^,], %[^,], %d, %d, %f\n", username, itemname, &itemcode, &quantity, &price);				
			if(strcmp(user, username) == 0) {
			printf("You purchased %d unit(s) of item %s (itemnumber: %d), at $%.2f each, for a total of $%.2f<br><br>", quantity, itemname, itemcode, (float) price/quantity, price);
			
			}
			
		}
		fclose(fp);	
		
		printf("<a href=\"http://www.cs.mcgill.ca/~parauj2/homepage\">HOME</a><br>");
		printf("<form><input type=\"button\" value =\"Back to menu\" onClick=\"history.go(-1);return true;\"></form><br>");
		printf("</body></html>");
		return(0);
		}
		else {
			sprintf(command,"./passweb.cgi -edit %s %s %s %s %s %s", user, oldpass, type, user, newpass, type);					

			int status = system(command);
			
			if(WEXITSTATUS(status)) {
				printf("%s%c%c\n","Content-Type:text/html;charset= iso-8859-1",13,10);
				printf("<html>");	
				printf("<head><title>Error!</title></head>");	
				printf("<body>Must select new password.<p>");
				
				//printf("User from query_string = ^%s^ <br><br>", user);
				
				printf("<a href=\"http://www.cs.mcgill.ca/~parauj2/homepage\">HOME</a><br>");
				printf("<form><input type=\"button\" value =\"Back to menu\" onClick=\"history.go(-1);return true;\"></form><br>");		
				printf("</body></html>");
				
				return(EXIT_FAILURE);
				}
				else {
					printf("%s%c%c\n","Content-Type:text/html;charset= iso-8859-1",13,10);
					printf("<html>");
					printf("<head><title>Success!</title></head>");	
					printf("<body>Password Changed!<p>");	
					
					//printf("User from query_string = ^%s^ <br><br>", user);
					
					printf("<a href=\"http://www.cs.mcgill.ca/~parauj2/homepage\">HOME</a><br>");
					printf("<form><input type=\"button\" value =\"Back to menu\" onClick=\"history.go(-1);return true;\"></form><br>");			
					printf("</body></html>");
					return(EXIT_SUCCESS);	
					}
			}
}

int sys(char *data)
{
	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
/*	char *data = getenv("QUERY_STRING");
	if(data == NULL)
	{
		printf("Error, could not read from login.c");
		exit(EXIT_FAILURE);
	}*/
	printf("%s",data);
	int len=strlen(data);
	int i=0;
	char opt='q';
	while(i<len-4)
	{
		if(data[i]=='o' && data[i+1]=='p' && data[i+2]=='t' && data[i+3]=='=')
		{
			opt=data[i+4];
			i=len;
		}
		else{
			i++;
		}
	}
	int success = (-1);
	if(opt=='a')
	{
			
		printf("<br />add");	
		char u[50];
		char p[50];
		char t[50];

		sscanf(data,"type=SYSTEM&opt=a&user=%[^&]&pass=%[^&]&type=%[^&]&user=&Ouser=&Opass=&Otype=&Nuser=&Npass=&Ntype=&user=&pass=",u,p,t);

		printf("<br />%s,%s,%s",u,p,t);
		if(strlen(u)==0 || strlen(p)==0 || strlen(t)==0)
		{
			printf("<br /> must fill in all fields");
			printf("<br /><form><input type=\"button\" value =\"Back to menu\" onClick=\"history.go(-1);return true;\"></form><br>");
			printf("<form action=\"http://www.cs.mcgill.ca/~gmacra/homepage\"><input value=\"Homepage\" type=\"submit\"></form>");
//			printf("<br /> <a href=\"http://www.cs.mcgill.ca/~gmacra/homepage\">HOME</a>");
			exit(EXIT_FAILURE);
		}

		char command[150];
		sprintf(command,"./passweb -add %s %s %s",u,p,t);
		success=system(command);
		printf("%d",success);
		if(!success)
		{
			printf("<br /> %s was successfully added to Members.csv!",u);
		}
		else if(success==256)
		{
			printf("<br /> Username %s already exists in Members.csv!",u);
		}
		else{
			printf("error in add!");
		}
	}
	else if(opt=='d')
	{
		printf("<br />del");
		char u[50];
//		char au[50],ap[50],at[50];
		sscanf(data,"type=SYSTEM&user=&pass=&type=&opt=d&user=%[^&]&Ouser=&Opass=&Otype=&Nuser=&Npass=&Ntype=&user=&pass=&type=",u);
		printf("<br />,%s",u);

		if(strlen(u)==0)
			{   
				printf("<br /> The delete feild must be filled");
				printf("<br /><form><input type=\"button\" value =\"Back to menu\" onClick=\"history.go(-1);return true;\"></form><br>");
				printf("<form action=\"http://www.cs.mcgill.ca/~gmacra/homepage\"><input value=\"Homepage\" type=\"submit\"></form>");

				exit(EXIT_FAILURE);
	                } 

		char command[150];
		sprintf(command,"./passweb -del %s",u);
		success=system(command);
		printf("<br />success=%d",success);
		if(!success)
		{
			printf("<br /> %s was successfully deleted from Members.csv!",u);
		}
		else if(success==256)
		{
			printf("<br /> %s could not be deleted (doesn't exist in Members.csv.",u);
		}
		else{
			printf("error in delete");
		}

	}
	else if(opt=='e')
	{
		printf("<br />edit");
	//	char u[50];
	//	char au[50],ap[50],at[50];
		char oU[50], oP[50], oT[50], nU[50], nP[50], nT[50];
		sscanf(data,"type=SYSTEM&user=&pass=&type=&user=&opt=e&Ouser=%[^&]&Opass=%[^&]&Otype=%[^&]&Nuser=%[^&]&Npass=%[^&]&Ntype=%[^&]&user=&pass=",oU,oP,oT,nU,nP,nT);
		printf("<br />%s,%s,%s,%s,%s,%s",oU,oP,oT,nU,nP,nT);
		
		if(strlen(oU)==0 || strlen(oP)==0 || strlen(oT)==0 || strlen(nU)==0 || strlen(nP)==0 || strlen(nT)==0 )
		{
			printf("<br /> must fill in all fields");
			printf("<br /><form><input type=\"button\" value =\"Back to menu\" onClick=\"history.go(-1);return true;\"></form><br>");
			printf("<form action=\"http://www.cs.mcgill.ca/~gmacra/homepage\"><input value=\"Homepage\" type=\"submit\"></form>");

			exit(EXIT_FAILURE);
		} 

		char command[150];
		sprintf(command,"./passweb -edit %s %s %s %s %s %s",oU,oP,oT,nU,nP,nT);
		success=system(command);
		if(!success)
		{
			printf("<br /> username:%s was changed to %s password:%s type:%s", oU,nU,nP,nT);
		}
		else if(success==256)
		{
			printf("<br /> could not find %s to edit or password enter incorrectly",oU);
		}
		else{
			printf("error in edit!");
		}

	}
	else if(opt=='v')
	{
		char uV[50],pV[50];
	//	char u[50];
	//	char au[50],ap[50],at[50];
	//	char oU[50], oP[50], oT[50], nU[50], nP[50], nT[50];

		printf("<br />verify");
		sscanf(data,"type=SYSTEM&user=&pass=&type=&user=&Ouser=&Opass=&Otype=&Nuser=&Npass=&Ntype=&opt=v&user=%[^&]&pass=%s",uV,pV);
		printf("<br />%s,%s",uV,pV);
		
		if(strlen(uV)==0 || strlen(pV)==0)
		{
			printf("<br /> must fill in all fields");
			printf("<br /><form><input type=\"button\" value =\"Back to menu\" onClick=\"history.go(-1);return true;\"></form><br>");
			printf("<form action=\"http://www.cs.mcgill.ca/~gmacra/homepage\"><input value=\"Homepage\" type=\"submit\"></form>");

			exit(EXIT_FAILURE);
		} 

		char command[150];
		sprintf(command,"./passweb -verify %s %s",uV,pV);
		success=system(command);

		if(!success)
		{
			printf("<br /> %s exists in Memebers.csv!",uV);
		}
		else if(success==256)
		{
			printf("<br /> %s does not exist in Memebers.csv!",uV);
		}

	}
	else if(opt=='i')
	{
		
		printf("<br />Inventory<br />");
		char id[100];
		char name[100];
		char des[100];
		char qua[100];
		char pur[100];
		FILE *pF;
		int i=1;
		pF= fopen("Inventory.csv","r");
		if(pF == NULL)
		{
			printf("CANT OPEN");
			exit(EXIT_FAILURE);

		}
		printf("<br /><br />");
		printf("<center><table border=\"25\">");
		printf("<tr><th></th><th>ID</th><th>Name</th><th>Description</th><th>Quantity</th><th>Price</th></tr>");
		while(!feof(pF))
		{
			fscanf(pF,"%[^,],%[^,],%[^,],%[^,],%s\n",id,name,des,qua,pur);
			
			printf("<tr><th>item %d</th><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>$%s.00</td>",i,id,name,des,qua,pur);
			i++;
		}
		printf("</center>");
		fclose(pF);
		printf("<br /><form><input type=\"button\" value =\"Back to menu\" onClick=\"history.go(-1);return true;\"></form><br>");
		printf("<form action=\"http://www.cs.mcgill.ca/~gmacra/homepage\"><input value=\"Homepage\" type=\"submit\"></form>");

		exit(EXIT_SUCCESS);
		
	}
	else
	{
		printf("ERROR");
		exit(EXIT_FAILURE);
	}


	FILE *pFile;
	char line[200];
	char line1[200];
	char line2[200];
	pFile = fopen ("Members.csv", "r");
	if(pFile == NULL)
	{
		printf("\nCANT OPEN");
		exit(EXIT_FAILURE);
	}
	printf("<br /><br />");
	while(!feof(pFile))
	{
		
		fscanf(pFile,"%[^,],%[^,],%s\n",line,line1,line2);
		printf("<br />%s,%s,%s", line,line1,line2);
	}
	fclose(pFile);
	
	printf("<br /><form><input type=\"button\" value =\"Back to menu\" onClick=\"history.go(-1);return true;\"></form><br>");
	printf("<form action=\"http://www.cs.mcgill.ca/~gmacra/homepage\"><input value=\"Homepage\" type=\"submit\"></form>");

	exit(0);

}
