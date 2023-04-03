language = input("Welcome to our robot assistant!\nPlease select your language:\n1. English\n2. French\n3. Spanish\n4. German\n")

if language == "1":
    print("You have selected English.")
    # TODO: implement English language functionality
elif language == "2":
    print("Vous avez sélectionné le français.")
    # TODO: implement French language functionality
elif language == "3":
    print("Ha seleccionado español.")
    # TODO: implement Spanish language functionality
elif language == "4":
    print("Sie haben Deutsch ausgewählt.")
    # TODO: implement German language functionality
else:
    print("Invalid input. Please select a language from the options provided.")
    exit(1)
