#ifndef CSD_GRP_H
#define CSD_GRP_H


#include <grp.h>
#include <sys/types.h>

struct group *csd_getgrnam(const char *name);
struct group *csd_getgrgid(gid_t gid);
void csd_endgrent(void);
struct group *csd_getgrent(void);
void csd_setgrent(void);

#endif