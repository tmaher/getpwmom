#include <pwd.h>
#include <string.h>
#include <stdlib.h>

/*
  To recap, version 7 password format is...

  pw_nam:pw_passwd:pw_uid:pw_gid:pw_gecos:pw_dir:pw_shell

  So for example...

  tmaher:x:5183:100:Tom Maher:/home/tmaher:/bin/bash

*/

#define MOM_ENT_ENV_NAME "GETPWMOM_ENT"



int mom_init = 0;
struct passwd mom_passwd;
char *mom_ent_fallback = "root:x:0:0:Charlie Root:/:/bin/sh";

struct passwd *mom_do_init(void){
  int i=0;
  char *env_ent;

  if(mom_init) return &mom_passwd;

  env_ent = getenv(MOM_ENT_ENV_NAME);
  if(env_ent == NULL) env_ent = mom_ent_fallback;

  mom_passwd.pw_name = strsep(&env_ent, ":");
  mom_passwd.pw_passwd = strsep(&env_ent, ":");
  mom_passwd.pw_uid = (uid_t) atoi(strsep(&env_ent, ":"));
  mom_passwd.pw_gid = (gid_t) atoi(strsep(&env_ent, ":"));
  mom_passwd.pw_gecos = strsep(&env_ent, ":");
  mom_passwd.pw_dir = strsep(&env_ent, ":");
  mom_passwd.pw_shell = strsep(&env_ent, ":");

  mom_init=1;
  return &mom_passwd;
}
