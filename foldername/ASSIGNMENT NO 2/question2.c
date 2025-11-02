#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 5
#define COUPON "EID2025"
#define OFF_RATE 0.25


int codes[MAX_ITEMS] = {1, 2, 3, 4, 5};
float prices[MAX_ITEMS] = {220.0, 180.0, 350.0, 300.0, 750.0};
int stock[MAX_ITEMS] = {100, 150, 200, 80, 50};


int basket[MAX_ITEMS] = {0};
char buyer_name[100] = "Unknown";
char buyer_cnic[25] = "N/A";


float total = 0.0;
float final_amount = 0.0;
int discount_used = 0;


void enterCustomer();
void showStock();
void addToBasket();
void checkout();
void invoice();


void enterCustomer() {
    printf("\n--- Customer Details ---\n");
    printf("Enter Full Name: ");
    scanf(" %[^\n]s", buyer_name);

    printf("Enter CNIC (e.g., 12345-6789012-3): ");
    scanf("%s", buyer_cnic);

    printf("\nCustomer profile saved successfully!\n");
}

void showStock() {
    printf("\n--- Product List -----\n");
    printf("Code\tPrice (Rs.)\tAvailable\n\n");
    for (int i = 0; i < MAX_ITEMS; i++) {
        printf("%d\t%.2f\t\t%d\n", codes[i], prices[i], stock[i]);
    }
    printf("\n");
}

void addToBasket() {
    int id, qty, again = 0;

    do {
        showStock();
        printf("Enter product code (1-%d): ", MAX_ITEMS);
        if (scanf("%d", &id) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        if (id < 1 || id > MAX_ITEMS) {
            printf("Invalid product code!\n");
            continue;
        }

        int index = id - 1;
        printf("Enter quantity for item %d: ", codes[index]);
        if (scanf("%d", &qty) != 1) {
            printf("Invalid number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (qty <= 0) {
            printf("Quantity must be greater than zero.\n");
        } else if (qty > stock[index]) {
            printf("Sorry, only %d units left in stock.\n", stock[index]);
        } else {
            basket[index] += qty;
            stock[index] -= qty;
            printf("%d units of item %d added to basket.\n", qty, codes[index]);
        }

        printf("\nAdd another item? (1 for yes, 0 for no): ");
        scanf("%d", &again);
        while (getchar() != '\n');
    } while (again == 1);
}

void checkout() {
    char coupon[50];
    int has_coupon = 0;
    int items = 0;
    total = 0.0;
    final_amount = 0.0;
    discount_used = 0;

    printf("\n--- Checkout ---\n");
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (basket[i] > 0) {
            total += basket[i] * prices[i];
            items++;
        }
    }

    if (items == 0) {
        printf("Your cart is empty!\n");
        return;
    }

    printf("Total before discount: Rs. %.2f\n", total);
    printf("Do you have a coupon code? (1/0): ");
    scanf("%d", &has_coupon);

    if (has_coupon == 1) {
        printf("Enter coupon code: ");
        scanf("%s", coupon);

        if (strcmp(coupon, COUPON) == 0) {
            final_amount = total * (1 - OFF_RATE);
            discount_used = 1;
            printf("Coupon applied successfully! You saved 25%%.\n");
        } else {
            printf("Invalid coupon.\n");
            final_amount = total;
        }
    } else {
        printf("No coupon entered.\n");
        final_amount = total;
    }

    printf("Total to pay: Rs. %.2f\n", final_amount);
}

void invoice() {
    printf("\n===== RECEIPT =====\n");
    printf("Customer: %s\n", buyer_name);
    printf("CNIC: %s\n\n", buyer_cnic);

    if (total == 0.0) {
        printf("No checkout done yet. Please add items and proceed to checkout first.\n");
        return;
    }

    printf("Items Bought:\n");
    printf("Code\tQty\tUnit Price\tTotal\n\n");
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (basket[i] > 0) {
            printf("%d\t%d\t%.2f\t\t%.2f\n", codes[i], basket[i], prices[i], basket[i] * prices[i]);
        }
    }

    printf("\nSubtotal:\t\t\tRs. %.2f\n", total);
    if (discount_used) {
        printf("Discount Applied (25%%):\t-Rs. %.2f\n", total - final_amount);
    } else {
        printf("Discount Applied:\t\tRs. 0.00\n");
    }

    printf("-------------------------------------------\n");
    printf("Amount Payable:\t\t\tRs. %.2f\n", final_amount);
    printf("\nThanks for visiting Liberty Supermart!\n");
}

int main() {
    int choice;

    do {
        printf("\n=== Liberty Supermart Menu ===\n");
        printf("1. Enter Customer Details\n");
        printf("2. View Product List\n");
        printf("3. Add Items to Basket\n");
        printf("4. Checkout & Apply Discount\n");
        printf("5. Print Receipt\n");
        printf("6. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                enterCustomer();
                break;
            case 2:
                showStock();
                break;
            case 3:
                addToBasket();
                break;
            case 4:
                checkout();
                break;
            case 5:
                invoice();
                break;
            case 6:
                printf("Exiting program... Goodbye!\n");
                break;
            default:
                printf("Invalid option! Please pick from 1-6.\n");
        }
    } while (choice != 6);

    return 0;
}
