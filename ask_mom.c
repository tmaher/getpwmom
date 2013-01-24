#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include "getpwmom.h"


int main(int argc, char **argv){
  struct passwd *mom;

  printf("starting\n");
  mom = MOM_ENTRY();

  printf("user %s, uid %d, shell %s\n", mom->pw_name, MOM_GETUID(), mom->pw_shell);

  return 0;
}
