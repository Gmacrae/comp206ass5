#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	printf("%s%c%c\n","Content-Type:text/html;charset= iso-8859-1",13,10);
	int n = atoi(getenv("CONTENT_LENGTH"));
	int x = 0;
	int i = 8; //8 for each character in username= (where u is 0 and = is 8)
	char inputArray[n];
	
	//initialize array to \0
	for(x=0;x<n;x++)
	{
		inputArray[x]='\0';
	}


	fgets(inputArray, n+1, stdin);


	//this if/while loop determines the number of character in username
	x=i+1;
	int u;
	//if nothing inputed for username make array size 0;
	if(inputArray[x] == '&' && inputArray[x+1] =='p')
	{	
		u=0;
	}
	else
	{

		while(inputArray[x] != '&' && inputArray[x+1] != 'p')
			{
				x++;
			}

		u=x-i-1;
	}
	printf("<br />");
	char username[u];
	//size of password	
	int y;

	y=n-u-19; //total char- (char in user)-19(8 for user 8 for pass 3 for ==&
//	printf("n=%d,y=%d,x=%d<br />",n,y,u);
	
		
	char password[y];
 	if(u==0 || y==0)
	{
		printf("MUST ENTER A USERNAME AND PASSWORD");
		printf("<br /><form><input type=\"button\" value =\"Back to Login \" onClick=\"history.go(-1);return true;\"></form><br>");
		printf("<form action=\"http://www.cs.mcgill.ca/~gmacra/homepage\"><input value=\"Homepage\" type=\"submit\"></form>");
		exit(EXIT_FAILURE);
	}
	sscanf(inputArray,"username=%[^&]&password=%s",username,password);

	printf("<br /> username:%s<br />password:%s <br />",username,password);

	verify(&username, &password);
	return 0;
}

int verify(char *user, char *pass)
{
//	printf("%s,%d,%d,%s",user,strlen(user),strlen(pass),pass);
	
	char u[strlen(user)];
	char p[strlen(pass)];
	char t[10];
 	FILE *pFile;
	char SYS[7]="SYSTEM";
	char USE[5]="USER";

	pFile =  fopen("Members.csv","r");
	if(pFile==NULL)
	{
		perror("couldn't open Members.csv");
		return EXIT_FAILURE;
	}
	else
	{
		while(!feof(pFile))
		{
			fscanf(pFile, "%[^,], %[^,],%s\n", u, p, t);
//			printf("<br/>%s,%s,%s<br />",u,p,t);
//			printf("%d,%d<br />",strcmp(u,user),strcmp(p,pass));

		
			if(strcmp(user,u)==0 && strcmp(pass,p)==0){
				fclose(pFile);
		//		char SYS[6];
//				printf("type =%s,SYS=%s,USE=%s,%d",t,SYS,USE,strcmp(t,SYS));
				if(!strcmp(t,USE) || !strcmp(t,SYS))
				{
					return(menu(&t));
				}
				else 
				{
					printf("<br /> undefined user type<br/>");
					return EXIT_FAILURE;
				}

				return EXIT_SUCCESS;
			}
		}
	}
	printf("<br />INCORRECT PASSWORD OR USERNAME ");
	printf("<a href=\"http://www.cs.mcgill.ca/~gmacra/homepage\"> HOME<a><br />");
	fclose(pFile);
	return EXIT_FAILURE;
	
}

int menu(char *type)
{

	char USER[5]="USER";
	char SYS[7]="SYSTEM";
	if(!strcmp(type,USER))
	{
		//printf("<br />%s<br />",type);
		printf("<html><head><title>User Menu</title></head>");
		printf("<body>Welcome to the user prefrences page for Python Pearls ++.<p>");
		printf("<form name=\"input\" action=\"menu.c\" method=\"get\">");
		printf("<input type=\"radio\" name=\"option\" value=\"C\">Change Password.<br>");
		printf("<input type=\"radio\" name=\"option\" value=\"H\">View Purchase History.<br>");
		printf("<a href=\"http://www.cs.mcgill.ca/~gmacra/homepage\">Return Home.</a><br>");
		printf("<input type=\"submit\" value=\"Login\"></form></body></html>");
		printf("<meta http-equiv=\"refresh\" content=\"0;URL=http://www.cs.mcgill.ca/~dwhitn/cgi-bin/userMenu.html\">");
		return EXIT_SUCCESS;
	}

	else if(!strcmp(type,SYS))
	{
		printf("<html>\n<head>\n<title>SYSTEM MENU</title><br /><center>Welcome to the SYSTEM MENU<br /> <br />");
		printf("</head>");
	
		printf("<body>\n <form name=\"input\" action=\"menu.cgi\" method=\"get\">");
		
		printf("<input type=\"hidden\" name=\"type\" value=\"SYSTEM\">");


		printf("<input type=\"radio\" name=\"opt\" value=\"a\" >ADD<br />");
		printf("Username<input type=\"text\"  name=\"user\">");
		printf("Password<input type=\"text\"  name=\"pass\">");
		printf("Type<input type=\"text\" name=\"type\">");

		printf("<br /><br /><input type=\"radio\" name=\"opt\" value=\"d\">DEL<br />");
		printf("Username<input type=\"text\" name=\"user\">");
		
		printf("<br /><br /><input type=\"radio\" name=\"opt\" value=\"e\">EDIT<br />");
		printf("Old Username<input type=\"text\" name=\"Ouser\">");
		printf("Old Password<input type=\"text\" name=\"Opass\">");
		printf("Old Type<input type=\"text\" name=\"Otype\">");
		printf("<br />New Username<input type=\"text\" name=\"Nuser\">");
		printf("New Password<input type=\"text\" name=\"Npass\">");
		printf("New Type<input type=\"text\" name=\"Ntype\">");


		printf("<br /><br/><input type=\"radio\" name=\"opt\" value=\"v\">VERIFY<br />");
		printf("Username<input type=\"text\" name=\"user\">");
		printf("Password<input type=\"text\" name=\"pass\">");

		printf("<br /><br /><input type=\"radio\" name=\"opt\" value=\"i\">Inventory<br />");
		//printf("<input type=\"hidden\" name=\"type\" value=\"SYSTEM\">");

		printf("<input type=\"submit\" value=\"Submit\">\n</form>\n</center></body></html>");
	
		printf("<a href=\"http://www.cs.mcgill.ca/~gmacra/homepage\">HOME</a><br />");
		



		return EXIT_SUCCESS;
		
	}
	else
	{
		perror("<br />ERROR IN DETECTING USER TYPE<br />");
		return EXIT_FAILURE;
	}
	return EXIT_FAILURE;
}
