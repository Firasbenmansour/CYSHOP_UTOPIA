#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX_STORE_STORAGE 1000 

typedef enum { SMALL, MEDIUM, LARGE } ProductSize;


/////////////////
typedef struct{
char name[50];
char lname[50];
char id[50];
char password[50];
 }Login; 

typedef struct {
    char name[50];
    int ref_num;
    int quantity;
    float price;
    ProductSize size;
} Product;

typedef struct{
       char name[50];
       char surname[50];
       int purchase_history[100];
       int num_purchases;
}Customer;

void managementMode();

//  Affichage du menu principal //
void showMenu() {
    printf("\n--- MAIN MENU ---\n");
    printf("1. MANAGEMENT MODE\n");
    printf("2. BUYING MODE\n");
    printf("3. LEAVE\n");
}

 
// login 1 //
// void login(){
//     int choice;
//     do {
//         printf("\n--- LOGIN ---\n");
//         printf("1. LOG IN TO YOUR ACCOUNT\n");
//         printf("2. REGISTER\n");
//         printf("3. LEAVE\n");
//         scanf("%d", &choice);
//         switch (choice) {
//             case 1:
//                 existing_account();
//                 break;
//             case 2:
//                 create_account();
//                 break;
//             case 3:
//                 printf("Thank you for visiting our store. See you soon !");
//                 break;
//             default:
//                 printf("Invalid choice. Please enter a valid option.\n");
//                 break;
//         }
//     } while (choice != 3);
// }

//login version 2//
void logorsignin(Login a){
  char login[50];
  char id[50];
  char password[50];
  char name[50];
  char lname[50];
  char sid[50];
  char spassword[50];
  int r=0; 
  
printf("Hello\n");
printf("What do you want to do?\n");
printf("Login or sign up\n");
scanf("%[^\n]",login);

  if(strcmp(login,"Login")==0){
      printf("What is your id?\n");
      scanf("%s",id);
      printf("What is your password?\n");
      scanf("%s",password);
      FILE *fichier=fopen("idandpassword.txt","r");
      if(fichier==NULL){
      exit(1);
      }
      else{
        while(fscanf(fichier,"%s %s %s %s",a.name,a.lname,a.id,a.password)!=EOF){
        
          if(strcmp(id,a.id)==0 &&         strcmp(password,a.password)==0){
          printf("You are connected\n");
            r=1;
            
          }
            
          }
        if(r!=1){
          printf("Your id or your password is incorrect");
        }
      }
     fclose(fichier); 
  } 
   
  else if(strcmp(login,"sign up")==0){
    printf("What is your first name?\n");
    scanf("%s",name);
    printf("What is your last name?\n");
    scanf("%s",lname);
    printf("Choose a an id\n");
    scanf("%s",sid);
    printf("Choose a password\n");
    scanf("%s",spassword);
    
    FILE *fichier=fopen("idandpassword.txt","a");
      if(fichier==NULL){
      exit(1);
      }
      else{
        //fseek(fichier,SEEK_END,SEEK_SET);
        fprintf(fichier,"\n%s %s %s %s",name,lname,sid,spassword);
      }
    fclose(fichier);
  }
  
  else {
    printf("Erreur choose a correct option");
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
    FILE *fp = fopen("products.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < num_products; i++) {
        if (products[i].ref_num == ref_num) {
            printf("Enter the quantity to be restocked: ");
            scanf("%d", &quantity);
            products[i].quantity += quantity;
            printf("%d units of %s have been added to the stock.\n", quantity, products[i].name);
            fprintf(fp, "%d\n", num_products);
            for (int i = 0; i < num_products; i++) {
            fprintf(fp, "%d %s %d %d %f\n", products[i].ref_num, products[i].name, products[i].quantity, products[i].size, products[i].price);
            }
            fclose(fp);
            free(products);
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
    // logorsignin(a);
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
    } while (choice != 3);
}

// mode achat //
// void buyingMode() {    
//     int choice;
//     login a;
//     logorsignin(a);
//     printf("\n--- BUYING MODE ---\n");
//     printf("1. T-SHIRTS & POLOS\n");
//     printf("2. SHIRTS\n");
//     printf("3. SWEATS & HOODIES\n");
//     printf("4. JEANS\n"); 
//     printf("5. PANTS\n");
//     printf("6. SHOES\n");
//     printf("7. SNEAKERS\n");
//     printf("8. JACKETS\n");
//     printf("Choix : ");
//     scanf("%d", &choice);
//     do{
//     switch (choice) {
//         case 1:
//             ();
//             break;
//         case 2:
//             ();
//             break;
//         case 3:
//             ();
//             break;
//         case 4:
//             ();
//             break;
//         case 5:
//             ();
//             break;
//         case 6:
//             ();
//             break;
//         case 7:
//             ();
//             break;
//         case 8:
//             ();
//         default:
//             printf("Choix invalide. Veuillez saisir un choix valide.\n");
//             break;
//         }
//     } while (choice != 8);  
// }
     



// enregistrement des infos du produit dans le fichier "product.txt" //
void save_product(Product p){
     FILE* product_file = NULL;
     product_file = fopen("product.txt", "w");  // ouverture du fichier test.txt en lecture/écriture //
     if(product_file==NULL){ //test
        printf("Error in opening file");
        exit(1);
      }
      fprintf(product_file, "%s,%d,%d,%.2f,%d\n", p.name, p.ref_num, p.quantity, p.price, p.size);
      fprintf(product_file, "\n");
      fclose(product_file);
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
     printf("Bienvenue dans notre magasin !\n\n");
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
