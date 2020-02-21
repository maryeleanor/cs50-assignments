import csv
import cs50
from sys import argv


# check command line args
if len(argv) != 2:
    print("Usage: houses.py [csv file]")


# open students db file vwith SQLite
db = cs50.SQL("sqlite:///students.db")

# create table in students.db
# db.execute("CREATE TABLE students (first TEXT,middle TEXT,last TEXT,house TEXT,birth NUMERIC)")

# open csv
with open(argv[1], "r") as characters:

    # create Dictreader
    reader = csv.DictReader(characters)

    for row in reader:

        fullName = row["name"]
        house = row["house"]
        birth = row["birth"]

        # use split to check name strings for middle name
        name = fullName.split(" ")

        if len(name) == 3:
            first = name[0]
            middle = name[1]
            last = name[2]

        else:
            first = name[0]
            middle = None
            last = name[1]

        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)", first, middle, last, house, birth)

