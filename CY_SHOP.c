#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX_STORE_STORAGE 10000 

typedef enum { SMALL, MEDIUM, LARGE } ProductSize;

typedef struct{
char name[50];
char lname[50];
char id[50];
char password[50];
int isSignedIn; 
int mode;
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
            FILE *fichier_login;

            fichier_login = fopen("idandpassword.txt", "r");

            if (fichier_login == NULL) {
                printf("Error opening login file.\n");
                exit(0);
            } else {
                while (fscanf(fichier_login, "%s %s %s %s %d", a->name, a->lname, a->id, a->password, &a->mode) != EOF) {
                    if (strcmp(id, a->id) == 0 && strcmp(password, a->password) == 0) {
                        printf("You are connected\n");
                        r = 1;
                        a->isSignedIn = 1;
                        break;
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
            // New user sign up
            printf("What is your first name?\n");
            scanf("%s", name);
            printf("What is your last name?\n");
            scanf("%s", lname);
            int test = 0;

            // Loop to make sure every user has a different ID
            do {
                printf("Choose an ID\n");
                scanf("%s", sid);

                FILE *fichier_signup_check;
                fichier_signup_check = fopen("idandpassword.txt", "r");

                if (fichier_signup_check == NULL) {
                    printf("Error opening login file.\n");
                    exit(1);
                } else {
                    test = 1;
                    while (fscanf(fichier_signup_check, "%s %s %s %s %d", a->name, a->lname, a->id, a->password, &a->mode) != EOF) {
                        if (strcmp(sid, a->id) == 0) {
                            printf("ID already in use. Please choose another ID.\n");
                            test = 0;
                            break;
                        }
                    }
                }

                fclose(fichier_signup_check);
            } while (test == 0);

            printf("Choose a password\n");
            scanf("%s", spassword);
            printf("Choose your mode:\n");
            printf("1. Management\n");
            printf("2. Buying\n");
            scanf("%d", &a->mode);

            FILE *fichier_signup;
            fichier_signup = fopen("idandpassword.txt", "a");

            if (fichier_signup == NULL) {
                printf("Error opening signup file.\n");
                exit(1);
            } else {
                fprintf(fichier_signup, "%s %s %s %s %d\n", name, lname, sid, spassword, a->mode);
                fclose(fichier_signup);
                a->isSignedIn = 1;
                printf("Sign up successful. You are now signed in.\n");
            }

            // Create a client file for the new user and store user information
            char filename[100];
            sprintf(filename, "%s.txt", sid);
            FILE *client_file = fopen(filename, "w");

            if (client_file == NULL) {
                printf("Error creating client file.\n");
                exit(1);
            } else {
                fprintf(client_file, "%s %s %s %s %d\n", name, lname, sid, spassword, a->mode);
                fclose(client_file);
            }

            // Reopen idandpassword.txt to update the Login structure with the new user's information
            FILE *fichier_login_new;
            fichier_login_new = fopen("idandpassword.txt", "r");
            if (fichier_login_new == NULL) {
                printf("Error opening login file.\n");
                exit(0);
            } else {
                while (fscanf(fichier_login_new, "%s %s %s %s %d", a->name, a->lname, a->id, a->password, &a->mode) != EOF) {
                    if (strcmp(sid, a->id) == 0 && strcmp(spassword, a->password) == 0) {
                        printf("You are connected\n");
                        r = 1;
                        a->isSignedIn = 1;
                        break;
                    }
                }
                if (r != 1) {
                    printf("Your id or your password is incorrect\n");
                    a->isSignedIn = 0;
                }
            }
            fclose(fichier_login_new);
            break;
        case 3:
            printf("Quitting...\n");
            exit(0);
        default:
            printf("Error: Choose a correct option.\n");
            break;
    }
}

void Showrestockneeds(Product products[], int num_products) {
    printf("\n--- Products with 0 stock ---\n");
    int zero_stock = 0;
    for (int i = 1; i < num_products; i++) {
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
        total_area += products[i].quantity * products[i].size;
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

            int totalStorageNeeded = quantity * products[i].size;
            int totalStorageAvailable = 0;

            for (int j = 0; j < num_products; j++) {
                totalStorageAvailable += products[j].quantity * products[j].size;
            }

            if (totalStorageNeeded > (MAX_STORE_STORAGE - totalStorageAvailable)) {
                printf("Cannot restock. Exceeds maximum stock capacity.\n");
                increaseStock(products,num_products);
            }

            products[i].quantity += (quantity * products[i].size);
            printf("%d units of %s have been added to the stock.\n", quantity, products[i].name);
            break;
        }
    }

    if (!found) {
        printf("Product not found.\n");
        printf("\n----------\n");
        printf("1. Retry\n");
        printf("2. Go back to the management menu\n");
        printf("3. Exit the shop\n");
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
            printf("Invalid choice. Please enter a number between 1 and 3: ");
            // Clear the input buffer
            while (getchar() != '\n');
        }
        if (choice == 1) {
            increaseStock(products, num_products);  // Retry the function
        } else if (choice == 2) {
            return;  // Return back to the management mode
        } else if (choice == 3) {
            printf("\nQuitting...\n");
            exit(0);
        }
    }
    FILE *fp = fopen("products2.txt", "w");
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

    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
        printf("Invalid choice. Please enter a number between 1 and 3: ");
    }

    if (choice == 1) {
        increaseStock(products, num_products);
    } else if (choice == 2) {
        managementMode();
    } else if (choice == 3) {
        printf("\nQuitting...\n");
        exit(0);
    }
}

