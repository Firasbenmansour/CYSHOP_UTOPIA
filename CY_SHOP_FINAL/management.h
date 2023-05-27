#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "structures.h"

void managementMode();
void Showrestockneeds(Product products[], int num_products);
void swap(Product *a, Product *b);
int partition(Product *products, int low, int high);
void quicksort(Product *products, int low, int high);
void showLowestStock(Product *products, int numProducts);
void ShowRemainingSpace(Product products[], int num_products);
void increaseStock(Product *products, int num_products);
void showStock(Product *products, int num_products);

#endif