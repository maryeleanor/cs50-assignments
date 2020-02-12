from cs50 import get_int


def main():
    height = get_height()
    build(height)


def get_height():
    while True:
        # get size for pyramid from user
        height = get_int("Height: ")
        if 0 < height < 9:
            break
    return height
    
    
def build(height):
    row = 0
    spaces = height - 1
    
    for row in range(height):
        # print spaces
        for s in range(spaces, 0, -1):
            print(" ", end="")
        
        # blocks on the left    
        for b in range(row + 1):
            print("#", end="")
        
        # middle space    
        print("  ", end="")
       
        # blocks on the right
        for b in range(row + 1):
            print("#", end="")
            
        # take out space
        spaces -= 1
        # new line
        print()
        
         
main()