void showStock(Product *products, int num_products) {
    int ref_num;
    int choice;
    printf("Enter the reference number of the product you want to view: ");
    while (scanf("%d", &ref_num) != 1) {
        printf("Invalid input. Please enter a valid reference number: ");
        // Clear the input buffer
        while (getchar() != '\n');
    }
    int found = 0;
    for (int i = 0; i < num_products; i++) {
        if (products[i].ref_num == ref_num) {
            // Print product information
            printf("Product: %s\n", products[i].name);
            printf("Reference number: %d\n", products[i].ref_num);
            printf("Quantity: %d\n", products[i].quantity);
            printf("Size: %d\n", products[i].size);
            printf("Price: %f\n", products[i].price);
            printf("\n----------\n");
            printf("1. Continue\n");
            printf("2. Go back to the management menu\n");
            printf("3. Exit the shop\n");
            while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
                printf("Invalid choice. Please enter a number between 1 and 3: ");
                // Clear the input buffer
                while (getchar() != '\n');
            }
            if (choice == 1) {
                showStock(products,num_products);
            } else if (choice == 2) {
                managementMode();
            } else if (choice == 3) {
                printf("\nQuitting...\n");
                exit(0);
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Product not found.\n");
        printf("\n----------\n");
        printf("1. Retry\n");
        printf("2. Go back to the management menu\n");
        printf("3. Exit the shop\n");
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
            printf("Invalid choice. Please enter a number between 1 and 3: ");
            while (getchar() != '\n');
        }
        if (choice == 1) {
            showStock(products, num_products); 
        } else if (choice == 2) {
            managementMode();
        } else if (choice == 3) {
            printf("\nQuitting...\n");
            exit(0);
        }
    }
}


//  Mode gestion //
void managementMode() {
    int choice;
    printf("\n--- MANAGEMENT MODE ---\n");
    FILE *fp = fopen("products2.txt", "r");
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
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
        printf("Invalid choice. Please enter a number between 1 and 3: ");
    }
    if (choice == 1) {
        showStock(products, num_products);
    }
    else if (choice == 2) {
        increaseStock(products, num_products);
    }
    else if (choice == 3) {
                printf("\nExiting management mode...\n");
                free(products);
                return;
    }
}


