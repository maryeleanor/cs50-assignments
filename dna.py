
import re
import csv
from sys import argv


def main():
    if len(argv) != 3:
        print("Usage: dna.py [csv file] [DNA sequence txt file]")

    # open CSV file and write to list
    file = open(argv[1], "r")
    csv_file = csv.reader(file)
    row = next(csv_file)

    # open txt and write to memory
    text = open(argv[2], "r")
    sequence = text.read()

    # create lists for STR counts and potential match
    STR_counts = [0]*(len(row)-1)
    match = [0]*(len(row)-1)

    # run functions
    dna_count(row, sequence, STR_counts)
    dna_match = compare(row, csv_file, STR_counts, match)
    print(dna_match)

    # close files
    file.close()
    text.close()


# iterate through DNA and count sequence occurences
def dna_count(row, sequence, STR_counts):

    for i in range(1, len(row)):
        substring = row[i]
        cursor = 0
        counter = 0
        max = 0

        # s[i:j] in python takes the string s, and returns the substring with all of the characters from i'th character up to (but not including) the j'th
        # for each STR, compute the longest run of consecuutive repeats in the DNA sequence
        while(cursor+len(substring) <= len(sequence)):
            if(sequence[cursor:cursor+len(substring)] == substring):
                counter += 1
                cursor = cursor+len(substring)
                if(max < counter):
                    max = counter
            else:
                counter = 0
                cursor += 1

        STR_counts[i-1] = max
    return STR_counts


# compare the STR couunts against each row in the CSV file
def compare(row, csv_file, STR_counts, match):
    for row in csv_file:
        for j in range(1, len(row)):
            match[j-1] = int(row[j])

        if(match == STR_counts):
            dna_match = row[0]
#            print(match)
            return dna_match

    dna_match = "No Match"
    return dna_match


main()