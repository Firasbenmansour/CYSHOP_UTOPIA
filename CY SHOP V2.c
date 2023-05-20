#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX_STORE_STORAGE 1000 

typedef enum { SMALL, MEDIUM, LARGE } ProductSize;

typedef struct{
char name[50];
char lname[50];
char id[50];
char password[50];
int isSignedIn; 
 }Login; 

typedef struct {
char        name[50];
int         ref_num;
int         quantity;
float       price;
ProductSize size;
} Product;

typedef struct{
char name[50];
char surname[50];
int  purchase_history[100];
int  num_purchases;
}Customer;

void managementMode();

//  Affichage du menu principal //
void showMenu() {
    printf("--- MAIN MENU ---\n");
    printf("1. MANAGEMENT MODE\n");
    printf("2. BUYING MODE\n");
    printf("3. LEAVE\n");
}

//login //
void logorsignin(Login *a) {
    int login;
    char id[50];
    char password[50];
    char name[50];
    char lname[50];
    char sid[50];
    char spassword[50];
    int r = 0;

    printf("\nHello\n");
    printf("1. Login\n");
    printf("2. Sign up\n");
    printf("3. Back\n");
    scanf("%d", &login);

    switch (login) {
        case 1:
            printf("What is your id?\n");
            scanf("%s", id);
            printf("What is your password?\n");
            scanf("%s", password);
            FILE *fichier_login = fopen("idandpassword.txt", "r");
            if (fichier_login == NULL) {
                exit(1);
            } else {
                while (fscanf(fichier_login, "%s %s %s %s", a->name, a->lname, a->id, a->password) !=EOF) {
                    if (strcmp(id, a->id) == 0 && strcmp(password, a->password) == 0) {
                        printf("You are connected\n");
                        r = 1;
                        a->isSignedIn = 1;
                    }
                }
                if (r != 1) {
                    printf("Your id or your password is incorrect\n");
                    a->isSignedIn = 0;
                }
            }
            fclose(fichier_login);
            break;
        case 2:
            printf("What is your first name?\n");
            scanf("%s", name);
            printf("What is your last name?\n");
            scanf("%s", lname);
            printf("Choose an id\n");
            scanf("%s", sid);
            printf("Choose a password\n");
            scanf("%s", spassword);

            FILE *fichier_signup = fopen("idandpassword.txt", "a");
            if (fichier_signup == NULL) {
                exit(1);
            } else {
                fprintf(fichier_signup, "\n%s %s %s %s", name, lname, sid, spassword);
                fclose(fichier_signup);
                a->isSignedIn = 1;
                printf("Sign up successful. You are now signed in.\n");
            }
            break;
        case 3:
            printf("Going back...\n");
            main();
        default:
            printf("Error: Choose a correct option.\n");
            break;
    }
} 

void Showrestockneeds(Product products[], int num_products) {
    printf("\n--- Products with 0 stock ---\n");
    int zero_stock = 0;
    for (int i = 0; i < num_products; i++) {
        if (products[i].quantity == 0) {
            printf("%s (ref: %d)\n", products[i].name, products[i].ref_num);
            zero_stock += 1;
        }
    }
    if (zero_stock==0) {
        printf("No products with 0 stock.\n");
    }
}
void swap(Product *a, Product *b) {
    Product temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Product *products, int low, int high) {
    int pivot = products[high].quantity;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (products[j].quantity < pivot) {
            i++;
            swap(&products[i], &products[j]);
        }
    }
    swap(&products[i + 1], &products[high]);
    return (i + 1);
}

void quicksort(Product *products, int low, int high) {
    if (low < high) {
        int pi = partition(products, low, high);
        quicksort(products, low, pi - 1);
        quicksort(products, pi + 1, high);
    }
}

void showLowestStock(Product *products, int numProducts) {
    int count = 0;
    quicksort(products, 0, numProducts - 1);
    printf("Products with the lowest stock:\n");
    for (int i = 0; i < numProducts && count < 5; i++) {
        if (products[i].quantity > 0) {
            printf("%d. %s (reference number %d) - %d in stock\n", count + 1,
                   products[i].name, products[i].ref_num, products[i].quantity);
            count++;
        }
    }
    if (count == 0) {
        printf("No products with stock found.\n");
    }
}

void ShowRemainingSpace(Product products[], int num_products) {
    int total_area = 0;
    for (int i = 0; i < num_products; i++) {
        switch (products[i].size) {
            case SMALL:
                total_area += 1;
                break;
            case MEDIUM:
                total_area += 2;
                break;
            case LARGE:
                total_area += 4;
                break;
        }
    }
    int remaining_area = MAX_STORE_STORAGE - total_area;
    printf("\n--- Remaining space in store ---\n");
    printf("Total store area: %d\n", MAX_STORE_STORAGE);
    printf("Area used by products: %d\n", total_area);
    printf("Remaining area: %d\n", remaining_area);
}

