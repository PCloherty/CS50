# TODO
from cs50 import SQL
from sys import argv,exit


if len(argv) != 2:
    print("not enough arguments, 'python import.py characters.csv'")
    exit()

db = SQL("sqlite:///students.db")

dict = db.execute('select first, middle, last, birth, house from students where house = ? order by last, first', argv[1]);
#print(dict)
for row in dict:
    
    if row["middle"] == None:
        print(f'{row["first"]} {row["last"]}, born {row["birth"]}')
    else:
        print(f'{row["first"]} {row["middle"]} {row["last"]}, born {row["birth"]}')
