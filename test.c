#include<stdlib.h>
#include<stdio.h>


int main(void)
{
	char *string = getenv("QUERY_STRING");
	int theAge, theDays;

	sscanf(string,"myAge=%s",&theAge);

	theDays= theAge *365; //without leap years

	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("<br /> Your age in days is :<v>%d</b><br/>", theDays);
}

