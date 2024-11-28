#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_PATH "inventory.txt"

typedef struct {
    char productID[20];
    char productName[50];
    char supplierName[50];
    int stock;
    float unitCost;
} Product;

void addProduct();
void viewProducts();
void searchProduct();
void updateProduct();
void deleteProduct();
void calculateInventoryWorth();
int checkDuplicateID(const char *id);

void menu() {
    int choice;
    do {
        printf("\nWarehouse Inventory System\n");
        printf("1. Add Product\n");
        printf("2. View All Products\n");
        printf("3. Search Product\n");
        printf("4. Update Product Details\n");
        printf("5. Delete Product\n");
        printf("6. Calculate Total Inventory Worth\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                viewProducts();
                break;
            case 3:
                searchProduct();
                break;
            case 4:
                updateProduct();
                break;
            case 5:
                deleteProduct();
                break;
            case 6:
                calculateInventoryWorth();
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 0);
}

void addProduct() {
    FILE *file = fopen(FILE_PATH, "a");
    if (!file) return;

    Product item;
    printf("Enter Product ID: ");
    scanf(" %s", item.productID);

    if (checkDuplicateID(item.productID)) {
        printf("Duplicate ID found.\n");
        fclose(file);
        return;
    }

    printf("Enter Product Name: ");
    scanf(" %[^\n]", item.productName);
    printf("Enter Supplier Name: ");
    scanf(" %[^\n]", item.supplierName);
    printf("Enter Stock: ");
    scanf("%d", &item.stock);
    printf("Enter Unit Cost: ");
    scanf("%f", &item.unitCost);

    if (item.stock < 0 || item.unitCost < 0) {
        fclose(file);
        return;
    }

    fprintf(file, "%s|%s|%s|%d|%.2f\n", item.productID, item.productName, item.supplierName, item.stock, item.unitCost);
    fclose(file);
}

void viewProducts() {
    FILE *file = fopen(FILE_PATH, "r");
    if (!file) return;

    Product item;
    printf("\n%-15s %-25s %-20s %-10s %-10s\n", "Product ID", "Name", "Supplier", "Stock", "Unit Cost");
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%d|%f\n", item.productID, item.productName, item.supplierName, &item.stock, &item.unitCost) != EOF) {
        printf("%-15s %-25s %-20s %-10d %-10.2f\n", item.productID, item.productName, item.supplierName, item.stock, item.unitCost);
    }

    fclose(file);
}

void searchProduct() {
    FILE *file = fopen(FILE_PATH, "r");
    if (!file) return;

    char query[50];
    printf("Enter Product ID or Name: ");
    scanf(" %[^\n]", query);

    Product item;
    int found = 0;
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%d|%f\n", item.productID, item.productName, item.supplierName, &item.stock, &item.unitCost) != EOF) {
        if (strcmp(item.productID, query) == 0 || strcasecmp(item.productName, query) == 0) {
            printf("\n%s\n%s\n%s\n%d\n%.2f\n", item.productID, item.productName, item.supplierName, item.stock, item.unitCost);
            found = 1;
            break;
        }
    }

    if (!found) printf("Product not found.\n");

    fclose(file);
}

void updateProduct() {
    FILE *file = fopen(FILE_PATH, "r");
    if (!file) return;

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        fclose(file);
        return;
    }

    char query[20];
    printf("Enter Product ID: ");
    scanf(" %s", query);

    Product item;
    int found = 0;
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%d|%f\n", item.productID, item.productName, item.supplierName, &item.stock, &item.unitCost) != EOF) {
        if (strcmp(item.productID, query) == 0) {
            found = 1;
            printf("Enter New Stock: ");
            scanf("%d", &item.stock);
            printf("Enter New Unit Cost: ");
            scanf("%f", &item.unitCost);
        }
        fprintf(tempFile, "%s|%s|%s|%d|%.2f\n", item.productID, item.productName, item.supplierName, item.stock, item.unitCost);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILE_PATH);
        rename("temp.txt", FILE_PATH);
    } else {
        remove("temp.txt");
    }
}

void deleteProduct() {
    FILE *file = fopen(FILE_PATH, "r");
    if (!file) return;

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        fclose(file);
        return;
    }

    char query[20];
    printf("Enter Product ID: ");
    scanf(" %s", query);

    Product item;
    int found = 0;
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%d|%f\n", item.productID, item.productName, item.supplierName, &item.stock, &item.unitCost) != EOF) {
        if (strcmp(item.productID, query) != 0) {
            fprintf(tempFile, "%s|%s|%s|%d|%.2f\n", item.productID, item.productName, item.supplierName, item.stock, item.unitCost);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILE_PATH);
        rename("temp.txt", FILE_PATH);
    } else {
        remove("temp.txt");
    }
}

void calculateInventoryWorth() {
    FILE *file = fopen(FILE_PATH, "r");
    if (!file) return;

    Product item;
    float totalWorth = 0;
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%d|%f\n", item.productID, item.productName, item.supplierName, &item.stock, &item.unitCost) != EOF) {
        totalWorth += item.stock * item.unitCost;
    }

    printf("Total Inventory Worth: %.2f\n", totalWorth);

    fclose(file);
}

int checkDuplicateID(const char *id) {
    FILE *file = fopen(FILE_PATH, "r");
    if (!file) return 0;

    Product item;
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%d|%f\n", item.productID, item.productName, item.supplierName, &item.stock, &item.unitCost) != EOF) {
        if (strcmp(item.productID, id) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int main() {
    menu();
    return 0;
}

