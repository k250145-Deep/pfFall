#include <stdio.h>

#define ROWS 3
#define COLS 3

void show_sector(int r, int c, int grid[ROWS][COLS]) {
    int flag = grid[r][c];

    printf("\n--- Sector [%d,%d] Status ---\n", r + 1, c + 1);
    printf("Status Flag: %d\n", flag);
    printf("Power: %s\n", (flag & 1) ? "ON" : "OFF");
    printf("Overload: %s\n", (flag & 2) ? "YES" : "NO");
    printf("Maintenance: %s\n\n", (flag & 4) ? "Required" : "Not Needed");
}

void modify_sector(int grid[ROWS][COLS]) {
    int r, c, new_flag;

    printf("\nEnter sector coordinates (row col) between 1 and %d: ", ROWS);
    if (scanf("%d %d", &r, &c) != 2 || r < 1 || c < 1 || r > ROWS || c > COLS) {
        printf(" Invalid sector coordinates. Try again.\n");
        while (getchar() != '\n');
        return;
    }

    r--; 
    c--;

    show_sector(r, c, grid);

    printf("Enter new status flag (0–7): ");
    scanf("%d", &new_flag);

    if (new_flag < 0 || new_flag > 7) {
        printf("Invalid flag. Must be between 0–7.\n");
        return;
    }

    grid[r][c] = new_flag;
    printf("Sector [%d,%d] updated successfully! New flag: %d\n\n", r + 1, c + 1, grid[r][c]);
}

void check_sector(int grid[ROWS][COLS]) {
    int r, c;

    printf("\nEnter coordinates to check (1-%d 1-%d): ", ROWS, COLS);
    scanf("%d %d", &r, &c);

    if (r < 1 || r > ROWS || c < 1 || c > COLS) {
        printf(" Invalid input! Try again.\n");
        return;
    }

    show_sector(r - 1, c - 1, grid);
}

void run_diagnostics(int grid[ROWS][COLS]) {
    printf("\n--- Running Grid Diagnostics ---\n");
    int alerts = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int val = grid[i][j];
            if (val & 2) {
                printf(" Sector [%d,%d] overloaded (flag %d)\n", i + 1, j + 1, val);
                alerts++;
            }
            if (val & 4) {
                printf("🔧 Sector [%d,%d] requires maintenance (flag %d)\n", i + 1, j + 1, val);
                alerts++;
            }
        }
    }

    if (!alerts)
        printf(" All sectors operating normally.\n");
    printf("\n");
}

int main() {
    int grid[ROWS][COLS] = {
        {3, 1, 2},
        {3, 4, 5},
        {6, 7, 7}
    };

    int option;

    do {
        printf("\n=== IESCO Grid Control Panel ===\n");
        printf("1. Update Sector\n");
        printf("2. View Sector Details\n");
        printf("3. Run Diagnostics\n");
        printf("4. Exit\n");
        printf("Select option: ");
        scanf("%d", &option);
        while (getchar() != '\n');

        switch (option) {
            case 1:
                modify_sector(grid);
                break;
            case 2:
                check_sector(grid);
                break;
            case 3:
                run_diagnostics(grid);
                break;
            case 4:
                printf("\nSystem shutting down. Goodbye!\n");
                break;
            default:
                printf(" Invalid option, please choose between 1–4.\n");
        }

    } while (option != 4);

    return 0;
}
