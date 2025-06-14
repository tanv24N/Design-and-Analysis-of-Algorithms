#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random integer in a given range
int generateRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

char* generateRandomString(int i, int profit, int weight) {
    // Assuming a reasonable upper limit for the string length
    // Adjust the size as needed
    char* buffer = (char*)malloc(50 * sizeof(char));
    if (buffer == NULL) {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    snprintf(buffer, 50, "\nItem%d %d %d", i, profit, weight);

    return buffer;
}

// Function to create the 0/1 Knapsack problem and write it to a file
void createKnapsack(char *filename) {
    FILE *file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }

    // Seed for random number generation
    srand(time(NULL));
int x=10;
char** outputStrings = (char**)malloc(x * sizeof(char*));
    if (outputStrings == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Generate the number of items (n) between 5 and 10
    int n = generateRandom(5, 10);
    //fprintf(file, "%d ", n);

    // Create a list of n items
    int totalWeight = 0;

    for (int i = 1; i <= n; i++) {
        int profit = generateRandom(10, 30);
        int weight = generateRandom(5, 20);

        //fprintf(file, "\nItem%d %d %d", i, profit, weight);
        outputStrings[i - 1] = generateRandomString(i, profit, weight);


        totalWeight += weight;
    }

    // Set the capacity of the knapsack (W = floor(0.6 * ∑ wi from i=1 to n))
    int capacity = totalWeight * 0.6;
    fprintf(file, "%d  %d",n , capacity);

     for (int i = 0; i < n; i++) {
        fprintf(file, "%s", outputStrings[i]);

        // Free the allocated memory for each string
        free(outputStrings[i]);
    }

    fclose(file);
}
//Main function
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <output_filename>\n", argv[0]);
        return 1;
    }

    createKnapsack(argv[1]);

    return 0;
}
