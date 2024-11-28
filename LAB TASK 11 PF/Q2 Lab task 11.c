#include <stdio.h>
#include <stdlib.h>
int main() {
    FILE *inputFile = fopen("document.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Could not open the file 'document.txt'.\n"); 
        return 1; 
    }

    char buffer[1024];
    int currentLine = 1;
    while (fgets(buffer, sizeof(buffer), inputFile)) {
        printf("%d: %s", currentLine++, buffer);
    }

    fclose(inputFile); 
    return 0;
}

