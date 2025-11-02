#include <stdio.h>
#include <string.h>

#define MAX 100


void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int *n);
void processSale(int isbns[], int quantities[], int n);
void lowStock(int isbns[], char titles[][50], float prices[], int quantities[], int n);
int findBook(int isbns[], int n, int isbn);

int main() {
    int isbns[MAX];
    char titles[MAX][50];
    float prices[MAX];
    int quantities[MAX];
    int n = 0;
    int choice;

    do {
        printf("\n==== LIBERTY BOOKS INVENTORY ====\n");
        printf("1. Add New Book\n");
        printf("2. Process Sale\n");
        printf("3. Low Stock Report\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addBook(isbns, titles, prices, quantities, &n);
                break;
            case 2:
                processSale(isbns, quantities, n);
                break;
            case 3:
                lowStock(isbns, titles, prices, quantities, n);
                break;
            case 4:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    } while(choice != 4);

    return 0;
}

int findBook(int isbns[], int n, int isbn) {
    for(int i=0; i<n; i++) {
        if(isbns[i] == isbn)
            return i;
    }
    return -1;
}

void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int *n) {
    if(*n >= MAX) {
        printf("Inventory full!\n");
        return;
    }

    int isbn;
    printf("Enter ISBN: ");
    scanf("%d", &isbn);

    if(findBook(isbns, *n, isbn) != -1) {
        printf("Book already exists!\n");
        return;
    }

    isbns[*n] = isbn;

    printf("Enter Title: ");
    getchar(); 
    gets(titles[*n]); 

    printf("Enter Price: ");
    scanf("%f", &prices[*n]);

    printf("Enter Quantity: ");
    scanf("%d", &quantities[*n]);

    (*n)++;

    printf("Book added!\n");
}

void processSale(int isbns[], int quantities[], int n) {
    int isbn, sold;
    printf("Enter ISBN: ");
    scanf("%d", &isbn);

    int i = findBook(isbns, n, isbn);
    if(i == -1) {
        printf("Book not found!\n");
        return;
    }

    printf("Enter number of copies sold: ");
    scanf("%d", &sold);

    if(quantities[i] < sold) {
        printf("Not enough stock! Only %d left.\n", quantities[i]);
    } else {
        quantities[i] -= sold;
        printf("Sale done. Remaining: %d\n", quantities[i]);
    }
}

void lowStock(int isbns[], char titles[][50], float prices[], int quantities[], int n) {
    int found = 0;
    printf("\n--- LOW STOCK REPORT ---\n");
    for(int i=0; i<n; i++) {
        if(quantities[i] < 5) {
            printf("ISBN: %d | Title: %s | Price: %.2f | Qty: %d\n", isbns[i], titles[i], prices[i], quantities[i]);
            found = 1;
        }
    }
    if(!found)
        printf("No low stock books!\n");
}
