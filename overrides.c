#include "getpwmom.h"

uid_t getuid(void){ return MOM_GETUID(); }
uid_t geteuid(void){ return MOM_GETEUID(); }
gid_t getgid(void){ return MOM_GETGID(); }
gid_t getegid(void){ return MOM_GETEGID(); }
struct passwd *getpwent(void){ return MOM_GETPWENT(); }
void setpwent(void){ MOM_SETPWENT(); return; }

struct passwd *getpwnam(const char *l){ return MOM_GETPWNAM(l); }
int getpwnam_r(const char *name, struct passwd *pwd, char *buffer,
               size_t bufsize, struct passwd **result){
  return getpwnam_r(name, pwd, buffer, bufsize, result);
}

struct passwd *getpwuid(uid_t u){ return MOM_GETPWUID(u); }
int getpwuid_r(uid_t u, struct passwd *pwd, char *buffer,
               size_t bufsize, struct passwd **result){
  return getpwuid_r(u, pwd, buffer, bufsize, result);
}

uid_t (*MOM_REAL_GETUID)(void);
struct passwd *(*MOM_REAL_GETPWUID)(uid_t);

void MOM_REAL_SAVE(void){
  MOM_REAL_GETUID = dlsym(RTLD_NEXT, "getuid");
  MOM_REAL_GETPWUID = dlsym(RTLD_NEXT, "getpwuid");
}
