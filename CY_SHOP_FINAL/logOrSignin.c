#include "logOrSignin.h"
#include "structures.h"


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
    if(scanf("%d", &login) != 1) {
        printf("Error: Invalid input. Please enter a valid option.\n");
        while (getchar() != '\n');
        return;
    }
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