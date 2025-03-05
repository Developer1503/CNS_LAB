#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 64 // 512 bits (64 bytes)

// MD Buffer Initialization
uint32_t A = 0x67452301;
uint32_t B = 0xefcdab89;
uint32_t C = 0x98badcfe;
uint32_t D = 0x10325476;

// Function to append padding bits and message length
void padMessage(uint8_t *message, uint64_t length, uint8_t **paddedMessage, uint64_t *newLength) {
    uint64_t bitLength = length * 8; // Original length in bits
    uint64_t paddingLength = (BLOCK_SIZE - ((length + 8) % BLOCK_SIZE)) % BLOCK_SIZE;
    *newLength = length + paddingLength + 8;

    *paddedMessage = (uint8_t *)malloc(*newLength);
    memcpy(*paddedMessage, message, length);
    (*paddedMessage)[length] = 0x80; // Append '1' bit
    memset(*paddedMessage + length + 1, 0, paddingLength - 1); // Append '0' bits

    // Append length (low-order first, little-endian format)
    for (int i = 0; i < 8; i++) {
        (*paddedMessage)[*newLength - 8 + i] = (bitLength >> (i * 8)) & 0xFF;
    }
}

int main() {
    char message[1024];
    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    uint8_t *paddedMessage;
    uint64_t newLength;

    padMessage((uint8_t *)message, strlen(message), &paddedMessage, &newLength);

    // Print padded message in hex
    printf("Padded Message: \n");
    for (uint64_t i = 0; i < newLength; i++) {
        printf("%02x ", paddedMessage[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }
    printf("\n");

    free(paddedMessage);
    return 0;
}
