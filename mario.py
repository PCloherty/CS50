from cs50 import get_int

def main():
    height = 0
    while height < 1 or height > 8:
        height = get_int("please enter a number between 1 to 8\nHeight:")
    for levels in range(height):
        for space in range(height-levels-1):
            print(" ", end ="")
            space+=1
        for block in range(levels+1):
            print("#",end = "")
            block +=1
        print("  ",end ="")
        for block in range(levels+1):
            print("#",end="")
            block +=1
        print("")
main()