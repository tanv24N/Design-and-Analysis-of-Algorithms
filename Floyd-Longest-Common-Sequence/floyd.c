/*
Name: Tanvi Ninawe
BNumber: B01023357
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function to create a matrix from the input file
int **CreateMatrix(FILE *file, int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                fprintf(stderr, "Error reading matrix elements.\n");
                exit(1);
            }
        }
    }
    return matrix;
}

//Function to print all pair shortest path for all vertices
void allPairShortestPath(int n, int D[n][n], int P[n][n], FILE *outputFile) {
     int nextValues[n][n]; // Array to store next values
    int pathArray[n][n][n]; // Array to store paths

    for (int u = 0; u < n; u++) {
        fprintf(outputFile, "\nV%d-Vj: shortest path and length\n", u + 1);
        for (int v = 0; v < n; v++) {
            if (u == v) {
                fprintf(outputFile, "V%d V%d : 0\n", u + 1, v + 1);
            } else {

                nextValues[u][v] = P[u][v]; // Save next value in the array

                int next = P[u][v];
                int pathLength = 0;

                // Store the path in the array
                pathArray[u][v][pathLength++] = u + 1;
                while (next != v) {
                    pathArray[u][v][pathLength++] = next + 1;
                    next = P[next][v];
                }
                pathArray[u][v][pathLength++] = v + 1;

                // Print the path
                fprintf(outputFile, "V%d", u + 1);
                for (int i = 1; i < pathLength; i++) {
                    fprintf(outputFile, " V%d", pathArray[u][v][i]);
                }
                fprintf(outputFile, " : %d", D[u][v]);

                fprintf(outputFile, "\n");
            }
        }
    }
}

//Floyd's algorithm 
void floydAlgo(int n, int D[n][n], int P[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            P[i][j] = j;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (D[i][j] > D[k][j] + D[i][k]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k;
                }
                else
                {
                    D[i][j] = D[i][j];
                }
            }
        }
    }
}

//Main function
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    //Open the input file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error in opening input file.\n");
        return 1;
    }
    //Open the output file
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error in opening output file.\n");
        return 1;
    }

    //Initilaize matrixNumber and n to keep count of Problem number and number of vertices
    int matrixNumber = 0;
    int n;
    char line[1024];

    //Read the input file line by line
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Problem") != NULL) {
            if (matrixNumber > 0) {
                fprintf(outputFile, "\n");
            }
            matrixNumber++;
            fprintf(outputFile, "%s", line);

            if (strstr(line, "n =") != NULL) {
                sscanf(line, "Problem %d: n = %d", &matrixNumber, &n);
            }
            //Initilaize matrix 
            int **matrix = CreateMatrix(file, n);
            int D[n][n];  
            int P[n][n];
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					D[i][j] = matrix[i][j];
				}
            }
            //Call Floyd algorithm function
            floydAlgo(n, D, P);

            //Print the Path matrix in output file
            fprintf(outputFile, "P matrix:\n");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    fprintf(outputFile, "%d  ", P[i][j] + 1); 
                }
                fprintf(outputFile, "\n");
            }
            //Call All pair shortest path function and print shortest Paths and length
            allPairShortestPath(n, D, P, outputFile);
        }
    }
    //Close the input and output file
    fclose(file);
    fclose(outputFile);

    return 0;
}
