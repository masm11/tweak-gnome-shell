#define _GNU_SOURCE	// for memmem()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/fcntl.h>

#define PATH "/usr/lib/gnome-shell/libgnome-shell.so"

#define FROM "var ANIMATION_MIN_WAKEUP_INTERVAL = 1.0;"
#define TO   "var ANIMATION_MIN_WAKEUP_INTERVAL =0.01;"

int main(void)
{
    // length of FROM and TO must be equal.
    switch (0) {
    case sizeof(FROM) == sizeof(TO):
    case 0:
	;
    }
    
    int page_size;
    if ((page_size = sysconf(_SC_PAGESIZE)) == -1) {
	perror("sysconf");
	exit(1);
    }
    
    struct stat st;
    if (stat(PATH, &st) == -1) {
	perror(PATH);
	exit(1);
    }
    
    off_t size = st.st_size;
    
    int fd;
    if ((fd = open(PATH, O_RDWR)) == -1) {
	perror(PATH);
	exit(1);
    }
    
    unsigned char *buf;
    if ((buf = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == NULL) {
	perror("mmap");
	exit(1);
    }
    
    unsigned char *p;
    if ((p = memmem(buf, size, FROM, strlen(FROM))) == NULL) {
	fprintf(stderr, "not found.");
	exit(0);
    }
    memcpy(p, TO, strlen(TO));
    
    unsigned long page_beg = (unsigned long) p / page_size;
    unsigned long page_end = ((unsigned long) p + strlen(TO) - 1) / page_size;
    
    if (msync((void *) (page_beg * page_size), (page_end - page_beg + 1) * page_size, MS_ASYNC) == -1) {
	perror("msync");
	exit(1);
    }
    
    return 0;
}
