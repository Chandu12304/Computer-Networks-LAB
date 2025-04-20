#include <stdio.h>
#include <math.h>

// Function declarations
void genhamcode();
void makeerror();
void correcterror();

int h[12]; // Array for storing the codeword

int main() {
    int i, ch;

    // Input the message bits
    printf("\nEnter the message in bits:\n");
    for (i = 1; i < 12; i++) {
        if (i == 3 || i == 5 || i == 6 || i == 7 || i == 9 || i == 10 || i == 11) {
            scanf("%d", &h[i]);
        }
    }

    // Display the input message bits
    printf("\nInput message bits are:\n");
    for (i = 1; i < 12; i++) {
        printf("%d", h[i]);
    }

    // Generate the Hamming code
    genhamcode();

    // Ask the user if they want to introduce an error
    printf("\nDo you want to make an error (0 or 1)?\n");
    scanf("%d", &ch);
    if (ch) {
        makeerror();
        correcterror();
    } else {
        printf("\nNo error introduced.");
    }

    return 0;
}

// Function to generate the Hamming code
void genhamcode() {
    int temp, i;

    // Calculate parity bits
    temp = h[3] + h[5] + h[7] + h[9] + h[11];
    h[1] = (temp % 2 != 0) ? 1 : 0;

    temp = h[3] + h[6] + h[7] + h[10] + h[11];
    h[2] = (temp % 2 != 0) ? 1 : 0;

    temp = h[5] + h[6] + h[7];
    h[4] = (temp % 2 != 0) ? 1 : 0;

    temp = h[9] + h[10] + h[11];
    h[8] = (temp % 2 != 0) ? 1 : 0;

    // Display the transmitted codeword
    printf("\nTransmitted codeword is:\n");
    for (i = 1; i < 12; i++) {
        printf(" %d ", h[i]);
    }
}

// Function to introduce an error in the codeword
void makeerror() {
    int pos, i;

    printf("\nEnter the position where you want to introduce an error:\n");
    scanf("%d", &pos);

    // Flip the bit at the specified position
    h[pos] = (h[pos] == 1) ? 0 : 1;

    // Display the codeword with the error
    printf("\nError occurred, and the error codeword is:\n");
    for (i = 1; i < 12; i++) {
        printf(" %d ", h[i]);
    }
}

// Function to correct the error in the codeword
void correcterror() {
    int r1, r2, r4, r8, i, errpos;

    // Calculate the error position using parity bits
    r1 = (h[1] + h[3] + h[5] + h[7] + h[9] + h[11]) % 2;
    r2 = (h[2] + h[3] + h[6] + h[7] + h[10] + h[11]) % 2;
    r4 = (h[4] + h[5] + h[6] + h[7]) % 2;
    r8 = (h[8] + h[9] + h[10] + h[11]) % 2;

    // Calculate the error position
    errpos = r8 * 8 + r4 * 4 + r2 * 2 + r1 * 1;

    printf("\nError occurred at position %d\n", errpos);
    printf("\n\n............ Correction starts now ............\n");

    // Correct the error
    h[errpos] = (h[errpos] == 1) ? 0 : 1;

    // Display the corrected codeword
    printf("\nOriginal codeword is:\n");
    for (i = 1; i < 12; i++) {
        printf(" %d ", h[i]);
    }
}