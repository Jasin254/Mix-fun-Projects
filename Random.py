import random

num = random.randint(1, 100)
attempts = 0

print("I'm thinking of a number between 1 and 100. Can you guess what it is?")

while True:
    guess = int(input("Enter your guess: "))
    attempts += 1

    if guess < num:
        print("Too low! Try again.")
    elif guess > num:
        print("Too high! Try again.")
    else:
        print("Congratulations, you guessed the number in", attempts, "attempts!")
        break
