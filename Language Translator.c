#include <stdio.h>
#include <string.h>

int main() {
    char word[100];
    
    printf("Enter a word: ");
    scanf("%s", word);
    
    if (strcmp(word, "hello") == 0) {
        printf("Translation: Hola\n");
    } else if (strcmp(word, "goodbye") == 0) {
        printf("Translation: Adiós\n");
    } else if (strcmp(word, "thank you") == 0) {
        printf("Translation: Gracias\n");
    } else {
        printf("Translation not found.\n");
    }
    
    return 0;
}