void buying(char* clientID) {
    printf("Here is your buying cart\n\n");
    FILE* buyingcart = fopen("buy.txt", "r");
    if (buyingcart == NULL) {
        exit(1);
    }

    int num, i;
    int t = 0;
    float pricee = 0;
    int m = 0;
    Product a;
    while (fscanf(buyingcart, " %s %d %f", a.name, &a.ref_num, &a.price) == 3) {
        m = m + 1;
    }
    if (m == 0) {
        printf("There is NOTHING in your buying cart\n");
        t = 1;
    }
    else {
        num = m;

        Product* price = malloc(num * sizeof(Product));
        printf("Here are the articles that you want to buy\n\n");
        rewind(buyingcart);
        for (i = 0; i < num; i++) {
            fscanf(buyingcart, " %s %d %f", price[i].name, &price[i].ref_num, &price[i].price);
            printf("%s (ref: %d)    price: %.2f$\n ", price[i].name, price[i].ref_num, price[i].price);
        }
        for (i = 0; i < num; i++) {
            pricee = pricee + price[i].price;
        }

        printf("\n\n\nTotal price: %.2f\n", pricee);
        fclose(buyingcart);
        free(price);

        // Ask for confirmation
        printf("Confirm purchase? (1: Yes, 0: No): ");
        int confirm;
        scanf("%d", &confirm);

        if (confirm == 1) {
            // Open client's file
            char filename[100];
            sprintf(filename, "%s.txt", clientID);

            FILE* clientFile = fopen(filename, "a");
            if (clientFile == NULL) {
                printf("Error opening client file.\n");
                exit(1);
            }

            // Append purchased articles to the client's file
            buyingcart = fopen("buy.txt", "r");
            if (buyingcart == NULL) {
                printf("Error opening buying cart file.\n");
                exit(1);
            }

            while (fscanf(buyingcart, " %s %d %f", a.name, &a.ref_num, &a.price) == 3) {
                fprintf(clientFile, "\n%s %d %f", a.name, a.ref_num, a.price);
            }

            fclose(clientFile);
            fclose(buyingcart);
            t = 1;  // Purchase confirmed

            // Reset the buying cart
            FILE* resetBuy = fopen("buy.txt", "w");
            if (resetBuy == NULL) {
                printf("Failed to reset the buying cart.\n");
                return ;
            }
            fclose(resetBuy);
        }
        else {
            printf("Purchase canceled.\n");
        }
    }

    return ;
}



void buysomething(){
int c,i,d;
  char nameb[100];
  int ref_num;
  int h=0;
  printf("What do you want to buy?\n");
  FILE*buy=fopen("product.txt","r+");
  if (buy == NULL) {
  exit(1);
}
  int number;
  fscanf(buy,"%d",&number);
  Product*buyy=malloc(number*sizeof(Product));
  FILE*buycart=fopen("buy.txt","a");
  if (buycart == NULL) {
  exit(1);
}
  do{
    printf("1. Name of the article\n");
    printf("2. Reference number of the article\n");
    scanf("%d",&c);
    }while(c!=1 && c!=2);
  
  switch(c){
    case 1 :
    printf("What is the name of the article?\n");
    scanf("%s",nameb);
      for(i=0;i<number;i++){
    fscanf(buy,"%d %s %d %d %f",&buyy[i].ref_num,buyy[i].name,&buyy[i].quantity,&buyy[i].size,&buyy[i].price);
      if(strcmp(nameb,buyy[i].name)==0){
        
        fprintf(buycart,"\n%s %d %f",buyy[i].name,buyy[i].ref_num,buyy[i].price);
        printf("The article has been aded to cart\n");
          h=1;
        fclose(buycart);
      }
     
    }
      if(h==0){
        printf("We can't find the article\n");
      }
    break;

    case 2 :
      printf("What is the reference number of the article?\n");
    scanf("%d",&ref_num);
      for(i=0;i<number;i++){
    fscanf(buy,"%d %s %d %d %f",&buyy[i].ref_num,buyy[i].name,&buyy[i].quantity,&buyy[i].size,&buyy[i].price);
      if(ref_num==buyy[i].ref_num){
        fprintf(buycart,"\n%s %d %f",buyy[i].name,buyy[i].ref_num,buyy[i].price);
          h=1;
        printf("The article has been aded to cart\n");
        fclose(buycart);
      }
      
      }
     if(h==0){
        printf("We can't find the article\n");
      }
  }
}




