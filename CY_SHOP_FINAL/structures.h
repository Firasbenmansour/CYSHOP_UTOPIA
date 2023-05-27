#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include<string.h>



typedef struct{
char name[50];
char lname[50];
char id[50];
char password[50];
int isSignedIn; 
int mode;
 }Login; 

typedef struct {
    char name[50];
    int ref_num;
    int quantity;
    float price;
    int size;
} Product;

typedef struct {
    char name[50];
    char surname[50];
    int purchase_history[100];
    int num_purchases;
} Customer;

#endif