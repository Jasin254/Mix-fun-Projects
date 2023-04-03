#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char language[10];
    
    printf("Welcome to our robot assistant!\n");
    printf("Please select your language:\n");
    printf("1. English\n");
    printf("2. French\n");
    printf("3. Spanish\n");
    printf("4. German\n");
    
    fgets(language, sizeof(language), stdin);
    language[strcspn(language, "\n")] = '\0'; // remove newline character
    
    if (strcmp(language, "1") == 0) {
        printf("You have selected English.\n");
        // TODO: implement English language functionality
    }
    else if (strcmp(language, "2") == 0) {
        printf("Vous avez sélectionné le français.\n");
        // TODO: implement French language functionality
    }
    else if (strcmp(language, "3") == 0) {
        printf("Ha seleccionado español.\n");
        // TODO: implement Spanish language functionality
    }
    else if (strcmp(language, "4") == 0) {
        printf("Sie haben Deutsch ausgewählt.\n");
        // TODO: implement German language functionality
    }
    else {
        printf("Invalid input. Please select a language from the options provided.\n");
        exit(1);
    }
    
    return 0;
}
