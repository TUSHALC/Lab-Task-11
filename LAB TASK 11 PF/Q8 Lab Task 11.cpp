#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "library.txt"

typedef struct {
    char code[20];
    char name[50];
    char writer[50];
    int stock;
    float cost;
} Item;

void addItem();
void viewItems();
void findItem();
void modifyItem();
void removeItem();
void totalValue();
int checkDuplicate(const char *code);

void menu() {
    int option;
    do {
        printf("\nSystem Menu\n");
        printf("1. Add Item\n");
        printf("2. View All Items\n");
        printf("3. Find Item\n");
        printf("4. Modify Item\n");
        printf("5. Remove Item\n");
        printf("6. Calculate Total Value\n");
        printf("0. Quit\n");
        printf("Select an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                addItem();
                break;
            case 2:
                viewItems();
                break;
            case 3:
                findItem();
                break;
            case 4:
                modifyItem();
                break;
            case 5:
                removeItem();
                break;
            case 6:
                totalValue();
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (option != 0);
}

void addItem() {
    FILE *fp = fopen(DATA_FILE, "a");
    if (!fp) {
        printf("File error.\n");
        return;
    }

    Item item;
    printf("Enter Code: ");
    scanf(" %s", item.code);

    if (checkDuplicate(item.code)) {
        printf("Item with Code %s exists.\n", item.code);
        fclose(fp);
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", item.name);
    printf("Enter Writer: ");
    scanf(" %[^\n]", item.writer);
    printf("Enter Stock: ");
    scanf("%d", &item.stock);
    printf("Enter Cost: ");
    scanf("%f", &item.cost);

    if (item.stock < 0 || item.cost < 0) {
        printf("Invalid values.\n");
        fclose(fp);
        return;
    }

    fprintf(fp, "%s|%s|%s|%d|%.2f\n", item.code, item.name, item.writer, item.stock, item.cost);
    printf("Item added.\n");

    fclose(fp);
}

void viewItems() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        printf("No records.\n");
        return;
    }

    Item item;
    printf("\n%-10s %-30s %-20s %-10s %-10s\n", "Code", "Name", "Writer", "Stock", "Cost");
    printf("------------------------------------------------------------\n");
    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%d|%f\n", item.code, item.name, item.writer, &item.stock, &item.cost) != EOF) {
        printf("%-10s %-30s %-20s %-10d %-10.2f\n", item.code, item.name, item.writer, item.stock, item.cost);
    }

    fclose(fp);
}

void findItem() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        printf("No records.\n");
        return;
    }

    char search[50];
    printf("Enter Code or Name: ");
    scanf(" %[^\n]", search);

    Item item;
    int located = 0;
    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%d|%f\n", item.code, item.name, item.writer, &item.stock, &item.cost) != EOF) {
        if (strcmp(item.code, search) == 0 || strcasecmp(item.name, search) == 0) {
            printf("Found:\n");
            printf("Code: %s\nName: %s\nWriter: %s\nStock: %d\nCost: %.2f\n", item.code, item.name, item.writer, item.stock, item.cost);
            located = 1;
            break;
        }
    }

    if (!located) printf("Not found.\n");

    fclose(fp);
}

void modifyItem() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        printf("No records.\n");
        return;
    }

    FILE *tmp = fopen("temp.txt", "w");
    if (!tmp) {
        fclose(fp);
        printf("Error.\n");
        return;
    }

    char target[20];
    printf("Enter Code: ");
    scanf(" %s", target);

    Item item;
    int updated = 0;
    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%d|%f\n", item.code, item.name, item.writer, &item.stock, &item.cost) != EOF) {
        if (strcmp(item.code, target) == 0) {
            updated = 1;
            printf("New Stock: ");
            scanf("%d", &item.stock);
            printf("New Cost: ");
            scanf("%f", &item.cost);
        }
        fprintf(tmp, "%s|%s|%s|%d|%.2f\n", item.code, item.name, item.writer, item.stock, item.cost);
    }

    fclose(fp);
    fclose(tmp);

    if (updated) {
        remove(DATA_FILE);
        rename("temp.txt", DATA_FILE);
        printf("Updated.\n");
    } else {
        remove("temp.txt");
        printf("Not found.\n");
    }
}

void removeItem() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        printf("No records.\n");
        return;
    }

    FILE *tmp = fopen("temp.txt", "w");
    if (!tmp) {
        fclose(fp);
        printf("Error.\n");
        return;
    }

    char target[20];
    printf("Enter Code: ");
    scanf(" %s", target);

    Item item;
    int found = 0;
    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%d|%f\n", item.code, item.name, item.writer, &item.stock, &item.cost) != EOF) {
        if (strcmp(item.code, target) != 0) {
            fprintf(tmp, "%s|%s|%s|%d|%.2f\n", item.code, item.name, item.writer, item.stock, item.cost);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(tmp);

    if (found) {
        remove(DATA_FILE);
        rename("temp.txt", DATA_FILE);
        printf("Deleted.\n");
    } else {
        remove("temp.txt");
        printf("Not found.\n");
    }
}

void totalValue() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        printf("No records.\n");
        return;
    }

    Item item;
    float sum = 0;
    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%d|%f\n", item.code, item.name, item.writer, &item.stock, &item.cost) != EOF) {
        sum += item.stock * item.cost;
    }

    printf("Total Value: %.2f\n", sum);
    fclose(fp);
}

int checkDuplicate(const char *code) {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) return 0;

    Item item;
    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%d|%f\n", item.code, item.name, item.writer, &item.stock, &item.cost) != EOF) {
        if (strcmp(item.code, code) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int main() {
    menu();
    return 0;
}

