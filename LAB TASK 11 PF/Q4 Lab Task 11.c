#include <stdio.h>
struct PhoneNumber {
    int areaCode;
    int exchangeCode;
    int lineNumber;
};

int main() {
    struct PhoneNumber myPhone = {212, 767, 8900}; 
    struct PhoneNumber userPhone;  
    printf("Enter area code: ");
    scanf("%d", &userPhone.areaCode);

    printf("Enter exchange code: ");
    scanf("%d", &userPhone.exchangeCode);

    printf("Enter line number: ");
    scanf("%d", &userPhone.lineNumber);

    printf("\nMy number is (%d) %d-%d\n", 
           myPhone.areaCode, myPhone.exchangeCode, myPhone.lineNumber);
    printf("Your number is (%d) %d-%d\n", 
           userPhone.areaCode, userPhone.exchangeCode, userPhone.lineNumber);

    return 0;
}

