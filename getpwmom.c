#include "getpwmom.h"

int MOM_INIT = 0;
int MOM_GETPWENT_STATE = 0;

struct passwd *MOM_ENTRY(void){
  int i=0;
  char *env_ent, *raw_id;

  if(MOM_INIT) return &MOM_PASSWD;

  if(getenv(ENT_ENV_NAME) != NULL)
    env_ent = strdup(getenv(ENT_ENV_NAME));
  else
    env_ent = strdup(ENT_FALLBACK);

  MOM_PASSWD.pw_name = strsep(&env_ent, ":");
  MOM_PASSWD.pw_passwd = strsep(&env_ent, ":");
  raw_id = strsep(&env_ent, ":");
  MOM_PASSWD.pw_uid = (uid_t) ((raw_id == NULL) ? 0 : atoi(raw_id));
  raw_id = strsep(&env_ent, ":");
  MOM_PASSWD.pw_gid = (gid_t) ((raw_id == NULL) ? 0 : atoi(raw_id));
  MOM_PASSWD.pw_gecos = strsep(&env_ent, ":");
  MOM_PASSWD.pw_dir = strsep(&env_ent, ":");
  MOM_PASSWD.pw_shell = strsep(&env_ent, ":");

  MOM_INIT=1;
  return &MOM_PASSWD;
}

uid_t MOM_GETUID(void){
  return MOM_ENTRY()->pw_uid;
}

uid_t MOM_GETEUID(void){
  return MOM_GETUID();
}

gid_t MOM_GETGID(void){
  return MOM_ENTRY()->pw_gid;
}

gid_t MOM_GETEGID(void){
  return MOM_GETGID();
}

struct passwd *MOM_GETPWENT(void){
  if(MOM_GETPWENT_STATE) return NULL;

  MOM_GETPWENT_STATE = 1;
  return MOM_ENTRY();
}

void MOM_SETPWENT(void){
  MOM_GETPWENT_STATE = 0;
  return;
}

struct passwd *MOM_GETPWNAM(const char *login){
  if(0 == strncmp(login, MOM_ENTRY()->pw_name, strlen(MOM_ENTRY()->pw_name))){
    return MOM_ENTRY();
  }
  errno = ENOENT;
  return NULL;
}

struct passwd *MOM_GETPWUID(uid_t uid){
  if(uid == MOM_ENTRY()->pw_uid){
    return MOM_ENTRY();
  }
  errno = ENOENT;
  return NULL;
}

int MOM_COPY_PWSTRUCT(struct passwd *dest, char *buf, size_t buflen,
                       struct passwd **result, struct passwd *src){
  char *p = buf;

  if(buflen < strlen(src->pw_name) + strlen(src->pw_passwd) +
     strlen(src->pw_gecos) + strlen(src->pw_dir) + strlen(src->pw_shell) + 5){
    result = NULL;
    return ENOMEM;
  }

  strcpy(p, src->pw_name);
  dest->pw_name = p;
  p += strlen(src->pw_name) + 1;

  strcpy(p, src->pw_passwd);
  dest->pw_passwd = p;
  p += strlen(src->pw_passwd) + 1;

  dest->pw_uid = src->pw_uid;
  dest->pw_gid = src->pw_gid;

  strcpy(p, src->pw_gecos);
  dest->pw_gecos = p;
  p += strlen(src->pw_gecos) + 1;

  strcpy(p, src->pw_dir);
  dest->pw_dir = p;
  p += strlen(src->pw_dir) + 1;

  strcpy(p, src->pw_shell);
  dest->pw_shell = p;

  *result = dest;

  return 0;
}

int MOM_GETPWNAM_R(const char *name, struct passwd *pwd,
                   char *buf, size_t buflen, struct passwd **result){
  if(0 != strncmp(name, MOM_ENTRY()->pw_name, strlen(MOM_ENTRY()->pw_name))){
    *result = NULL;
    return 0;
  }

  return MOM_COPY_PWSTRUCT(pwd, buf, buflen, result, MOM_ENTRY());
}

int MOM_GETPWUID_R(uid_t uid, struct passwd *pwd,
                   char *buf, size_t buflen, struct passwd **result){
  if(uid != MOM_ENTRY()->pw_uid){
    *result = NULL;
    return 0;
  }

  return MOM_COPY_PWSTRUCT(pwd, buf, buflen, result, MOM_ENTRY());
}

