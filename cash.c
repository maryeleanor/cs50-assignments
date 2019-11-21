#include <cs50.h>
#include <stdio.h>
#include <math.h>

// get float for how much change is owed
// if neg # is given, ask again
float get_change(string prompt)
{
    float n;
    do
    {
       n = get_float("%s", prompt);
    }
    while (n < 0);
    return n;
}

//cycle through the coins deducting the changeAmt
int numCoins(int cents) {
   
     int q = cents/25;
     cents = cents-(25*q);
    
     int d = cents/10;
     cents = cents-(10*d);
    
     int n = cents/5;
     cents = cents-(5*n);
    
     int p = cents;
    
    return(q+d+n+p);
}

int main(void)
{
    //run get_change and make sure to get positive float
    float change = get_change("Change owed: ");
    //round changeAmt to dollars
    int myCents = round(change * 100);
    //run numCoins to cycle through quarters, dimes, nickels, and pennies
    int coins = numCoins(myCents);
    //print the number of coins we should get back
    printf("I would give you this many coins:\n");
    printf("%i\n", coins);
    
}
    


