#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_ITEMS 100
#define MAX_CUSTOMERS 100
#define MAX_ORDERS 100
#define MAX_INVOICE_ITEMS 100
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20


#define FILENAME_ITEMS "items.txt"
#define FILENAME_CUSTOMERS "customers.txt"
#define FILENAME_ORDERS "orders.txt"
#define FILENAME_INVOICE "invoice.txt"



struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char name[50];
    int age;
    char gender;
    char address[100];
};

struct Item {
    int id;
    char name[50];
    int quantity;
    float price;
};

struct Customer {
    int id;
    char name[50];
    int age;
    char telephone[15];
    char address[100];
};

struct Order {
    int orderId;
    int customerId;
    int itemId;
    int quantity;
    float totalPrice;
    char date[20];
};

struct InvoiceItem {
    int orderId;
    char customerName[50];
    char itemName[50];
    int quantity;
    float totalPrice;
    char date[20];
};


struct User users[MAX_USERS];
struct Item inventory[MAX_ITEMS];
struct Customer customers[MAX_CUSTOMERS];
struct Order orders[MAX_ORDERS];
struct InvoiceItem invoice[MAX_INVOICE_ITEMS];
int userCount = 0;
int itemCount = 0;
int customerCount = 0;
int orderCount = 0;
int invoiceCount = 0;
char admin_username[MAX_USERNAME_LENGTH] = "admin";
char admin_password[MAX_PASSWORD_LENGTH] = "admin";


void registerAccount();
void createAdminAccount();


int login();

void loadUsersFromFile();
void loadInventoryFromFile();
void loadCustomersFromFile();
void loadOrdersFromFile();
void loadInvoiceFromFile();


void saveInventoryToFile();
void saveCustomersToFile();
void saveOrdersToFile();
void saveInvoiceToFile();

void productMenu();
void customerMenu();
void orderMenu();
void printMenu();


void addItem();
void removeItem();
void searchItem();
void displayItem();

void addCustomer();
void updateCustomer();
void deleteCustomer();


void createOrder();
void removeOrder();
void updateOrder();


void viewInvoice();


void bToCBusinessMenu();
void srDealingWithCustomer();
void managerConfirmation();
void placementOrderByDeliveryBoy();


void clearScreen();


                                  //Main Part

int main() {
    clearScreen();

    createAdminAccount();
    
    loadUsersFromFile();
    loadInventoryFromFile();
    loadCustomersFromFile();
    loadOrdersFromFile();
    loadInvoiceFromFile();

    if (!login()) {
        printf("Login failed. Exiting...\n");
        return 1;
    }

    int choice;

    do {
        printf("                     <<<< HOME PAGE >>>>\n");
        printf("\t ==========================================\n");
        printf("1. Product Menu\n");
        printf("2. Customer Menu\n");
        printf("3. Order Menu\n");
        printf("4. B to C Business\n");
        printf("5. Print Menu\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                productMenu();
                break;
            case 2:
                customerMenu();
                break;
            case 3:
                orderMenu();
                break;
            case 4:
                bToCBusinessMenu();
                break;
            case 5:
                printMenu();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    saveInventoryToFile();
    saveCustomersToFile();
    saveOrdersToFile();
    saveInvoiceToFile();
    
    return 0;
}





void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


                           //Register and Login 


void registerAccount() {
    clearScreen();
    struct User newUser;
     printf("                <<<< Registration Page >>>>\n");
    printf("\t ==========================================\n");


    printf("Enter your Full name: \n");
    scanf("%s", newUser.name);

    printf("Enter your age: \n");
    scanf("%d", &newUser.age);

    printf("Enter your gender (M/F): \n");
    scanf(" %c", &newUser.gender);

    printf("Enter your address: \n");
    scanf("%s", newUser.address);

    printf("Enter a new username: \n");
    scanf("%s", newUser.username);

    printf("Enter a strong password (e.g., at least 8 characters with uppercase, lowercase, numbers, and special characters): ");
    scanf("%s", newUser.password);

    FILE *file = fopen("users.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s %s %d %c %s\n", newUser.username, newUser.password, newUser.name,
                newUser.age, newUser.gender, newUser.address);
        fclose(file);
        printf("Account registered successfully!\n");
        printf("Please remember your username and password for future login.\n");
    } else {
        printf("Error: Could not open file for writing.\n");
    }
}


void createAdminAccount() {
    char choice;

       printf("\t ==========================================\n");
    printf("\t          INVENTORY MANAGEMENT SYSTEM\n");
    printf("\t ==========================================\n");
    printf("                   Create Admin Account\n");
    printf("Do you want to register a new account? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        registerAccount();
    } else if (choice != 'n' && choice != 'N') {
        printf("Invalid choice. Please try again.\n");
        createAdminAccount();
    }

}





int login() {
    clearScreen();

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int found = 0;

    printf("                     <<<< LOGIN PAGE >>>>\n");
    printf("\t ==========================================\n");
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            found = 1;
            printf("Login successful!\n");
            return 1;
        }
    }

    if (!found) {
        printf("Invalid username or password. Please try again.\n");
        return 0;
    }
}




                               //Load From File


