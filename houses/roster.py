import csv
import cs50
from sys import argv


# check command line args
if len(argv) != 2:
    print("Usage: roster.py [house name]")


# open students db file vwith SQLite
db = cs50.SQL("sqlite:///students.db")

houseName = argv[1]

result = db.execute("SELECT * FROM students WHERE house LIKE ? ORDER BY last,first", houseName)

for row in result:
    
    first = row["first"]
    middle = row["middle"]
    last = row["last"]
    birth = row["birth"]
    
    if middle == None:
        print(f"{first} {last}, born {birth}")
    else:
        print(f"{first} {middle} {last}, born {birth}")    
