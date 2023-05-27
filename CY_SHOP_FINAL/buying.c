#include "buying.h"
#include "structures.h"

void buying(char* clientID) {
    printf("Here is your buying cart\n\n");
    FILE* buyingcart = fopen("buy.txt", "r");
    if (buyingcart == NULL) {
        exit(1);
    }

    int num, i;
    float pricee = 0;
    int m = 0;
    Product a;
    // A loop to know the number of lines in the buy.txt files
    while (fscanf(buyingcart, " %s %d %f", a.name, &a.ref_num, &a.price) == 3) {
        m = m + 1;
    }
    if (m == 0) {
        printf("There is NOTHING in your buying cart\n");
    }
    else {
        num = m;

        Product* price = malloc(num * sizeof(Product));
        printf("Here are the articles that you want to buy\n\n");
        rewind(buyingcart);//Sets the file pointer at the beginning of the stream

      //Calculate the total price of the products to be purchased
        for (i = 0; i < num; i++) {
            fscanf(buyingcart, " %s %d %f", price[i].name, &price[i].ref_num, &price[i].price);
            printf("%s (ref: %d)    price: %.2f$\n ", price[i].name, price[i].ref_num, price[i].price);
        }
        for (i = 0; i < num; i++) {
            pricee = pricee + price[i].price;
        }

        printf("\n\n\nTotal price: %.2f$\n", pricee);
        fclose(buyingcart);
        free(price);

        // Ask for confirmation
        printf("Confirm purchase? (1: Yes, 0: No): ");
        int confirm;
        scanf("%d", &confirm);
        while (getchar() != '\n');
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
                fprintf(clientFile, "\n%s %d %.2f", a.name, a.ref_num, a.price);
            }

            fclose(clientFile);
            fclose(buyingcart);

            // Reset the buying cart
            FILE* resetBuy = fopen("buy.txt", "w");
            if (resetBuy == NULL) {
                printf("Failed to reset the buying cart.\n");
                return ;
            }
            fclose(resetBuy);
        }
        else {
          printf("Keep items in the cart? (1: Yes, 0: No): ");
            int keepItems;
            scanf("%d", &keepItems);
            while (getchar() != '\n');

            if (keepItems == 0) {
                // Reset the buying cart
                FILE* resetBuy = fopen("buy.txt", "w");
                if (resetBuy == NULL) {
                    printf("Failed to reset the buying cart.\n");
                    return;
                }
                fclose(resetBuy);
            }
            printf("Purchase canceled.\n");
        }
    }

    return ;
}