void affiche_articlemenu(int a,int b){
  FILE*menu=fopen("product.txt","r+");
  if (menu == NULL) {
  exit(1);
}
    int num_productsss;
    fscanf(menu,"%d", &num_productsss);
    Product*prod=malloc(num_productsss*sizeof(Product));
    int i;
   
  for(i=0;i<num_productsss;i++){
    fscanf(menu,"%d %s %d %d %f",&prod[i].ref_num,prod[i].name,&prod[i].quantity,&prod[i].size,&prod[i].price);
  
    if(b==1){
       
      if(i>=1 && i<18){
      
     printf("%s (ref : %d)    price: %.2f$\n ",prod[i].name,prod[i].ref_num,prod[i].price);
    }
  }
    if(b==2){
       
       if(i>=18 && i<28){
    
    printf("%s (ref : %d)    price: %.2f$\n ",prod[i].name,prod[i].ref_num,prod[i].price);
     }
    }

     if(a==3){
        
       if(i>=28 && i<46){
    
    printf("%s (ref : %d)    price: %.2f$\n ",prod[i].name,prod[i].ref_num,prod[i].price);
     }
    }

     if(a==7){
        
       if(i>=46 && i<60){
   
    printf("%s (ref : %d)    price: %.2f$\n ",prod[i].name,prod[i].ref_num,prod[i].price);
     }
    }

     if(a==6){
        
       if(i>=60 && i<66){
    
    printf("%s (ref : %d)    price: %.2f$\n ",prod[i].name,prod[i].ref_num,prod[i].price);
     }
    }

     if(a==4){
        
       if(i>=66 && i<78){
    
    printf("%s (ref : %d)    price: %.2f$\n ",prod[i].name,prod[i].ref_num,prod[i].price);
     }
    }

     if(a==2){
        
       if(i>=78 && i<93){
    
    printf("%s (ref : %d)    price: %.2f$\n ",prod[i].name,prod[i].ref_num,prod[i].price);
     }
    }

     if(a==5){
        
       if(i>=93 && i<102){
    
    printf("%s (ref : %d)    price: %.2f$\n ",prod[i].name,prod[i].ref_num,prod[i].price);
     }
    }

 
    
  }
  fclose(menu);
  free(prod);
}

