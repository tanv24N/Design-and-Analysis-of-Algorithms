/*
Name: Tanvi Ninawe
BNumber: B01023357
*/

#include <stdio.h>
#include <string.h>

#define MAX 1024

int n, m;
char X[MAX];
char Y[MAX];
int matLCS[MAX][MAX];

//Function to find the maximum between two input
int max(int a, int b) {
    return (a > b) ? a : b;
}

//Function to calculate the LCS
int calculateLCS() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                matLCS[i][j] = 1 + matLCS[i - 1][j - 1];
            } else {
                matLCS[i][j] = max(matLCS[i][j - 1], matLCS[i - 1][j]);
            }
        }
    }																																																																																																																																																																																																																																																																																															
	return matLCS[n][m];
}

//Function to create Subsequence
void createSubseq() {
    int i = n, j = m;
    int lcsLength = matLCS[n][m];
    char lcs[lcsLength + 1]; 
    lcs[lcsLength] = '\0';

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[lcsLength - 1] = X[i - 1];
            i--;
            j--;
            lcsLength--;
        } else if (matLCS[i - 1][j] > matLCS[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("LCS: %s\n", lcs);
}

int main(int argc, char* argv[]) {
    //Check number of commad line arguments
    if (argc != 3) {
        printf("Usage: %s <string1> <string2>\n", argv[0]);
        return 1;
    }

    char* str1 = argv[1];
    char* str2 = argv[2];
    m = strlen(str1);
    n = strlen(str2);

    //Copy input strings to character arrays
    strcpy(X, str2);
    strcpy(Y, str1);
    
    //Calculate length of LCS
    calculateLCS();
	printf("Length of the string : %d\n", calculateLCS());
    createSubseq();

    return 0;
}