void buysomething(){
  int c,i;
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
  
  //Ask how the customer want to add their products in the buying cart
  do{
    printf("1. Name of the article\n");
    printf("2. Reference number of the article\n");
    scanf("%d",&c);
    while (getchar() != '\n');
  }while(c!=1 && c!=2);
  
  switch(c){
    case 1 :
      
    //Add a product in the buying cart by the name of the product
    printf("What is the name of the article?\n");
    scanf("%s",nameb);
        for(i=0;i<number;i++){
          fscanf(buy,"%d %s %d %d %f",&buyy[i].ref_num,buyy[i].name,&buyy[i].quantity,&buyy[i].size,&buyy[i].price);
          
          if(strcmp(nameb,buyy[i].name)==0){
            fprintf(buycart,"\n%s %d %f",buyy[i].name,buyy[i].ref_num,buyy[i].price);
            printf("The article has been aded to cart\n");
            h=1;
            fclose(buycart);
            fclose(buy);
          }
     
        }
        if(h==0){
        printf("We can't find the article\n");
        fclose(buycart);
        fclose(buy);
        }
  
    break;

    case 2 :
      
      //Add a product in the buying cart by the reference number of the product
      printf("What is the reference number of the article?\n");
      scanf("%d",&ref_num);
      while (getchar() != '\n');
      for(i=0;i<number;i++){
        fscanf(buy,"%d %s %d %d %f",&buyy[i].ref_num,buyy[i].name,&buyy[i].quantity,&buyy[i].size,&buyy[i].price);
        if(ref_num==buyy[i].ref_num){
            fprintf(buycart,"\n%s %d %.2f",buyy[i].name,buyy[i].ref_num,buyy[i].price);
            h=1;
            printf("The article has been aded to cart\n");
            fclose(buycart);
            fclose(buy);
        }
      }
      if(h==0){
        printf("We can't find the article\n");
        fclose(buycart);
        fclose(buy);
      }
 
    break;
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

   //Display a list of products by category based on the numbers entered in parameters
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
  int choice,choice2=0;
  int g=0;

  do{
  printf("How do you want to research?\n");
  printf("1. reference\n");
  printf("2. searching bar\n");
  printf("3. menu\n");
  scanf("%d",&searching);
  while (getchar() != '\n');
  }while(searching<1 || searching>3);
 //to search a product by a reference number
switch(searching){
  case 1:   
printf("What is the reference ?\n");
scanf("%d", &ref);
while (getchar() != '\n');
//Open the file with all the products
FILE *reference = fopen("product.txt", "r");
if (reference == NULL) {
  exit(1);
}
//Compares the references number entered by the user with those in the file
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
    //Compares the name entered by the user with those in the file
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
    //Displays a menu of products by category
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
    
    while (getchar() != '\n');
    //Depending on the category chosen we will use different numbers as parameters for the fonction affiche_articlemenu 
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
        while (getchar() != '\n');
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
  break;
 }
}



void purchasehistory(char* clientID){
    char filename[100];
    sprintf(filename, "%s.txt", clientID);
    //Open client file
    FILE* client_file = fopen(filename, "r");
    if (client_file == NULL) {
        printf("Error opening client file.\n");
        exit(1);
    }

    char line[100];

    // Skip lines with client information until the empty line
    while (fgets(line, sizeof(line), client_file) != NULL) {
        if (strcmp(line, "\n") == 0) {
            break;
        }
    }

    printf("\n--- Purchase History ---\n\n");

 int totalLines = 0;
    int lastThreeLines = 0;
  //Counts the total lines of produtcs purchased by customer
    while (fgets(line, sizeof(line), client_file) != NULL) {
        if (strcmp(line, "\n") != 0) {
        totalLines++;
        }
    }
    fseek(client_file, 0, SEEK_SET);  // Reset file pointer to the beginning

   // Skip lines with client information until the empty line
  while (fgets(line, sizeof(line), client_file) != NULL) {
        if (strcmp(line, "\n") == 0) {
            break;
        }

    //Display customer's last purchases with a maximum of three last products purchased
  if(totalLines==0){
    printf("No articles bought yet.\n");
  }
else{
    while (fgets(line, sizeof(line), client_file) != NULL) {
        if (strcmp(line, "\n") != 0) {
            lastThreeLines++;
        }
        if (lastThreeLines >= totalLines - 2 && strcmp(line, "\n") != 0) {
                printf("%s", line);
            }
     } 
   }
    fclose(client_file);
 }
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
    }
    else {
        printf("Account deletion cancelled.\n");
    }
}


void menubuy(char* clientId){
  int menuu;
   purchasehistory(clientId);

   //Display the buy mode menu, to choose an option until a right choice
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
     while (getchar() != '\n');
   }while(menuu<1 || menuu>5);

   //Will use different function according to user choice
   switch(menuu){
      case 1 :
       searcharticle();
       printf("\n\n");
       menubuy(clientId);
       break;
     
      case 2 :
       buysomething();
       printf("\n\n");
       menubuy(clientId);
       break;
     
      case 3 :
       buying(clientId);
       printf("\n\n");
       menubuy(clientId);
       break;
     
     case 4 :
       deleteClient(clientId);
       break;
     
    case 5 :
      return;
   }
}

