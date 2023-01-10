#ifndef FS_H_
#define FS_H_

#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define NR_OPEN_DEFAULT     (sizeof(long) * 8)

struct task_struct {
    /* .... */

    /* Open file information: */

	struct files_struct	*files;

    /* .... */
};

struct fdtable {
	unsigned int max_fds;
	struct file **fd;     
	unsigned long *close_on_exec;
	unsigned long *open_fds;
};

struct files_struct {
  /* ... */

	struct fdtable *fdt;
	struct fdtable fdtab;
  
	unsigned int next_fd;
	unsigned long close_on_exec_init[1];
	unsigned long open_fds_init[1];
	struct  file *fd_array[NR_OPEN_DEFAULT];

    /* ... */
};

struct path {
    char name[2048];        /* Burası aslında tam olarak böyle değil */
};

struct file {
    /* ..... */

	struct path	f_path;
	long f_count;
	int f_flags;
	mode_t f_mode;
	off_t f_pos;

    /* ..... */
};

void init_task(void);
int sys_open(const char *path, int flags, ...);
int sys_close(int fd);
int sys_dup(int fd);
int sys_dup2(int fd, int fd2);

extern struct task_struct *current;

#endif