void increaseStock(Product *products, int num_products) {
    int ref_num, quantity;
    int choice;
    printf("Enter the reference number of the product you want to restock: ");
    scanf("%d", &ref_num);

    int found = 0; 
    for (int i = 0; i < num_products; i++) {
        if (products[i].ref_num == ref_num) {
            found = 1;
            printf("Enter the quantity to be restocked: ");
            scanf("%d", &quantity);
            int totalStock = 0;
            for (int j = 0; j < num_products; j++) {
                if (products[j].ref_num == ref_num) {
                totalStock += products[j].quantity;
              }
            }
            if (totalStock + quantity > MAX_STORE_STORAGE) {
                printf("Cannot restock. Exceeds maximum stock capacity.\n");
                return;
            }

            products[i].quantity += quantity;
            printf("%d units of %s have been added to the stock.\n", quantity, products[i].name);
            break; 
        }
    }

    if (!found) {
        printf("Product not found.\n");
        return;
    }

    FILE *fp = fopen("products.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Write the updated product information to the file
    fprintf(fp, "%d\n", num_products);
    for (int i = 0; i < num_products; i++) {
        fprintf(fp, "%d %s %d %d %f\n", products[i].ref_num, products[i].name, products[i].quantity, products[i].size, products[i].price);
    }
    fclose(fp);

    printf("\n----------\n");
    printf("1. Continue\n");
    printf("2. Go back to the management menu\n");
    printf("3. Exit the shop\n");
    scanf("%d", &choice);
    do {
              switch (choice) {
            case 1:
                return;
                break;
            case 2:
                managementMode();
                break;
            case 3:
                printf("\nQuitting...\n");
                exit (0);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    } while (choice != 3);

    printf("\nQuitting...\n");
    exit(0);
}
void showStock(Product *products, int num_products) {
    int ref_num;
    int choice;
    printf("Enter the reference number of the product you want to view: ");
    scanf("%d", &ref_num);
    for (int i = 0; i < num_products; i++) {
        if (products[i].ref_num == ref_num) {
            printf("Product: %s\n", products[i].name);
            printf("Reference number: %d\n", products[i].ref_num);
            printf("Quantity: %d\n", products[i].quantity);
            printf("Size: %d\n", products[i].size);
            printf("Price: %f\n", products[i].price);
            printf("\n----------\n");
            printf("1. Continue \n");
            printf("2. Go back to the manegement menu \n");
            printf("3. exit the shop \n");
            scanf("%d", &choice);
            do {
              switch (choice) {
            case 1:
                return;
                break;
            case 2:
                managementMode();
                break;
            case 3:
                printf("\nQuitting...\n");
                exit (0);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    } while (choice != 3);
        }
    }
    printf("Product not found.\n");
}
//  Mode gestion //
void managementMode() {
    int choice;
    // Login a;
    // logorsignin(&a);
    // if (a.isSignedIn==1) {
    printf("\n--- MANAGEMENT MODE ---\n");
    FILE *fp = fopen("products.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    int num_products;
    fscanf(fp, "%d", &num_products);
    Product *products = malloc(num_products * sizeof(Product));
    for (int i = 0; i < num_products; i++) {
        fscanf(fp, "%d %s %d %d %f", &products[i].ref_num, products[i].name, &products[i].quantity, &products[i].size, &products[i].price);
    }
    fclose(fp);

    Showrestockneeds(products, num_products);
    showLowestStock(products, num_products);
    ShowRemainingSpace(products, num_products);

    printf("1. Display the stock of a product\n");
    printf("2. Increase the stock of a product\n");
    printf("3. BACK\n");
    scanf("%d", &choice);
    free(products);
    do {
        switch (choice) {
            case 1:
                showStock(products, num_products);
                break;
            case 2:
                increaseStock(products, num_products);
                break;
            case 3:
                printf("\nExiting management mode...\n");
                return;
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    } while (choice!=3);
   // }
   // else{
   //   logorsignin(&a);
   // }
}



// enregistrement des infos du client dans le fichier "client.txt" //
void save_customer(Customer c){
  FILE *client_file = fopen("client.txt", "w");
    if (client_file == NULL) {
        printf("Failed to open client file\n");
        exit(1);
    }
    fprintf(client_file, "%s,%s,", c.name, c.surname);
    for (int i = 0; i < c.num_purchases; i++) {
        fprintf(client_file, "%d,", c.purchase_history[i]);
    }
    fprintf(client_file, "\n");
    fclose(client_file);
}


////////////////
int main(void) {
    int choice;
     printf("\nWELCOME TO UTOPIA !\n\n");
   do {
        showMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                managementMode();
                break;
            // case 2:
            //     buyingMode();
            //     break;
            case 3:
                printf("Merci d'avoir visité notre magasin. À bientôt !");
                break;
            default:
                printf("Choix invalide. Veuillez saisir un choix valide.\n");
                break;
        }
    } while (choice != 3);
  return 0;
}
