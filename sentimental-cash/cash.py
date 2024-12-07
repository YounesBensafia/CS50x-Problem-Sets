
while True:
    try:
        change_owed = float(input("How much change is owed? "))
        if change_owed < 0:
            print("Negative number.")
        else:
            break
    except ValueError:
        print("Enter a valid number.")
cents = round(change_owed * 100)

quarters = 25
dimes = 10
nickels = 5
pennies = 1

num_quarters = cents // quarters
cents %= quarters

num_dimes = cents // dimes
cents %= dimes

num_nickels = cents // nickels
cents %= nickels

num_pennies = cents // pennies

total_coins = num_quarters + num_dimes + num_nickels + num_pennies

print(f"{total_coins}")
