#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function to solve the knapsack problem using brute force
void bruteForce(char *filename, char *outputFilename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }

    // Read the number of items (n) and the knapsack capacity from the file
    int n, capacity;
    fscanf(file, "%d %d", &n, &capacity);

    // Allocate memory for arrays to store profits and weights of items
    int *profits = (int *)malloc(n * sizeof(int));
    int *weights = (int *)malloc(n * sizeof(int));

    // Read the profits and weights of items from the file
    for (int i = 0; i < n; i++) {
        char itemName[10];
        fscanf(file, "%s %d %d", itemName, &profits[i], &weights[i]);
    }

    fclose(file);

    // Initialize variables to track the best solution
    int maxProfit = 0;
    int totalWeight = 0;
    int *selectedItems = (int *)malloc(n * sizeof(int));
    int *bestSelectedItems = (int *)malloc(n * sizeof(int));
    int selectedItemsCount = 0;

    // Iterate through all possible subsets of items
    for (int i = 0; i < (1 << n); i++) {
        int currentProfit = 0;
        int currentWeight = 0;

        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) != 0) {
                currentProfit += profits[j];
                currentWeight += weights[j];
                selectedItems[j] = 1;
            } else {
                selectedItems[j] = 0;
            }
        }

        // Update the best solution if the current subset is valid and improves the result
        if (currentWeight <= capacity && currentProfit > maxProfit) {
            maxProfit = currentProfit;
            totalWeight = currentWeight;
            memcpy(bestSelectedItems, selectedItems, n * sizeof(int));
        }
    }

    // Count the number of selected items
    for (int i = 0; i < n; i++) {
        if (bestSelectedItems[i] == 1) {
            selectedItemsCount++;
        }
    }

    FILE *outputFile = fopen(outputFilename, "w");
    // Write the selected items to the output file
    fprintf(outputFile, "%d %d %d\n", selectedItemsCount, maxProfit, totalWeight);

    for (int i = 0; i < n; i++) {
        if (bestSelectedItems[i] == 1) {
            fprintf(outputFile, "Item%d %d %d\n", i + 1, profits[i], weights[i]);
        }
    }

    fclose(outputFile);

    free(profits);
    free(weights);
    free(selectedItems);
    free(bestSelectedItems);
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_filename>\n", argv[0]);
        return 1;
    }

    char *outputFilename = "output1.txt";
  
     // Call the brute force function to solve the knapsack problem
    bruteForce(argv[1], outputFilename);

    return 0;
}