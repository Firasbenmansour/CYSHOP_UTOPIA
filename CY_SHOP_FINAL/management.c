#include "management.h"
#include "structures.h"
#define MAX_STORE_STORAGE 10000 


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
    FILE *fp = fopen("product_m.txt", "w");
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
        while (getchar() != '\n');
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

    // Read reference number input + make sure the input is an integer
    while (scanf("%d", &ref_num) != 1) {
        printf("Invalid input. Please enter a valid reference number: ");
        while (getchar() != '\n');
    }

    int found = 0;

    // Search for the product with the given reference number
    for (int i = 0; i < num_products; i++) {
        if (products[i].ref_num == ref_num) {
            // Print product information
            printf("Product: %s\n", products[i].name);
            printf("Reference number: %d\n", products[i].ref_num);
            printf("Quantity: %d\n", products[i].quantity);
            printf("Size: %d\n", products[i].size);
            printf("Price: %f\n", products[i].price);
            printf("\n----------\n");

            // Prompt for further action
            printf("1. Continue\n");
            printf("2. Go back to the management menu\n");
            printf("3. Exit the shop\n");

            // Read and validate the user's choice
            while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
                printf("Invalid choice. Please enter a number between 1 and 3: ");
                while (getchar() != '\n');
            }

            // Perform the selected action based on the user's choice
            if (choice == 1) {
                showStock(products, num_products);
            }
            else if (choice == 2) {
                managementMode();
            }
            else if (choice == 3) {
                printf("\nQuitting...\n");
                exit(0);
            }

            found = 1;
            break;
        }
    }

    // If the product is not found
    if (!found) {
        printf("Product not found.\n");
        printf("\n----------\n");

        // Prompt for further action
        printf("1. Retry\n");
        printf("2. Go back to the management menu\n");
        printf("3. Exit the shop\n");

        // Read and validate the user's choice
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
            printf("Invalid choice. Please enter a number between 1 and 3: ");
            while (getchar() != '\n');
        }

        // Perform the selected action based on the user's choice
        if (choice == 1) {
            showStock(products, num_products);
        }
        else if (choice == 2) {
            managementMode();
        }
        else if (choice == 3) {
            printf("\nQuitting...\n");
            exit(0);
        }
    }
}




void managementMode() {
    int choice;
    printf("\n--- MANAGEMENT MODE ---\n");

    // Open the file containing product information
    FILE *fp = fopen("product_m.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Read the number of products
    int num_products;
    fscanf(fp, "%d", &num_products);

    // Allocate memory for the products
    Product *products = malloc(num_products * sizeof(Product));

    // Read product information from the file
    for (int i = 0; i < num_products; i++) {
        fscanf(fp, "%d %s %d %d %f", &products[i].ref_num, products[i].name, &products[i].quantity, &products[i].size, &products[i].price);
    }

    // Close the file
    fclose(fp);

    // Show stock info
    Showrestockneeds(products, num_products);
    showLowestStock(products, num_products);
    ShowRemainingSpace(products, num_products);

    printf("1. Display the stock of a product\n");
    printf("2. Increase the stock of a product\n");
    printf("3. BACK\n");
    
    // Read and validate the user's choice
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
        printf("Invalid choice. Please enter a number between 1 and 3: ");
        while (getchar() != '\n'); //clear buffer
    }

    // Perform the selected operation based on the user's choice
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
