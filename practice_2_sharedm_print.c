#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define SHARED_MEMORY_OBJECT_NAME "my_shared_memory"
#define SHARED_MEMORY_OBJECT_SIZE 50


int main (int argc, char ** argv) {

    int shm;
    char *addr;

    if ( (shm = shm_open(SHARED_MEMORY_OBJECT_NAME, O_RDWR, 0777)) == -1 ) {
        perror("shm_open");
        return 1;
    }

    addr = mmap(0, SHARED_MEMORY_OBJECT_SIZE+1, PROT_WRITE|PROT_READ, MAP_SHARED, shm, 0);
    if ( addr == (char*)-1 ) {
    	perror("mmap");
    	return 1;
    }

    printf("Got from shared memory: %d\n", *addr);


    munmap(addr, SHARED_MEMORY_OBJECT_SIZE);
    close(shm);
}