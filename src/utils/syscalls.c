#ifdef __cplusplus
extern "C"
{
#endif

#include <sys/errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h>

char *environ_initial[1] = { 0 };
char **environ = environ_initial;

int _close_r(struct _reent *r, int file)
{
    (void) r;
    (void) file;

    return -1;
}

int _execve_r(struct _reent *r, const char *path, char * const argv[],
        char * const envp[])
{
    (void) r;
    (void) path;
    (void) argv;
    (void) envp;

    errno = ENOMEM;
    return -1;
}

void _exit(int status)
{
    (void) status;

    while (1)
        ;
}

pid_t _fork_r(struct _reent *r)
{
    (void) r;

    errno = EAGAIN;
    return -1;
}

int _fstat_r(struct _reent *r, int file, struct stat *st)
{
    (void) r;
    (void) file;
    (void) st;

    st->st_mode = S_IFCHR;
    return 0;
}

pid_t _getpid_r(struct _reent *r)
{
    (void) r;

    return 1;
}

int _isatty_r(struct _reent *r, int file)
{
    (void) r;
    (void) file;

    return 1;
}

int _kill_r(struct _reent *r, pid_t pid, int signal)
{
    (void) r;
    (void) pid;
    (void) signal;

    errno = EINVAL;
    return -1;
}

int _link_r(struct _reent *r, const char *old, const char *new)
{
    (void) r;
    (void) old;
    (void) new;

    errno = EMLINK;
    return -1;
}

off_t _lseek_r(struct _reent *r, int file, off_t offset, int whence)
{
    (void) r;
    (void) file;
    (void) offset;
    (void) whence;

    return 0;
}

int _open_r(struct _reent *r, const char *pathname, int flags, int mode)
{
    (void) r;
    (void) pathname;
    (void) flags;
    (void) mode;

    return -1;
}

ssize_t _read_r(struct _reent *r, int file, void *buf, size_t nbyte)
{
    (void) r;
    (void) file;
    (void) buf;
    (void) nbyte;

    return 0;
}

caddr_t _sbrk_r(struct _reent *r, int size)
{
    extern char __heap_start;
    extern char __heap_end;
    static char *current_heap_end = &__heap_start;
    char *previous_heap_end;

    (void) r;

    previous_heap_end = current_heap_end;

    if (current_heap_end + size > &__heap_end)
    {
        errno = ENOMEM;
        return (caddr_t) - 1;
    }

    current_heap_end += size;

    return (caddr_t) previous_heap_end;
}

int _stat_r(struct _reent *r, const char *pathname, struct stat *st)
{
    (void) r;
    (void) pathname;

    st->st_mode = S_IFCHR;
    return 0;
}

int _times_r(struct _reent *r, struct tms *buf)
{
    (void) r;
    (void) buf;

    return -1;
}

int _unlink_r(struct _reent *r, const char *pathname)
{
    (void) r;
    (void) pathname;

    errno = ENOENT;
    return -1;
}

pid_t _wait_r(struct _reent *r, int *stat_loc)
{
    (void) r;
    (void) stat_loc;

    errno = ECHILD;
    return -1;
}

ssize_t _write_r(struct _reent *r, int file, const void *buf, size_t nbyte)
{
    (void) r;
    (void) file;
    (void) buf;
    (void) nbyte;

    return 0;
}

#ifdef __cplusplus
}
#endif
