#include <stdio.h>
#include <string.h>

union won_or_dollar {
    int won;
    float dollar;
};

typedef struct product {
    char *name;
    _Bool w_d;
    union won_or_dollar price;
} product;

int main() {
    long long int amount, exchange;
    product products[6] = {{"PMP",        0, 600000},
                           {"MP3",        0, 153000},
                           {"SmartPhone", 1, .price.dollar= 520.40},
                           {"TV",         1, .price.dollar= 430.20},
                           {"Navigator",  0, 350000},
                           {"Laptop",     1, .price.dollar= 1950.00}};
    printf("Enter your holding amount and exchange rate");
    printf("holding amount :");
    scanf("%lld", &amount);
    printf("exchange rate :");
    scanf("%lld", &exchange);

    printf("you can buy ... \n");
    for (int i = 0; i < 6; i++) {
        if (products[i].w_d == 1) {
            products[i].price.won = (long long int) products[i].price.dollar * exchange;
            if (products[i].price.won > amount) {
                printf("%s , %lld won", products[i].name, products[i].price.won);

            }
        } else {
            if (products[i].price.won > amount) {
                printf("%s , %lld won", products[i].name, products[i].price.won);

            }
        }
    }


}
