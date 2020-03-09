#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void) 
{   

    //change as a float
    float changeOwed = get_float("How much change is owed(with decimal point)? ");
    //change as an int from the float
    int change = round(changeOwed * 100);

    //the amount of each coin
    int quarters =  0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;
    
    

    if (change > 0)
    {
        while (change >= 25) 
        {
            change = change - 25;
            quarters++;
        }
        while (change >= 10) 
        {
            change = change - 10;
            dimes++;
        }
        while (change >= 5) 
        {
            change = change - 5;
            nickels++;
        }
        while (change >= 1) 
        {
            change = change - 1;
            pennies++;
        }
        //list and quantity of coins
        int coins = quarters + dimes + nickels + pennies;
        printf("%d\n", coins);
    } 
    else 
    {
        main();
    }
}
