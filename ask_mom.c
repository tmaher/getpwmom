#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>

struct passwd *mom_do_init(void);

int main(int argc, char **argv){
  struct passwd *mom;

  printf("starting\n");
  mom = mom_do_init();

  printf("user %s, shell %s\n", mom->pw_name, mom->pw_shell);

  return 0;
}
