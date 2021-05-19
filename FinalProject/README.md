# Final Project
This final projects implements a software solution consisting of shell scripts and a C program to compute the lab attendance associated with students attending the class (on Zoom).\

## Part 1 : A Shell Script to Pre-process the Information in the CSV Files
This script searches through an input directory, gathers all files with format "lab-\*.csv", compiles the data and builds a consolidated CSV file that contains the records in a common format.\

The CSV files follow two specific formats : 

```
$ head -2 lab1/lab-A.csv
Name (Original Name),User Email, Total Durection(Minutes),Guest
Sophie Cao,sophie.cao@mail.mcgill.ca,65,No
```
<br>
```
$head -2 lab5/Lab-A.csv
Name (Original Name),User Email,Join Time,Leave Time,Duration (Minutes),Guest
Sophie Cao,sophie.cao@mail.mcgill.ca,01/21/2021 08:58:30 PM,01/21/2021 10:17:06 PM,78,No
```

The script takes two arguments, one input directory and one output CSV file. This output should be :

```
$ head -1 /data/labdata.csv
User Email,Name (Original Name),Lab,Total Duration (Minutes)
sophie.cao@mail.mcgill.ca,Sophie Cao,G,58
```

## Part 2 : A C Program to Compute the Attendance
This program computes the attendance associated with each student. It processes the duration of each lab for each student, taking into consideration that a given student may have multiple records for a single lab. 
Student records are kept in an alphabetical order using a linked list. If a student does not have a zoom record for a particular lab, then it is recorded as 0 duration.\

The output file should look like this :

```
User Email,Name (Original Name),A,B,C,D,E,F,G,H,U,Attendance (Percentage)
adeline.larsen@mail.mcgill.ca,Adeline Larsen,62,57,0,0,45,51,58,60,60,77.78
...
sophie.cao@mail.mcgill.ca,Sophie Cao,65,58,57,64,43,50,53,60,59,88.89
...
```

The last column represents the number of labs where the student spent 45 minutes or more in percentage.

* __zoomrecs.c__ reads through the input file, searches for the student in the linked list using their email as the search attribute. If found, it increments the duration appropriately. If not, it creates a record for the student. Once the task completed, the program reads through the linked list and writes the data to the ouput file.
* __labapp.c__ contains the main of the program. It calls the needed functions.
* A proper ```makefile``` is used to compile the C program.

## Part 3 : A Shell Script to Convert CSV to HTML
This script converts the input CSV file into an HTML format using Unix commands. The script only makes use of ```sed``` commands.
