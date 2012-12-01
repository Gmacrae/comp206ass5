#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//main function
int main(void) {
	
	char *data = getenv("QUERY_STRING");

	//stores the username and password input from the user
	char *user;
	char *pass;

	//stores the command that will be passed to the system() function
	char command[150];

	//stores the status of the system() function
	int status;

	//greet user and ask for credentials
//	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
//	printf("<html><head><title>Login</title></head>");	
//	printf("<body>Welcome to the login page for Python Pearls ++. ");
//	printf("Enter your credentials below.<p>");	
//	printf("<form name=\"input\" action=\"login.cgi\" method=\"get\">");
//	printf("User name: <input type=\"text\" name=\"username\"><br />");
//	printf("Password: &nbsp; <input type=\"password\" name=\"password\"><br />");
//	printf("<input type=\"submit\" value=\"Login\"></form></body></html>");
	
	//char *data = getenv("QUEREY_STRING");
	
//	if(data == NULL) {
//		printf("\nUnable to read QUEREY_STRING\n");
//		exit(EXIT_FAILURE);
//	}
	
	sscanf(data, "username=%s", user);
	sscanf(data, "password=%s", pass);

	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("<br/>username is :%s<br/>", user);
	printf("<br/>password is :%s<br/>", pass);


	//add the username and password to a string. 
//	sprintf(command,"./passweb.cgi -verify %s %s", username, password);	

	//use that string as a series of commands for the command line,
	//accessed using system().	
//	status = system(command);	

	//if the exit status of passweb was EXIT_FAILURE (1)
/*	if (WEXITSTATUS(status)) {
		printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
		printf("<html>");		
		printf("<a href=\"http://www.cs.mcgill.ca/~parauj2/homepage/error\" target=\"_blank\">HOME<a><br />");
printf("<a href=\"http://www.cs.mcgill.ca/~parauj2/homepage/homepage\" >HOME<a><br/>");
		printf("</html>");
		exit(EXIT_FAILURE);
	} 
	
	//else the exit status must have been EXIT_SUCCESS
	else {
		printf("Valid!\n");
		exit(EXIT_SUCCESS);
	}*/

} 
