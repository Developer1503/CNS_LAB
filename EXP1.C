#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function to perform substitution encryption
void substitutionEncryption(char plaintext[], int key) {
    char ciphertext[100];
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        // Encrypt each letter with (P + K) % 26
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a' + key) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i];  // non-alphabet characters are unchanged
        }
    }
    ciphertext[i] = '\0';  // null terminate the ciphertext string
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext (Substitution): %s\n", ciphertext);
}

// Function to perform substitution decryption
void substitutionDecryption(char ciphertext[], int key) {
    char plaintext[100];
    int i;
    for (i = 0; i < strlen(ciphertext); i++) {
        // Decrypt each letter with (C - K) % 26
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key + 26) % 26) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - key + 26) % 26) + 'a';
        } else {
            plaintext[i] = ciphertext[i];  // non-alphabet characters are unchanged
        }
    }
    plaintext[i] = '\0';  // null terminate the plaintext string
    printf("Ciphertext: %s\n", ciphertext);
    printf("Plaintext (Substitution Decryption): %s\n", plaintext);
}

// Function to calculate factors of a number
void getFactors(int num, int* factors, int* factorCount) {
    *factorCount = 0;
    for (int i = 1; i <= num; i++) {
        if (num % i == 0) {
            factors[*factorCount] = i;
            (*factorCount)++;
        }
    }
}

// Function to perform transposition encryption
void transpositionEncryption(char plaintext[], int* factors, int factorCount) {
    int len = strlen(plaintext);
    for (int i = 0; i < factorCount; i++) {
        int rows = factors[i];
        int cols = len / rows;

        if (cols * rows != len) {
            continue; // Skip if the matrix cannot fit exactly
        }

        char matrix[rows][cols];
        int idx = 0;

        // Fill the matrix row by row
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (plaintext[idx] != '\0') {
                    matrix[r][c] = plaintext[idx++];
                } else {
                    matrix[r][c] = 'X'; // Fill the remaining cells with 'X'
                }
            }
        }

        printf("Matrix (%dx%d):\n", rows, cols);
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                printf("%c ", matrix[r][c]);
            }
            printf("\n");
        }

        // Read column by column to generate ciphertext
        char ciphertext[len + 1];
        idx = 0;
        for (int c = 0; c < cols; c++) {
            for (int r = 0; r < rows; r++) {
                ciphertext[idx++] = matrix[r][c];
            }
        }
        ciphertext[idx] = '\0';

        printf("Ciphertext (Transposition): %s\n", ciphertext);
    }
}

// Function to perform transposition decryption
void transpositionDecryption(char ciphertext[], int* factors, int factorCount) {
    int len = strlen(ciphertext);
    for (int i = 0; i < factorCount; i++) {
        int rows = factors[i];
        int cols = len / rows;

        if (cols * rows != len) {
            continue; // Skip if the matrix cannot fit exactly
        }

        char matrix[rows][cols];
        int idx = 0;

        // Fill the matrix column by column
        for (int c = 0; c < cols; c++) {
            for (int r = 0; r < rows; r++) {
                if (ciphertext[idx] != '\0') {
                    matrix[r][c] = ciphertext[idx++];
                } else {
                    matrix[r][c] = 'X'; // Fill the remaining cells with 'X'
                }
            }
        }

        printf("Matrix (%dx%d):\n", rows, cols);
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                printf("%c ", matrix[r][c]);
            }
            printf("\n");
        }

        // Read row by row to recover plaintext
        char plaintext[len + 1];
        idx = 0;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                plaintext[idx++] = matrix[r][c];
            }
        }
        plaintext[idx] = '\0';

        printf("Ciphertext: %s\n", ciphertext);
        printf("Recovered Plaintext (Transposition Decryption): %s\n", plaintext);
    }
}

int main() {
    int choice;
    char plaintext[100], ciphertext[100];
    int key;

    // Substitution Encryption
    printf("Enter the plaintext for Substitution Encryption: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove newline character

    printf("Enter the key for Substitution Encryption (integer): ");
    scanf("%d", &key);
    getchar();  // Clear newline character

    substitutionEncryption(plaintext, key);

    // Substitution Decryption
    printf("\nEnter the ciphertext for Substitution Decryption: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  // Remove newline character

    printf("Enter the key for Substitution Decryption (integer): ");
    scanf("%d", &key);
    getchar();  // Clear newline character

    substitutionDecryption(ciphertext, key);

    // Transposition Encryption
    printf("\nEnter the plaintext for Transposition Encryption: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove newline character

    // Get factors of plaintext length for matrix dimensions
    int factors[10], factorCount;
    getFactors(strlen(plaintext), factors, &factorCount);

    transpositionEncryption(plaintext, factors, factorCount);

    // Transposition Decryption
    printf("\nEnter the ciphertext for Transposition Decryption: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  // Remove newline character

    transpositionDecryption(ciphertext, factors, factorCount);

    return 0;
}
