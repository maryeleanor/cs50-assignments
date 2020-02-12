
import re
from cs50 import get_string


def main():
    
    # prompt user for text
    text = get_string("Text: ")
    
    # run Grade function to calculate 
    theGrade = int(grade(text))
    
    if 1 < theGrade < 16:
        print(f"Grade {theGrade}")
    elif theGrade < 1:
        print("Before Grade 1")
    elif theGrade > 16:
        print("Grade 16+")
        

def grade(text):

    # count letters
    x = re.findall("[a-zA-Z]", text)
    letters = len(x)

    # count words
    words = re.split("\s", text)
    words = len(words)

    # count sentences
    sentences = re.split("[.!?]", text)
    sentences = len(sentences)-1

    # L is average # of letters per 100 words and S is the average # of sentences per 100 words
    L = (letters/words)*100
    S = (sentences/words)*100 
    
    # calculate grade
    grade = 0.0588 * L - 0.296 * S - 15.8
    grade = round(grade, 0)
    
    return grade


main()