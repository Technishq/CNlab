//Write a C/C++ program to decode the code words at the receiver using CRC and Hamming code.
#include <stdio.h>
#include <string.h>
#include <math.h>

#define N strlen(g)

char t[28], cs[28], g[30];
int data_received[30], m, r, l;

void xor_for_crc() {
    for (int c = 1; c < N; c++)
        cs[c] = ((cs[c] == g[c]) ? '0' : '1');
}

void crc_check() {
    for (int e = 0; e < N; e++)
        cs[e] = t[e];
    for (int e = 0; e <= strlen(t) - N; ) {
        if (cs[0] == '1')
            xor_for_crc();
        for (int c = 0; c < N - 1; c++)
            cs[c] = cs[c + 1];
        cs[N - 1] = t[e + N];
        e++;
    }
}

int hamming_check(int data_received[], int l) {
    int error_pos = 0;
    for (int i = 0; i < r; i++) {
        int position = (int)pow(2, i);
        int count = 0;
        for (int j = position; j <= l; j += position * 2) {
            for (int k = j; k < j + position; k++) {
                if (k <= l) {
                    if (data_received[k] == 1) {
                        count++;
                    }
                }
            }
        }
        if (count % 2 != 0) {
            error_pos += position;
        }
    }
    return error_pos;
}

int main() {
    printf("\nEnter the codeword received for CRC: ");
    scanf("%s", t);
    printf("\nEnter the generating polynomial: ");
    scanf("%s", g);

    crc_check();

    printf("\nRemainder after CRC check: %s", cs);
    int crc_error = 0;
    for (int i = 0; i < N; i++) {
        if (cs[i] != '0') {
            crc_error == 1;
            break;
        }
    }

    if (crc_error)
        printf("\nError detected in CRC!\n");
    else
        printf("\nNo error in CRC!\n");

    printf("\nEnter the number of bits in the received Hamming codeword: ");
    scanf("%d", &l);
    printf("\nEnter the received Hamming codeword (as a sequence of 0s and 1s): ");
    for (int i = 1; i <= l; i++) {
        scanf("%1d", &data_received[i]);
    }

    // Calculate the number of redundancy bits in the Hamming code
    r = 0;
    while ((int)pow(2, r) < l + 1)
        r++;

    int error_pos = hamming_check(data_received, l);

    if (error_pos == 0)
        printf("\nNo error in Hamming Code!\n");
    else {
        printf("\nError detected at position: %d\n", error_pos);
        printf("Correcting error...\n");
        data_received[error_pos] = data_received[error_pos] ^ 1; // Flip the error bit
        printf("Corrected codeword: ");
        for (int i = 1; i <= l; i++) {
            printf("%d", data_received[i]);
        }
        printf("\n");
    }

    return 0;
}
