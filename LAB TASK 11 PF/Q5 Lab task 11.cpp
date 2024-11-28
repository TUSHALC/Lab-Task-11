#include <stdio.h>
#include <string.h>

struct ProductInvoice {
    char itemCode[20];
    char itemDescription[50];
    int itemQuantity;
    float itemUnitPrice;
};

float calculateInvoiceTotal(struct ProductInvoice *invoice) {
    if (invoice->itemQuantity <= 0) {
        invoice->itemQuantity = 0; 
    }
    if (invoice->itemUnitPrice <= 0) {
        invoice->itemUnitPrice = 0.0; 
    }
    return invoice->itemQuantity * invoice->itemUnitPrice;
}

int main() {
    struct ProductInvoice invoiceA = {"P101", "Electric Drill", 3, 49.99};
    struct ProductInvoice invoiceB = {"P202", "Screwdriver Set", -2, -9.50};

    float totalAmountA = calculateInvoiceTotal(&invoiceA);
    float totalAmountB = calculateInvoiceTotal(&invoiceB);

    printf("Invoice A:\n");
    printf("Item Code: %s\n", invoiceA.itemCode);
    printf("Description: %s\n", invoiceA.itemDescription);
    printf("Quantity: %d\n", invoiceA.itemQuantity);
    printf("Unit Price: $%.2f\n", invoiceA.itemUnitPrice);
    printf("Invoice Total: $%.2f\n\n", totalAmountA);

    printf("Invoice B:\n");
    printf("Item Code: %s\n", invoiceB.itemCode);
    printf("Description: %s\n", invoiceB.itemDescription);
    printf("Quantity: %d\n", invoiceB.itemQuantity);
    printf("Unit Price: $%.2f\n", invoiceB.itemUnitPrice);
    printf("Invoice Total: $%.2f\n", totalAmountB);

    return 0;
}