void searcharticle(){
  char name[100];
  int searching;
  int ref;
  char ser[50];
  int choice,choice2=0;
  int g=0;
  FILE*fichier=fopen("product.txt","r+");
  do{
  printf("How do you want to research?\n");
  printf("1. reference\n");
  printf("2. searching bar\n");
  printf("3. menu\n");
  scanf("%d",&searching);
  }while(searching<1 || searching>3);
  
switch(searching){
  case 1:   
printf("What is the reference ?\n");
scanf("%d", &ref);

FILE *reference = fopen("product.txt", "r");
if (reference == NULL) {
  exit(1);
}

int num_products;
fscanf(reference, "%d", &num_products);
Product *products = malloc(num_products * sizeof(Product));
for (int i = 0; i < num_products; i++) {
  fscanf(reference, "%d %s %d %d %f", &products[i].ref_num, products[i].name, &products[i].quantity, &products[i].size, &products[i].price);
  if (ref == products[i].ref_num) {
    printf("Here your article :\n");
    printf("%s (ref: %d): %.2f$\n", products[i].name, products[i].ref_num, products[i].price);
    g = 1;
    break;
  }
}
fclose(reference);
free(products);
if (g == 0) {
  printf("Sorry but we can't find your article.\n");
}
break;

  case 2:
printf("What do you search for?\n");
    scanf(" %[^\n]", name);
    printf("%s\n", name);

    FILE* search_file = fopen("product.txt", "r+");
    if (search_file == NULL) {
        printf("Failed to open the file.\n");
        exit(1);
    }
    int num_productss;
fscanf(search_file, "%d", &num_productss);
Product *productss = malloc(num_productss * sizeof(Product));
for (int i = 0; i < num_productss; i++) {
  fscanf(search_file, "%d %s %d %d %f", &productss[i].ref_num, productss[i].name, &productss[i].quantity, &productss[i].size, &productss[i].price);
  
  if (strcmp(name, productss[i].name)==0) {
    printf("Here your article :\n");
    printf("%s (ref: %d): %.2f$\n", productss[i].name, productss[i].ref_num,productss[i].price);
    g = 1;
    break;
  }
}
fclose(search_file);
free(productss);
if (g == 0) {
  printf("Sorry but we can't the article.\n");
}
  break;

  case 3:
        printf("Here is the menu\n");
         do{    
     printf("1. T-SHIRTS & POLOS\n");
     printf("2. SHIRTS\n");
     printf("3. SWEATS \n");
     printf("4. JEANS\n"); 
     printf("5. SHOES\n");
     printf("6. SNEAKERS\n");
     printf("7. JACKETS\n");
     printf("Choice : ");
     scanf("%d", &choice);
           if(choice<1 || choice>7){
             printf("Choose a correct option\n");
           }
     } while (choice<1 || choice>7);
    
   
    switch(choice){
      case 1 :
      do{
      printf("What do you want?\n");
      printf("1. T-SHIRTS\n");
      printf("2. POLOS\n");
      printf("Choice : ");
      scanf("%d",&choice2);
        if(choice2!=1 && choice2!=2){
          printf("Choose a correct option\n");
        }
      }while(choice2!=1 && choice2!=2);
        if(choice2==1){
          printf("Here is the T-SHIRTS that we offer\n");
        }
        else{
          printf("Here is the POLOS that we offer\n");
        }
      affiche_articlemenu(choice,choice2);
      break;

      case 2 :
         printf("Here is the SHIRTS that we offer\n");
      affiche_articlemenu(choice,choice2);
      break;

      case 3 :
         printf("Here is the SWEATS that we offer\n");
      affiche_articlemenu(choice,choice2);
      break;

      case 4 :
         printf("Here is the JEANS that we offer\n");
      affiche_articlemenu(choice,choice2);
      break;

      case 5 :
         printf("Here is the SHOES that we offer\n");
      affiche_articlemenu(choice,choice2);
      break;

      case 6 :
         printf("Here is the SNEAKERS that we offer\n");
      affiche_articlemenu(choice,choice2);
      break;

      case 7 :
         printf("Here is the JACKETS that we offer\n");
      affiche_articlemenu(choice,choice2);
      break;

      
      
    }

}
}



void purchasehistory(char* clientID){
    char filename[100];
    sprintf(filename, "%s.txt", clientID);

    FILE* client_file = fopen(filename, "r");
    if (client_file == NULL) {
        printf("Error opening client file.\n");
        exit(1);
    }

    char line[100];
    int isBuyingHistory = 0;

    // Skip lines until client information
    while (fgets(line, sizeof(line), client_file) != NULL) {
        if (strcmp(line, "\n") == 0) {
            break;
        }
    }

    printf("\n--- Purchase History ---\n\n");

    // Print the rest of the file as purchase history
    int hasHistory = 0;
    while (fgets(line, sizeof(line), client_file) != NULL) {
        if (strcmp(line, "\n") != 0) {
            printf("%s", line);
            hasHistory = 1;
        }
    }

    if (!hasHistory) {
        printf("No articles bought yet.\n");
    }
    fclose(client_file);
}




