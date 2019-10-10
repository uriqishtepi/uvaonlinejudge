/* Example on how to use mmap and how to set rlimits
 * when setting an rlimit lower than the mmaped file size
 * mmap call will fail with out of memory error
 *
 * When successful, mmap will show memory utilization as
 * large as the file it has mapped, but when unmapped, 
 * it will simply release that memory (as seen by ps tools).
 *
 * to generate the file to mmap use cat /dev/urandom > mmap_file
 * or dd if=/dev/urandom of=mmap_file bz=1024 count=100000
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define handle_error(str, errno) { \
    perror(str); \
    fprintf(stderr,str": %d %s\n", errno, strerror(errno)); \
    exit(1);    \
}


static int
cmpintp(const void *p1, const void *p2) {
    return (* (int *) p1) > (* (int *) p2);
}


int main() 
{
    struct rlimit rlim;

    int rc = getrlimit(RLIMIT_DATA, &rlim);
    if (-1 == rc)
        handle_error("getrlimit", rc);
    printf("getrlimit: %ld %ld\n", rlim.rlim_cur, rlim.rlim_max);

    if (0) {
        rlim.rlim_cur = 100000; //if fl size is > then we get cannot allocate memory
        rc = setrlimit(RLIMIT_DATA, &rlim);
        if (-1 == rc) {
            handle_error("setrlimit", errno);
        }

        rc = getrlimit(RLIMIT_DATA, &rlim);
        printf("setrlimit to: %ld %ld\n", rlim.rlim_cur, rlim.rlim_max);
    }

    int fd;
    struct stat sb;

    fd = open("mmap_file", O_RDWR);
    if (fd == -1)
        handle_error("open", errno);

    if (fstat(fd, &sb) == -1)           /* To obtain file size */
        handle_error("fstat", errno);

    printf("mmaping size : %ld\n", sb.st_size);
    char *addr = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
        handle_error("mmap", errno);

    printf("mapped successful\n");

    int *arr = (int *)addr;
    //for (int i = 0; i < sb.st_size / 4; i+=100)
    for (int i = 0; i < 10; i++)
        printf("i %d, arr[i] %d", i, arr[i]);
    printf("\n");

    qsort(arr, sb.st_size / 4, sizeof(int), cmpintp);

    for (int i = 0; i < 10; i++)
        printf("i %d, arr[i] %d\n", i, arr[i]);

    int k;
    printf("\nsorting successful, press key to continue...");
    fread(&k, 1, 1, stdin);

    rc = msync(addr, sb.st_size, MS_SYNC);
    if (rc) {
        handle_error("usync:", errno);
    }

    rc = munmap(addr, sb.st_size);
    if (rc) {
        handle_error("unmap:", errno);
    }
    printf("unmapped successful\n");
    printf("unmapping successful, press key to continue...");
    fread(&k, 1, 1, stdin);
}
