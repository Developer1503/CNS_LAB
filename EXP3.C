#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate (base^exp) % mod using binary exponentiation
long long powerMod(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod; // Ensure base is within mod
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    long long n, g, x, y, A, B, K1, K2;

    // Step i: Alice and Bob agree on public parameters n and g
    printf("Enter the large prime number n: ");
    scanf("%lld", &n);
    printf("Enter the generator g: ");
    scanf("%lld", &g);

    // Step ii: Alice chooses a secret random number x, computes A = g^x mod n
    printf("\nAlice chooses a secret random number x: ");
    scanf("%lld", &x);
    A = powerMod(g, x, n);  // A = g^x mod n
    printf("Alice computes A = g^x mod n = %lld\n", A);

    // Step iii: Alice sends A to Bob
    printf("\nAlice sends A to Bob: %lld\n", A);

    // Step iv: Bob chooses a secret random number y, computes B = g^y mod n
    printf("\nBob chooses a secret random number y: ");
    scanf("%lld", &y);
    B = powerMod(g, y, n);  // B = g^y mod n
    printf("Bob computes B = g^y mod n = %lld\n", B);

    // Step v: Bob sends B to Alice
    printf("\nBob sends B to Alice: %lld\n", B);

    // Step vi: Alice computes the shared secret key K1 = B^x mod n
    K1 = powerMod(B, x, n);  // K1 = B^x mod n
    printf("\nAlice computes the shared secret key K1 = B^x mod n = %lld\n", K1);

    // Step vii: Bob computes the shared secret key K2 = A^y mod n
    K2 = powerMod(A, y, n);  // K2 = A^y mod n
    printf("\nBob computes the shared secret key K2 = A^y mod n = %lld\n", K2);

    // Check if both Alice and Bob computed the same shared key
    if (K1 == K2) {
        printf("\nBoth Alice and Bob computed the same shared secret key: %lld\n", K1);
    } else {
        printf("\nError! The keys do not match!\n");
    }

    return 0;
}
