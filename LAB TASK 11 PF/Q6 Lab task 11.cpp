#include <stdio.h>
#include <string.h>

struct ProductInvoice {
    char itemCode[20];
    char itemDescription[50];
    int itemQuantity;
    float unitPrice;
};

float calculateInvoiceTotal(struct ProductInvoice *invoice) {
    if (invoice->itemQuantity <= 0) {
        invoice->itemQuantity = 0; 
    }
    if (invoice->unitPrice <= 0) {
        invoice->unitPrice = 0.0; 
    }
    return invoice->itemQuantity * invoice->unitPrice;
}

int main() {
   
    struct ProductInvoice invoice1 = {"P001", "Cordless Drill", 3, 75.50};
    struct ProductInvoice invoice2 = {"P002", "Wrench Set", -5, -20.00};

    float totalAmount1 = calculateInvoiceTotal(&invoice1);
    float totalAmount2 = calculateInvoiceTotal(&invoice2);

    printf("Invoice 1:\n");
    printf("Item Code: %s\n", invoice1.itemCode);
    printf("Description: %s\n", invoice1.itemDescription);
    printf("Quantity: %d\n", invoice1.itemQuantity);
    printf("Unit Price: $%.2f\n", invoice1.unitPrice);
    printf("Invoice Total: $%.2f\n\n", totalAmount1);

    printf("Invoice 2:\n");
    printf("Item Code: %s\n", invoice2.itemCode);
    printf("Description: %s\n", invoice2.itemDescription);
    printf("Quantity: %d\n", invoice2.itemQuantity);
    printf("Unit Price: $%.2f\n", invoice2.unitPrice);
    printf("Invoice Total: $%.2f\n", totalAmount2);

    return 0;
}

