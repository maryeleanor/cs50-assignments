from cs50 import get_float


def main():
    
    # run function to prompt user for change owed
    change = get_change()
    
    # muultiply change by 100 to calculate 
    myCents = round(change*100)
    
    # run number of coins function to calculate 
    coins = numCoins(myCents)
    
    print(coins)


def get_change():
    while True:
        # promt user for Change owed
        change = get_float("Change owed: ")
        if change > 0:
            break
    return change


def numCoins(cents):
    
    # quarters
    q = int(cents/25)
    cents = cents-(25*q) 

    # dimes
    d = int(cents/10)
    cents = cents-(10*d)

    # nickels
    n = int(cents/5)
    cents = cents-(5*n)
    
    # no need to calculate pennies, as all cents left are pennies
    # return change 
    return(q+d+n+cents)


main()
