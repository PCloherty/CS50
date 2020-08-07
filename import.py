# TODO
from cs50 import SQL
import csv
from sys import argv,exit

if len(argv) != 2:
    print("not enough arguments, 'python import.py characters.csv'")
    exit()
db = SQL("sqlite:///students.db")    
csvFile = argv[1]    
    
with open(f"{csvFile}", "r") as characters:
    reader = csv.DictReader(characters)
    for row in reader:
        name = row["name"].split(" ")
        if len(name) != 3:
            name.insert(1,None)
        #print(name)
        db.execute('Insert into students (first, middle, last, house, birth) values(?,?,?,?,?)', name[0], name[1], name[2], row["house"], row["birth"]);
    
    


#db.execute("")
