#ifndef CSD_PWD_H
#define CSD_PWD_H

#include <pwd.h>
#include <sys/types.h>

struct passwd *csd_getpwnam(const char *name);
struct passwd *csd_getpwuid(uid_t uid);

struct passwd *csd_getpwent(void);
void csd_endpwent(void);
void csd_setpwent(void);

#endif