void loadUsersFromFile() {
    FILE *file = fopen("users.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s %s %d %c %s", users[userCount].username, users[userCount].password, users[userCount].name,
                      &users[userCount].age, &users[userCount].gender, users[userCount].address) != EOF) {
            userCount++;
        }
        fclose(file);
    } else {
        printf("Error: Could not open file for reading.\n");
    }
}

void loadInventoryFromFile() {
    FILE *file = fopen(FILENAME_ITEMS, "r");
    if (file != NULL) {
        while (fscanf(file, "%d %s %d %f", &inventory[itemCount].id, inventory[itemCount].name,
                      &inventory[itemCount].quantity, &inventory[itemCount].price) != EOF) {
            itemCount++;
        }
        fclose(file);
    }
}

void loadCustomersFromFile() {
    FILE *file = fopen(FILENAME_CUSTOMERS, "r");
    if (file != NULL) {
        while (fscanf(file, "%d %s %d %s %s", &customers[customerCount].id, customers[customerCount].name,
                      &customers[customerCount].age, customers[customerCount].telephone, customers[customerCount].address) != EOF) {
            customerCount++;
        }
        fclose(file);
    }
}

void loadOrdersFromFile() {
    FILE *file = fopen(FILENAME_ORDERS, "r");
    if (file != NULL) {
        while (fscanf(file, "%d %d %f", &orders[orderCount].customerId, &orders[orderCount].itemId,
                      &orders[orderCount].totalPrice) != EOF) {
            orderCount++;
        }
        fclose(file);
    }
}

void loadInvoiceFromFile() {
    FILE *file = fopen(FILENAME_INVOICE, "r");
    if (file != NULL) {
        while (fscanf(file, "%d %s %s %d %f %s", &invoice[invoiceCount].orderId, invoice[invoiceCount].customerName,
                      invoice[invoiceCount].itemName, &invoice[invoiceCount].quantity, &invoice[invoiceCount].totalPrice,
                      invoice[invoiceCount].date) != EOF) {
            invoiceCount++;
        }
        fclose(file);
    }
}




                                 //Save to File



void saveInventoryToFile() {
    FILE *file = fopen(FILENAME_ITEMS, "w");
    if (file != NULL) {
        for (int i = 0; i < itemCount; i++) {
            fprintf(file, "%d %s %d %.2f\n", inventory[i].id, inventory[i].name,
                    inventory[i].quantity, inventory[i].price);
        }
        fclose(file);
    }
}

void saveCustomersToFile() {
    FILE *file = fopen(FILENAME_CUSTOMERS, "w");
    if (file != NULL) {
        for (int i = 0; i < customerCount; i++) {
            fprintf(file, "%d %s %d %s %s\n", customers[i].id, customers[i].name, customers[i].age,
                    customers[i].telephone, customers[i].address);
        }
        fclose(file);
    }
}

void saveOrdersToFile() {
    FILE *file = fopen(FILENAME_ORDERS, "w");
    if (file != NULL) {
        for (int i = 0; i < orderCount; i++) {
            fprintf(file, "%d %d %.2f\n", orders[i].customerId, orders[i].itemId, orders[i].totalPrice);
        }
        fclose(file);
    }
}

