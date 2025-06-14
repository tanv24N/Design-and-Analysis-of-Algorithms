#include <stdio.h>
#include <stdlib.h>

struct Item {
    char name[10];
    int weight;
    int profit;
};

// Function to compare items based on their benefit per unit weight
int compare(const void *a, const void *b) {
    double ratio1 = ((struct Item*)a)->profit / (double)((struct Item*)a)->weight;
    double ratio2 = ((struct Item*)b)->profit / (double)((struct Item*)b)->weight;
    return (ratio2 > ratio1) ? 1 : -1;
}

// Function to solve 0/1 knapsack using greedy approach
void knapsackGreedy(struct Item items[], int n, int capacity) {
    // Sort items based on benefit per unit weight
    qsort(items, n, sizeof(struct Item), compare);

    FILE *outputFile = fopen("output3.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening output file.\n");
        exit(EXIT_FAILURE);
    }

    int currentWeight = 0, totalProfit = 0;
    int selectedItems[n];
    int selectedWeights[n];
    int count = 0; // Counter for selected items

    // Iterate through sorted items and add them to the knapsack
    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= capacity) {
            currentWeight += items[i].weight;
            totalProfit += items[i].profit;

            // Save selected item and weight in arrays
            selectedItems[count] = items[i].profit;
            selectedWeights[count] = items[i].weight;
            count++;
        }
    }

    // Write results to the output file
    fprintf(outputFile, "%d %d %d\n",count, totalProfit, currentWeight);

    // Print selected items from the arrays
    for (int i = 0; i < count; i++) {
       // Print selected items from the arrays
        fprintf(outputFile, "%s %d %d\n",  items[i].name, selectedItems[i], selectedWeights[i]);
    }

    fclose(outputFile);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
         // Check for correct command-line arguments
        fprintf(stderr, "Usage: %s <input_filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open and read from the input file
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening input file.\n");
        return EXIT_FAILURE;
    }

    int n, capacity;
    fscanf(inputFile, "%d %d", &n, &capacity);

    struct Item items[n];

    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%s %d %d", items[i].name, &items[i].profit, &items[i].weight);
    }

    fclose(inputFile);

    // Call the greedy knapsack function
    knapsackGreedy(items, n, capacity);

    return EXIT_SUCCESS;
}
