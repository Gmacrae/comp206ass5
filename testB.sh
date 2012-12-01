#!/bin/sh

echo "Content-type:text/html\n\n"
#read parameter

theAge='echo "QUERY_STRING" | sed -n 's/^.*myAge=\([^&]*\).*$/\1/p' | sed "s/%20/ /g"'

# Output

theDays='expr $theAge *365'

echo "<html>"
echo "<head><title>The Answer</title></head>"
echo "<body>"
echo "Your age in days is $theDays<br>"
echo "</body>"
echo "</html>"
