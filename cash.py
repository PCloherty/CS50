from cs50 import get_float


def cash_return():
    #initialise owed as an int
    owed = validate()
    owed = owed * 100
    coins = {"quarters": 0, "dimes": 0, "nickels": 0, "pennies": 0}
    if owed > 0:
        while owed >= 25:
            coins["quarters"] += 1
            owed = owed - 25
        while owed >= 10 :
            coins["dimes"] += 1
            owed = owed - 10
        while owed >= 5 :
            coins["nickels"] += 1
            owed = owed - 5
        while owed >= 1:
            coins["pennies"] += 1
            owed = owed - 1
    total = 0      
    for types in coins:
        total += coins[types]
        
    print(total)
    
    
def validate():
    while True:
        # while owed is not a float or is less than 0 ask again for input
        owed = get_float("How much change is owed(in decemal)?\nChange owed: ")
        if type(owed) == float and owed > 0:
            break
    return owed
    
cash_return()