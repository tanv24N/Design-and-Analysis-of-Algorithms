#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Item {
    char name[10];
    int weight;
    int profit;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

//int knapSack(int W, int wt[], int val[], int n);

// Function to compare items based on their benefit per unit weight
int compare(const void *a, const void *b) {
    double ratio1 = ((struct Item*)a)->profit / (double)((struct Item*)a)->weight;
    double ratio2 = ((struct Item*)b)->profit / (double)((struct Item*)b)->weight;
    return (ratio2 > ratio1) ? 1 : -1;
}
struct KnapsackResult {
    int maxValue;
    int totalWeight;
    int numSelectedItems;
    int selectedItems[100];
};


// Dynamic Programming function for the 0/1 Knapsack problem
/*int knapSack(int W, int wt[], int val[], int n) {
    int dp[W + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i < n + 1; i++) {
        for (int w = W; w >= 0; w--) {
            if (wt[i - 1] <= w)
                dp[w] = max(dp[w], dp[w - wt[i - 1]] + val[i - 1]);
        }
    }

    return dp[W];
}*/

struct KnapsackResult knapSack(int W, int wt[], int val[], int n) {
    // Making and initializing dp array
    int dp[W + 1];
    memset(dp, 0, sizeof(dp));

    int selected[n + 1][W + 1]; // 2D array to keep track of selected items
    memset(selected, 0, sizeof(selected));


    for (int i = 1; i < n + 1; i++) {
        for (int w = W; w >= 0; w--) {

            if (wt[i - 1] <= w) {

                // Finding the maximum value
                dp[w] = (dp[w] > dp[w - wt[i - 1]] + val[i - 1]) ? dp[w] : (dp[w - wt[i - 1]] + val[i - 1]);
                 selected[i][w] = 1;
            }
        }
    }
        // Extracting the total weight from the dp array
    int totalWeight = W;
    while (dp[totalWeight] == dp[totalWeight - 1]) {
        totalWeight--;
    }

    int numSelectedItems = 0;
    for (int i = 1; i <= n; i++) {
        if (selected[i][totalWeight]) {
            numSelectedItems++;
        }
    }

    // Creating and returning the result structure
    struct KnapsackResult result;
    result.maxValue = dp[W];
    result.totalWeight = totalWeight;
    result.numSelectedItems = numSelectedItems;

    int currentItem = n;
    int currentWeight = W;

    while (currentItem > 0 && currentWeight > 0) {
        if (selected[currentItem][currentWeight]) {
            result.selectedItems[currentItem - 1] = 1; // Mark item as selected
            currentWeight -= wt[currentItem - 1];
        }
        currentItem--;
    }

    return result;
}

// Function to solve 0/1 knapsack using dynamic programming
void knapsackDynamic(struct Item items[], int n, int capacity) {
    // Sort items based on benefit per unit weight
    qsort(items, n, sizeof(struct Item), compare);

    FILE *outputFile = fopen("output2.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening output file.\n");
        exit(EXIT_FAILURE);
    }

    int *wt, *val;
    wt = (int *)malloc(n * sizeof(int));
    val = (int *)malloc(n * sizeof(int));

    int totalWeightFilled = 0;
    int itemnum = 0;
    int totalWeightFilled_1 =0;

    for (int i = 0; i < n; i++) {
        wt[i] = items[i].weight;
        val[i] = items[i].profit;
    }
    
    for (int i = 0; i < n; i++) {
        if (wt[i] <= capacity) {
            //fprintf(outputFile, "%s %d %d\n", items[i].name, items[i].profit, items[i].weight);
            totalWeightFilled += wt[i];
            itemnum ++;
        }
    }

    //int totalProfit = knapSack(capacity, wt, val, n);
    struct KnapsackResult result = knapSack(capacity, wt, val, n);

    int x = sizeof(result.selectedItems);
    //int y = result.numSelectedItems;
    fprintf(outputFile, "%d %d %d\n", result.numSelectedItems, result.maxValue, result.totalWeight);

    for (int i = 0; i < x; i++) {
        if (wt[i] <= capacity) {
            fprintf(outputFile, "%s %d %d\n", items[i].name, items[i].profit, items[i].weight);
            totalWeightFilled_1 += wt[i];
        if (totalWeightFilled_1 == result.totalWeight)
        {
            break;
        }
        }
    }

    fclose(outputFile);
    free(wt);
    free(val);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

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

    knapsackDynamic(items, n, capacity);

    printf("Dynamic programming algorithm executed successfully. Check 'output2.txt' for results.\n");

    return EXIT_SUCCESS;
}
