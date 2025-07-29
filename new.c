#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>

struct admin {
    char name[100];
    char password[100];
};

struct Item {
    int id;
    char name[50];
    float price;
    int quantity;
};

struct Item inventory[100] = {
    {1, "Pizza", 250.0, 10},
    {2, "Chowmein", 120.0, 15},
    {3, "Momo", 150.0, 20},
    {4, "Samosa", 30.0, 40}
};

int itemCount = 4;

void loadInventoryFromFile() {
    FILE *fp = fopen("inventory.txt", "r");
    if (fp == NULL)
        return;

    itemCount = 0;
    while (fscanf(fp, "%d %f %d\n", &inventory[itemCount].id, inventory[itemCount].name, &inventory[itemCount].price, &inventory[itemCount].quantity) == 4) {
        itemCount++;
    }
    fclose(fp);
}

void saveInventoryToFile() {
    FILE *fp = fopen("inventory.txt", "w");
    if (fp == NULL) {
        printf("Failed to open file to save inventory.\n");
        return;
    }
    for (int i = 0; i < itemCount; i++) {
        fprintf(fp, "%d\t%s\t%.2f\t%d\n", inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
    fclose(fp);
}

int isStrongPassword(struct admin a1) {
    char *password = a1.password;
    int length = strlen(password);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSymbol = 0;

    if (length < 8) return 0;

    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else hasSymbol = 1;
    }
    return hasUpper && hasLower && hasDigit && hasSymbol;
}

void welcome() {
    printf("--------BCA First Year Project-----------\n");
    printf("Submitted by:\n1. Sabin Dangol\n2. Sachin Belbase\n3. Roshan Babu Koirala\n4. Sandesh Shrestha\n");
    printf("Submitted to: Department Of BCA\n\n");
}

void content() {
    printf("------Table Of Content-------\n");
    printf("* Log in\n* Order View\n* Order Placement\n* Payment\n");
}

void showInventory() {
    printf("ID:\tName:\t\tPrice:\t\tStock:\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d\t%-12s\t%.2f\t\t%d\n", inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
}

void placeOrder() {
    int id, qty, found;
    float totalAmount = 0.0;
    char customerName[100];

    printf("Enter your name: ");
    getchar();
    fgets(customerName, sizeof(customerName), stdin);
    customerName[strcspn(customerName, "\n")] = '\0';

    struct {
        char name[50];
        int qty;
        float subtotal;
    } ordered[100];

    int orderIndex = 0;

    while (1) {
        found = 0;
        printf("\nEnter item ID (0 to finish): ");
        scanf("%d", &id);
        if (id == 0) break;

        printf("Enter Quantity: ");
        scanf("%d", &qty);

        for (int i = 0; i < itemCount; i++) {
            if (inventory[i].id == id) {
                found = 1;
                if (inventory[i].quantity >= qty) {
                    inventory[i].quantity -= qty;
                    float cost = inventory[i].price * qty;
                    totalAmount += cost;
                    strcpy(ordered[orderIndex].name, inventory[i].name);
                    ordered[orderIndex].qty = qty;
                    ordered[orderIndex].subtotal = cost;
                    orderIndex++;
                    printf("Order placed! Subtotal: Rs. %.2f\n", cost);
                } else {
                    printf("Insufficient stock!\n");
                }
                break;
            }
        }
        if (!found) printf("Item not found.\n");
    }

    saveInventoryToFile();

    printf("\n=========== Final Receipt for %s ===========\n", customerName);
    printf("Item\t\tQty\tSubtotal\n");
    printf("-------------------------------------\n");
    for (int i = 0; i < orderIndex; i++) {
        printf("%-12s\t%d\tRs. %.2f\n", ordered[i].name, ordered[i].qty, ordered[i].subtotal);
    }
    printf("-------------------------------------\n");
    printf("Total Amount:\t\tRs. %.2f\n", totalAmount);
    printf("=====================================\n");
}

void addItem() {
    if (itemCount >= 100) {
        printf("Inventory full!\n");
        return;
    }
    struct Item newItem;
    newItem.id = itemCount + 1;
    printf("Enter item name: ");
    getchar();
    fgets(newItem.name, sizeof(newItem.name), stdin);
    newItem.name[strcspn(newItem.name, "\n")] = '\0';
    printf("Enter price: ");
    scanf("%f", &newItem.price);
    printf("Enter quantity: ");
    scanf("%d", &newItem.quantity);

    inventory[itemCount++] = newItem;
    printf("Item added successfully!\n");
    saveInventoryToFile();
}

void updateItem() {
    int id, found = 0;
    printf("Enter item ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            found = 1;
            printf("Updating %s\n", inventory[i].name);
            printf("Enter new name: ");
            getchar();
            fgets(inventory[i].name, sizeof(inventory[i].name), stdin);
            inventory[i].name[strcspn(inventory[i].name, "\n")] = '\0';
            printf("Enter new price: ");
            scanf("%f", &inventory[i].price);
            printf("Enter new quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Item updated successfully!\n");
            break;
        }
    }
    if (!found) printf("Item not found.\n");
    else saveInventoryToFile();
}

void deleteItem() {
    int id, found = 0;
    printf("Enter item ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            found = 1;
            for (int j = i; j < itemCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            itemCount--;
            printf("Item deleted successfully!\n");
            break;
        }
    }
    if (!found) printf("Item not found.\n");
    else saveInventoryToFile();
}

void adminMenu() {
    int choice;
    while (1) {
        printf("\n========== Admin Menu ==========\n");
        printf("1. View Inventory\n");
        printf("2. Add New Item\n");
        printf("3. Update Existing Item\n");
        printf("4. Delete Item\n");
        printf("5. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        system("CLS");

        switch (choice) {
            case 1: showInventory(); break;
            case 2: addItem(); break;
            case 3: updateItem(); break;
            case 4: deleteItem(); break;
            case 5: return;
            default: printf("Invalid choice!\n");
        }
        printf("\nPress any key to continue...\n");
        getch();
        system("CLS");
    }
}

int main() {
    welcome();
    getch();
    system("CLS");
    content();
    printf("\nPress any key to continue...\n");
    getch();
    system("CLS");
    loadInventoryFromFile();

    int a;
    struct admin a1;

    while (1) {
        printf("----LOG IN----\n1. Customer\n2. Admin\n3. Exit\n");
        printf("Enter a number: ");
        scanf("%d", &a);
        system("CLS");

        if (a == 1) {
            printf("Customer Section\n");
            showInventory();
            placeOrder();
            printf("\nPress any key to return to menu...\n");
            getch();
            system("CLS");
        }
        else if (a == 2) {
            getchar();
            printf("-----Admin Log in-----\n");
            printf("Enter Name: ");
            fgets(a1.name, sizeof(a1.name), stdin);
            a1.name[strcspn(a1.name, "\n")] = '\0';

            printf("Enter Password: ");
            int i = 0;
            char ch;
            while ((ch = getch()) != 13) {
                if (ch == 8 && i > 0) {
                    i--;
                    printf("\b \b");
                } else if (ch != 8) {
                    a1.password[i++] = ch;
                    printf("*");
                }
            }
            a1.password[i] = '\0';
            printf("\n");

            if (isStrongPassword(a1)) {
                printf("Welcome, %s\n", a1.name);
                adminMenu();
            } else {
                printf("Weak Password .... Try Again!\n");
                printf("Press any key to retry...\n");
                getch();
                system("CLS");
            }
        }
        else if (a == 3) {
            printf("Exiting the program. Thank you!\n");
            break;
        }
        else {
            printf("Invalid option. Please try again.\n");
            getch();
            system("CLS");
        }
    }
    return 0;
}
    
