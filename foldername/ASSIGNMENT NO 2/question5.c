#include <stdio.h>
#include <string.h>
#define MAX_LEN 255

void reverseString(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void toggleBits(char str[]) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] ^= 18;  
    }
}

void encryptMessage(char message[]) {
    reverseString(message);
    toggleBits(message);
    printf("\nEncoded message: %s\n\n", message);
}

void decryptMessage(char message[]) {
    toggleBits(message);
    reverseString(message);
    printf("\nDecoded message: %s\n\n", message);
}

int main() {
    char message[MAX_LEN];
    int option;

    do {
        printf("\n=== TCS Cryptography Tool ===\n");
        printf("1. Encrypt Message\n");
        printf("2. Decrypt Message\n");
        printf("3. Exit\n");
        printf("Choose an option (1-3): ");
        scanf("%d", &option);
        while (getchar() != '\n'); 

        switch (option) {
            case 1:
                printf("Enter message to encrypt: ");
                scanf("%[^\n]", message);
                encryptMessage(message);
                break;
            case 2:
                printf("Enter message to decrypt: ");
                scanf("%[^\n]", message);
                decryptMessage(message);
                break;
            case 3:
                printf("\nExiting. Thank you for using TCS Cryptography Tool!\n");
                break;
            default:
                printf("\n Invalid choice! Try again.\n");
        }
    } while (option != 3);

    return 0;
}
