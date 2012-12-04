#!/usr/local/bin/python

import cgi

def main():
	print "Content-type: text/html\n\n"
	form = cgi.FieldStorage() # parse query
	if form.has_key("myAge") and form["myAge"].value != "":
		
		print form
		print "<br />"
		Name = form["myName"]
		print "Hello "+Name.value+",<br />"
		
		theDays = form["myAge"].value 
		
		theDays = int(theDays)
		theDays = theDays *365
		
	
		print "<b> Your age in days is ",theDays, "<b/>"
	else:
		print"<h1>ERRROR! please enter your age.</h1>"

main()
