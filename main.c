#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "management.h"
#include "buying.h"
#include "logOrSignin.h"
#include "structures.h"


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