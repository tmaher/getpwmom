#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#ifndef _PW0N_COM_GETPWMOM_H
# define _PW0N_COM_GETPWMOM_H
/*
  To recap, version 7 password format is...

  pw_nam:pw_passwd:pw_uid:pw_gid:pw_gecos:pw_dir:pw_shell

  So for example...

  tmaher:x:5183:100:Tom Maher:/home/tmaher:/bin/bash

*/

#define ENT_ENV_NAME "GETPWMOM_ENT"
#define ENT_FALLBACK "root:x:0:0:Charlie Root:/:/bin/sh"

#ifndef NSS_BUFLEN_PASSWD
# define NSS_BUFLEN_PASSWD 1024
#endif

#define MOM_INIT pw0n_com_mom_init

#define MOM_GETPWENT_STATE pw0n_com_mom_getpwent_state

#define MOM_PASSWD pw0n_com_mom_passwd
struct passwd MOM_PASSWD;

#define MOM_ENTRY pw0n_com_mom_entry
struct passwd *MOM_ENTRY(void);

#define MOM_GETUID pw0n_com_mom_getuid
uid_t MOM_GETUID(void);

#define MOM_GETEUID pw0n_com_mom_geteuid
uid_t MOM_GETEUID(void);

#define MOM_GETGID pw0n_com_mom_getgid
gid_t MOM_GETGID(void);

#define MOM_GETEGID pw0n_com_mom_getegid
gid_t MOM_GETEGID(void);

#define MOM_GETPWENT pw0n_com_mom_getpwent
struct passwd *MOM_GETPWENT(void);

#define MOM_SETPWENT pw0n_com_mom_setpwent
void MOM_SETPWENT(void);

#define MOM_GETPWNAM pw0n_com_mom_getpwnam
struct passwd *MOM_GETPWNAM(const char *);

#define MOM_COPY_PWSTRUCT pw0n_com_mom_copy_pwstruct
int MOM_COPY_PWSTRUCT(struct passwd *, char *, size_t, struct passwd **,
                        struct passwd *);

#define MOM_GETPWNAM_R pw0n_com_mom_getpwnam_r
int MOM_GETPWNAM_R(const char *, struct passwd *,
                   char *, size_t, struct passwd **);

#define MOM_GETPWUID pw0n_com_mom_getpwuid
struct passwd *MOM_GETPWUID(uid_t);

#define MOM_GETPWUID_R pw0n_com_mom_getpwuid_r
int MOM_GETPWUID_R(uid_t, struct passwd *,
                   char *, size_t, struct passwd **);


#endif /* _PW0N_COM_GETPWMOM_H */