void saveInvoiceToFile() {
    FILE *file = fopen(FILENAME_INVOICE, "w");
    if (file != NULL) {
        for (int i = 0; i < invoiceCount; i++) {
            fprintf(file, "%d %s %s %d %.2f %s\n", invoice[i].orderId, invoice[i].customerName,
                    invoice[i].itemName, invoice[i].quantity, invoice[i].totalPrice, invoice[i].date);
        }
        fclose(file);
    }
}



                                    // Home page 5 Menu



void productMenu() {
    clearScreen();
    int choice;

    do {
        printf("                   <<<< Product Menu >>>>\n");
        printf("\t ==========================================\n");
       
        printf("1. Add Item\n");
        printf("2. Remove Item\n");
        printf("3. Search Item\n");
        printf("4. Display Inventory\n");
        printf("5. Back to Home Page\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addItem();
                break;
            case 2:
                removeItem();
                break;
            case 3:
                searchItem();
                break;
            case 4:
                displayItem();
                break;
            case 5:
                printf("Returning to Home Page...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}




void customerMenu() {
    clearScreen();

    int choice;

    do {
        printf("                   <<<< Customer Menu >>>>\n");
        printf("\t ==========================================\n");
        
        printf("1. Add Customer\n");
        printf("2. Update Customer\n");
        printf("3. Delete Customer\n");
        printf("4. Back to Home Page\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                updateCustomer();
                break;
            case 3:
                deleteCustomer();
                break;
            case 4:
                printf("Returning to Home Page...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}



void orderMenu() {
    clearScreen();
    int choice;

    do {
        printf("                   <<<< Order Menu >>>>\n");
        printf("\t ==========================================\n");
       
        printf("1. Create Order\n");
        printf("2. Remove Order\n");
        printf("3. Update Order\n");
        printf("4. Back to Home Page\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                createOrder();
                break;
            case 2:
                removeOrder();
                break;
            case 3:
                updateOrder();
                break;
            case 4:
                printf("Returning to Home Page...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}


void printMenu() {
    clearScreen();
    int choice;

    do { 
        printf("                   <<<< Print Menu >>>>\n");
        printf("\t ==========================================\n");
        
        printf("1. Invoice\n");
        printf("2. Back to Home Page\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                viewInvoice();
                break;
            case 2:
                printf("Returning to Home Page...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 2);
}



                                  //Product Menu

void addItem() {
    clearScreen();
    if (itemCount >= MAX_ITEMS) {
        printf("Inventory is full. Cannot add more items.\n");
        return;
    }

    struct Item newItem;

    printf("Enter item ID: ");
    scanf("%d", &newItem.id);

    printf("Enter item name: ");
    scanf("%s", newItem.name);

    printf("Enter quantity: ");
    scanf("%d", &newItem.quantity);

    printf("Enter price: ");
    scanf("%f", &newItem.price);

    inventory[itemCount++] = newItem;

    printf("Item added successfully.\n");
}




void removeItem() {
    clearScreen();
    int id;
    int found = 0;

    printf("Enter ID of item to remove: ");
    scanf("%d", &id);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            found = 1;
            printf("Item removed: %s\n", inventory[i].name);
            for (int j = i; j < itemCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            itemCount--;
            break;
        }
    }

    if (!found)
        printf("Item with ID %d not found.\n", id);
}



void searchItem() {
    clearScreen();
    int id;
    int found = 0;

    printf("Enter ID of item to search: ");
    scanf("%d", &id);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            found = 1;
            printf("Item found:\n");
            printf("ID: %d\n", inventory[i].id);
            printf("Name: %s\n", inventory[i].name);
            printf("Quantity: %d\n", inventory[i].quantity);
            printf("Price: %.2f\n", inventory[i].price);
            break;
        }
    }

    if (!found)
        printf("Item with ID %d not found.\n", id);
}



void displayItem() {
    clearScreen();
    if (itemCount == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    printf("\nInventory:\n");
    printf("ID\tName\tQuantity\tPrice\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d\t%s\t%d\t\t%.2f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
}

                     
                                  //Customer Menu
                                   


void addCustomer() {
    clearScreen();
    if (customerCount >= MAX_CUSTOMERS) {
        printf("Customer limit reached. Cannot add more customers.\n");
        return;
    }

    struct Customer newCustomer;

    printf("Enter customer ID: ");
    scanf("%d", &newCustomer.id);

    printf("Enter customer name: ");
    scanf("%s", newCustomer.name);

    printf("Enter customer age: ");
    scanf("%d", &newCustomer.age);

    printf("Enter customer telephone: ");
    scanf("%s", newCustomer.telephone);

    printf("Enter customer address: ");
    scanf("%s", newCustomer.address);

    customers[customerCount++] = newCustomer;

    printf("Customer added succcessfully.\n");
}




void updateCustomer() {
    clearScreen();
    int id;
    int found = 0;

    printf("Enter ID of customer to update: ");
    scanf("%d", &id);

    for (int i = 0; i < customerCount; i++) {
        if (customers[i].id == id) {
            found = 1;
            printf("Enter updated name: ");
            scanf("%s", customers[i].name);

            printf("Enter updated age: ");
            scanf("%d", &customers[i].age);

            printf("Enter updated telephone: ");
            scanf("%s", customers[i].telephone);

            printf("Enter updated address: ");
            scanf("%s", customers[i].address);

            printf("Customer details updated successfully.\n");
            break;
        }
    }

    if (!found)
        printf("Customer with ID %d not found.\n", id);
}




void deleteCustomer() {
    clearScreen();
    int id;
    int found = 0;

    printf("Enter ID of customer to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < customerCount; i++) {
        if (customers[i].id == id) {
            found = 1;
            printf("Customer removed: %s\n", customers[i].name);
            for (int j = i; j < customerCount - 1; j++) {
                customers[j] = customers[j + 1];
            }
            customerCount--;
            break;
        }
    }

    if (!found)
        printf("Customer with ID %d not found.\n", id);
}


                                  //Order Menu
                                 


void createOrder() {
    clearScreen();
    int customerId, itemId, quantity;
    char date[20];

    printf("Available Products:\n");
    displayItem();
    printf("Enter Customer ID: ");
    scanf("%d", &customerId);

    printf("Enter Item ID: ");
    scanf("%d", &itemId);

    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%s", date);

    if (inventory[itemId - 1].quantity < quantity) {
        printf("Requested quantity is not available in inventory.\n");
        return;
    }

    float totalPrice = inventory[itemId - 1].price * quantity;

    inventory[itemId - 1].quantity -= quantity;

    orders[orderCount].orderId = orderCount + 1; 
    orders[orderCount].customerId = customerId;
    orders[orderCount].itemId = itemId;
    orders[orderCount].quantity = quantity; 
    orders[orderCount].totalPrice = totalPrice;
    strcpy(orders[orderCount].date, date);
    orderCount++;

    
    char customerName[50]; 
    strcpy(customerName, customers[customerId - 1].name);


    invoice[invoiceCount].orderId = orders[orderCount - 1].orderId; 
    strcpy(invoice[invoiceCount].customerName, customerName); 
    strcpy(invoice[invoiceCount].itemName, inventory[itemId - 1].name);
    invoice[invoiceCount].quantity = quantity;
    invoice[invoiceCount].totalPrice = totalPrice;
    strcpy(invoice[invoiceCount].date, date);
    invoiceCount++;

    printf("Order #%d created successfully.\n", orders[orderCount - 1].orderId);
}






void removeOrder() {
    clearScreen();
    int orderId;
    printf("Enter Order ID to remove: ");
    scanf("%d", &orderId);

    int found = 0;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            printf("Order removed successfully.\n");
            for (int j = i; j < orderCount - 1; j++) {
                orders[j] = orders[j + 1];
            }
            orderCount--;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Order not found.\n");
    }
}



void updateOrder() {
    clearScreen();
    int orderId, newQuantity;
    printf("Enter Order ID to update: ");
    scanf("%d", &orderId);

    int found = 0;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            printf("Enter new quantity: ");
            scanf("%d", &newQuantity);

          
            for (int j = 0; j < itemCount; j++) {
                if (inventory[j].id == orders[i].itemId) {
                    orders[i].totalPrice = inventory[j].price * newQuantity;
                    break;
                }
            }

            printf("Order updated successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Order not found.\n");
    }
}

                                  //Print Menu
                                  


void viewInvoice() {
    clearScreen();
    printf("                             <<<< INVOICE >>>>\n");
    printf("\t            ==========================================\n");
    printf("Order ID\tCustomer Name\tItem Name\tQuantity\tTotal Price\tDate\n");
    for (int i = 0; i < invoiceCount; i++) {
        printf("%d\t\t%s\t\t%s\t\t%d\t\t%.2f\t\t%s\n", invoice[i].orderId, invoice[i].customerName,
                invoice[i].itemName, invoice[i].quantity, invoice[i].totalPrice, invoice[i].date);
    }
}



                                              // B To C menu



void bToCBusinessMenu() {
    clearScreen();
    int choice;

    do {
        printf("                  <<<< B To C Menu >>>>\n");
        printf("\t ==========================================\n");
       
        printf("1. SR Dealing with Customer\n");
        printf("2. Manager Confirmation\n");
        printf("3. Placement Ordered by Delivery Boy\n");
        printf("4. Back to Home Page\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                srDealingWithCustomer();
                break;
            case 2:
                managerConfirmation();
                break;
            case 3:
                placementOrderByDeliveryBoy();
                break;
            case 4:
                printf("Returning to Home Page...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}



void srDealingWithCustomer() {
    clearScreen();
    
    printf("Available Products:\n");
    displayItem();

    struct Customer customer;
    printf("Enter Customer ID: ");
    scanf("%d", &customer.id);

    printf("Enter Customer Name: ");
    scanf("%s", customer.name);

    printf("Enter Shop Name: ");
    scanf("%s", customer.address);  

    printf("Enter Customer Address: ");
    scanf("%s", customer.address);

    struct Order order;
    order.customerId = customer.id;
    
    printf("Enter Item ID: ");
    scanf("%d", &order.itemId);

    printf("Enter Quantity: ");
    scanf("%d", &order.quantity);

    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%s", order.date);

    float totalPrice = 0;
    int itemFound = 0;
    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == order.itemId) {
            if (inventory[i].quantity >= order.quantity) {
                totalPrice = inventory[i].price * order.quantity;
                inventory[i].quantity -= order.quantity;
                itemFound = 1;
            } else {
                printf("Not enough stock for Item ID %d\n", order.itemId);
                return;
            }
            break;
        }
    }

    if (!itemFound) {
        printf("Item with ID %d not found.\n", order.itemId);
        return;
    }

    order.totalPrice = totalPrice;
    order.orderId = ++orderCount; 
    orders[orderCount - 1] = order; 

    struct InvoiceItem newInvoice;
    newInvoice.orderId = order.orderId;
    strcpy(newInvoice.customerName, customer.name);
    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == order.itemId) {
            strcpy(newInvoice.itemName, inventory[i].name);
            break;
        }
    }
    newInvoice.quantity = order.quantity;
    newInvoice.totalPrice = totalPrice;
    strcpy(newInvoice.date, order.date);
    invoice[invoiceCount++] = newInvoice;

    printf("Order #%d created successfully.\n", order.orderId);
}





void managerConfirmation() {
    clearScreen();
    int orderId;
    printf("Enter Order ID to confirm: ");
    scanf("%d", &orderId);

    int found = 0;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            found = 1;
            printf("Order #%d is confirmed.\n", orderId);
            break;
        }
    }

    if (!found) {
        printf("Order ID %d not found.\n", orderId);
    }
}


void placementOrderByDeliveryBoy() {
    clearScreen();
    int orderId;
    printf("Enter Order ID to place: ");
    scanf("%d", &orderId);

    int found = 0;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            found = 1;
            printf("Order #%d is placed by the delivery boy.\n", orderId);
            break;
        }
    }

    if (!found) {
        printf("Order ID %d not found.\n", orderId);
    }
}




