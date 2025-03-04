#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate gcd (Greatest Common Divisor)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate modular inverse (D × E) mod φ(N) = 1
int modInverse(int e, int phi) {
    for (int d = 1; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1;
}

// Function to calculate power modulo (a^b) % c
long long powerMod(long long a, long long b, long long c) {
    long long result = 1;
    a = a % c;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % c;
        }
        b = b >> 1;
        a = (a * a) % c;
    }
    return result;
}

// Function to check if a number is prime
int isPrime(int n) {
    if (n <= 1)
        return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

// RSA Algorithm
void rsaAlgorithm() {
    int P, Q, N, phi, E, D, PT, CT;
    printf("\nEnter two large prime numbers (P and Q): ");
    scanf("%d %d", &P, &Q);

    // Step 2: Calculate N = P × Q
    N = P * Q;

    // Step 3: Calculate φ(N) = (P-1) * (Q-1)
    phi = (P - 1) * (Q - 1);

    // Step 4: Select E such that gcd(E, φ(N)) = 1
    do {
        printf("Enter the public key (encryption key) E: ");
        scanf("%d", &E);
    } while (gcd(E, phi) != 1);  // Ensure that E and φ(N) are coprime

    // Step 5: Select D such that (D × E) mod φ(N) = 1
    D = modInverse(E, phi);

    if (D == -1) {
        printf("No modular inverse exists for the chosen E.\n");
        return;
    }

    printf("Private key (D): %d\n", D);
    printf("Public key (E): %d\n", E);
    printf("N: %d\n", N);

    // Encryption: CT = (PT^E) mod N
    printf("\nEnter the plaintext PT: ");
    scanf("%d", &PT);
    CT = powerMod(PT, E, N);
    printf("Ciphertext (CT): %d\n", CT);

    // Decryption: PT = (CT^D) mod N
    int decryptedPT = powerMod(CT, D, N);
    printf("Decrypted Plaintext (PT): %d\n", decryptedPT);
}

// Digital Signature Algorithm
void digitalSignature() {
    int p, q, n, eA, dA, m, y, z;

    // Step 1: Alice chooses secret odd primes p, q and computes n = p * q
    printf("\nEnter two odd prime numbers (p and q): ");
    scanf("%d %d", &p, &q);
    n = p * q;

    // Step 2: Alice chooses eA such that gcd(eA, Φ(n)) = 1
    int phi = (p - 1) * (q - 1);
    do {
        printf("Enter Alice's public key (eA): ");
        scanf("%d", &eA);
    } while (gcd(eA, phi) != 1);  // Ensure gcd(eA, Φ(n)) = 1

    // Step 3: Alice computes dA = eA^-1 mod Φ(n)
    dA = modInverse(eA, phi);
    if (dA == -1) {
        printf("No modular inverse exists for the chosen eA.\n");
        return;
    }

    // Step 4: Alice's signature: y = m^dA mod n
    printf("\nEnter the message m (as an integer): ");
    scanf("%d", &m);
    y = powerMod(m, dA, n);
    printf("Alice's signature (y): %d\n", y);

    // Step 5: The signed message is (m, y)
    printf("The signed message is (m: %d, y: %d)\n", m, y);

    // Step 6: Bob can verify the signature by calculating z = y^eA mod n
    z = powerMod(y, eA, n);
    printf("\nBob calculates z = y^eA mod n: %d\n", z);

    // Step 7: The signature is valid if m == z
    if (m == z) {
        printf("The signature is valid. Message is authentic.\n");
    } else {
        printf("The signature is invalid. Message is not authentic.\n");
    }
}

int main() {
    int choice;
    
    printf("Choose an option:\n");
    printf("1. RSA Algorithm (Encryption and Decryption)\n");
    printf("2. Digital Signature Algorithm\n");
    scanf("%d", &choice);

    if (choice == 1) {
        rsaAlgorithm();
    } else if (choice == 2) {
        digitalSignature();
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