void deleteClient(char* clientID) {
    char filename[100];
    sprintf(filename, "%s.txt", clientID);

    // Check if the client file exists
    FILE* clientFile = fopen(filename, "r");
    if (clientFile == NULL) {
        printf("Client file does not exist.\n");
        return;
    }
    fclose(clientFile);

    // Confirmation
    int confirm;
    printf("Are you sure you want to delete your account? (1. Yes / 2. No): ");
    scanf("%d", &confirm);

    if (confirm == 1) {
        int provideFeedback;
        printf("Would you like to provide a reason for deleting your account? (1. Yes / 2. No): ");
        scanf("%d", &provideFeedback);

        // Ask for reason if requested
        char feedback[1000];
        if (provideFeedback == 1) {
            printf("Please provide a reason for deleting your account: ");
            scanf(" %[^\n]s", feedback);
        }

        // Delete the client file
        if (remove(filename) != 0) {
            printf("Failed to delete the client file.\n");
            return;
        }

        // Delete the client's login information from idandpassword.txt
        FILE* loginFile = fopen("idandpassword.txt", "r");
        FILE* tempFile = fopen("temp.txt", "w");

        if (loginFile == NULL || tempFile == NULL) {
            printf("Error opening login file.\n");
            return;
        }

        char name[50], lname[50], id[50], password[50];
        int mode;

        // Copy all clients' information to the temporary file except the one to be deleted
        while (fscanf(loginFile, "%s %s %s %s %d", name, lname, id, password, &mode) != EOF) {
            if (strcmp(clientID, id) != 0) {
                fprintf(tempFile, "%s %s %s %s %d\n", name, lname, id, password, mode);
            }
        }

        fclose(loginFile);
        fclose(tempFile);

        // Replace the original file with the temporary file
        if (remove("idandpassword.txt") != 0 || rename("temp.txt", "idandpassword.txt") != 0) {
            printf("Failed to update login information.\n");
            return;
        }

        // Save feedback in Feedback.txt if provided
        if (provideFeedback == 1) {
            FILE* feedbackFile = fopen("Feedback.txt", "a");
            if (feedbackFile == NULL) {
                printf("Failed to open feedback file.\n");
                return;
            }

            fprintf(feedbackFile, "%s: %s\n", clientID, feedback);
            fclose(feedbackFile);
        }

        printf("Your account has been deleted successfully.\n");
    } else {
        printf("Account deletion cancelled.\n");
    }
}



 void menubuy(char* clientId){
  int menuu;
   int s;
   purchasehistory(clientId);
   do{
   printf("\n\n---- BUYING MODE ----\n");
   printf("What do you want to do?\n");
   printf("1. Search for an article\n");
   printf("2. Add an article to cart\n");
   printf("3. Go to the buying cart\n");
   printf("4. Delete account\n");
   printf("5. Back\n");
     scanf("%d",&menuu);
     if(menuu<1 || menuu>5){
       printf("Choose a right option\n");
     }
   }while(menuu<1 || menuu>5);
   switch(menuu){
     case 1:
       searcharticle();
       printf("\n\n");
       menubuy(clientId);
           break;
     case 2:
       buysomething();
       printf("\n\n");
       menubuy(clientId);
           break;
     case 3 :
     buying(clientId);
       printf("\n\n");
     menubuy(clientId);
     case 4 :
     deleteClient(clientId);
      case 5:
      return;
   }
 }


int main(void) {
  while (1) {

  printf("\n WELCOME TO UTOPIA !\n\n");
  Login a;
  a.isSignedIn = 0;
  logorsignin(&a);

  if (a.isSignedIn == 1) {
    if (a.mode == 1) {
      managementMode();
    } else if (a.mode == 2) {
      menubuy(a.id);
    }
  }
  }

  return 0;
}
