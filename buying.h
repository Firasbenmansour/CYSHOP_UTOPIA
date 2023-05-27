#ifndef BUYING_H
#define BUYING_H

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "structures.h"

void menubuy(char* clientId);
void deleteClient(char* clientID);
void purchasehistory(char* clientID);
void searcharticle();
void affiche_articlemenu(int a,int b);
void buysomething();
void buying(char* clientID);

#endif