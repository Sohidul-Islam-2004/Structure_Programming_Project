#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 50

typedef struct
{
    int productID;
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;

void adminLogin();
void adminMenu();
void customerMenu();
void addProduct();
void updateProductQuantity();
void viewProducts();
void buyProduct();

int main()
{
    int choice;

    while (1)
    {
        printf("\n====================================\n");
        printf("        Online Shop Management       \n");
        printf("====================================\n");
        printf("1. Admin Login\n");
        printf("2. Customer Menu\n");
        printf("3. Exit\n");
        printf("====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            adminLogin();
            break;
        case 2:
            customerMenu();
            break;
        case 3:
            printf("\nExiting the program. Goodbye!\n");
            return 0;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }
        }
    return 0;
}

void adminLogin()
{
    char email[50], password[50];
    printf("\nEnter Admin Email: ");
    scanf("%s", email);
    printf("Enter Admin Password: ");
    scanf("%s", password);

    if (strcmp(email, "sohidul@gmail.com") == 0 && strcmp(password, "1234") == 0)
    {
        printf("\nLogin Successful!\n");
        adminMenu();
    }
    else
    {
        printf("\nInvalid Email or Password Try Again\n");
    }
}

void adminMenu()
{
    int choice;
    while (1)
    {
        printf("\n========== Admin Menu ==========\n");
        printf("1. Add Product\n");
        printf("2. Update Product Quantity\n");
        printf("3. View All Products\n");
        printf("4. Logout\n");
        printf("================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addProduct();
            break;
        case 2:
            updateProductQuantity();
            break;
        case 3:
            viewProducts();
            break;
        case 4:
            printf("\nLogging out...\n");
            return;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    }
}

void customerMenu()
{
    int choice;
    while (1)
    {
        printf("\n========== Customer Menu ==========\n");
        printf("1. View Products\n");
        printf("2. Buy Product\n");
        printf("3. Back to Main Menu\n");
        printf("===================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            viewProducts();
            break;
        case 2:
            buyProduct();
            break;
        case 3:
            printf("\nReturning to Main Menu...\n");
            return;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    }
}

void addProduct()
{
    if (productCount >= MAX_PRODUCTS)
    {
        printf("\nCannot add more products. Maximum limit reached.\n");
        return;
    }

    Product newProduct;
    printf("\nEnter Product ID: ");
    scanf("%d", &newProduct.productID);
    printf("Enter Product Name: ");
    getchar();
    fgets(newProduct.name, MAX_NAME_LENGTH, stdin);
    strtok(newProduct.name, "\n");
    printf("Enter Product Price: ");
    scanf("%f", &newProduct.price);
    printf("Enter Product Quantity: ");
    scanf("%d", &newProduct.quantity);

    products[productCount++] = newProduct;
    printf("\nProduct added successfully!\n");
}

void updateProductQuantity()
{
    int productID, quantity, found = 0;
    printf("\nEnter Product ID to Update Quantity: ");
    scanf("%d", &productID);

    for (int i = 0; i < productCount; i++)
    {
        if (products[i].productID == productID)
        {
            printf("Current Quantity: %d\n", products[i].quantity);
            printf("Enter Quantity to Add: ");
            scanf("%d", &quantity);
            products[i].quantity += quantity;
            printf("\nProduct quantity updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nProduct with ID %d not found.\n", productID);
    }
}

void viewProducts()
{
    if (productCount == 0)
    {
        printf("\nNo products available.\n");
        return;
    }

    printf("\n========== Available Products ==========\n");
    printf("ID\tName\t\tPrice\t\tQuantity\n");
    printf("========================================\n");
    for (int i = 0; i < productCount; i++)
    {
        printf("%d\t%s\t%.2f\t\t\t\t%d\n", products[i].productID, products[i].name, products[i].price, products[i].quantity);
    }
    printf("========================================\n");
}

void buyProduct()
{
    int productID, quantity, found = 0;
    printf("\nEnter Product ID to Buy: ");
    scanf("%d", &productID);

    for (int i = 0; i < productCount; i++)
    {
        if (products[i].productID == productID)
        {
            found = 1;
            printf("Product Name: %s\n", products[i].name);
            printf("Available Quantity: %d\n", products[i].quantity);
            printf("Enter Quantity to Buy: ");
            scanf("%d", &quantity);

            if (quantity > products[i].quantity)
            {
                printf("\n Out of  stock  Try again.\n");
            }
            else
            {
                products[i].quantity -= quantity;
                float totalPrice = quantity * products[i].price;
                printf("\nPurchase successful!\n");
                printf("========== Payment Receipt ==========\n");
                printf("Product: %s\n", products[i].name);
                printf("Quantity: %d\n", quantity);
                printf("Total Price: $%.2f\n", totalPrice);
                printf("=====================================\n");
            }
            break;
        }
    }

    if (!found)
    {
        printf("\nProduct with ID %d not found.\n", productID);
    }
}
