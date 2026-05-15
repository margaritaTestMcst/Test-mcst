#define _GNU_SOURCE

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

extern char *sys_errlist[]; 
extern int sys_nerr;

int main(){
    int fd = open("not_exist.txt", O_RDONLY);

    if(fd == -1){
        int err = errno;
        perror("Can't open file");

        printf("Errno = %s\n", strerrorname_np(err));

        /*
        [[deprecated]] const char *const sys_errlist[];
        [[deprecated]] int sys_nerr;

        sys_nerr
        sys_errlist
        Removed in glibc 2.32.

        The use of sys_errlist[] is nowadays deprecated; use strerror(3) instead

        Source https://man.archlinux.org/man/sys_errlist.3.en
        */
        // printf("Error: %s\n", sys_errlist[err]);

        printf("%s\n", strerror(err));

        return err;
    }
    
    close(fd);

    return 0;
}