/*
*
* Практика 2
*
* Написать две программы, которые обмениваются через разделяемую память.
* Одна инкрементирует число, вторая печатаетна экран.
* Добавить в программу изменения переменной возможность изменения по срабатыванию таймера, например 1 раз в секунду.
*
*/


#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define SHARED_MEMORY_OBJECT_NAME "my_shared_memory"
#define SHARED_MEMORY_OBJECT_SIZE 50

int main (int argc, char ** argv) {
    int shm, len;
    char *addr;
    int cnt = 0;
    char scnt[3];
    snprintf( scnt, 3, "%d", cnt );

    len = strlen(scnt);
    len = (len<=SHARED_MEMORY_OBJECT_SIZE)?len:SHARED_MEMORY_OBJECT_SIZE;

    if ( (shm = shm_open(SHARED_MEMORY_OBJECT_NAME, O_CREAT|O_RDWR, 0777)) == -1 ) {
        perror("shm_open");
        return 1;
    }

    if ( ftruncate(shm, SHARED_MEMORY_OBJECT_SIZE+1) == -1 ) {
        perror("ftruncate");
        return 1;
    }

    addr = mmap(0, SHARED_MEMORY_OBJECT_SIZE+1, PROT_WRITE|PROT_READ, MAP_SHARED, shm, 0);
    if ( addr == (char*)-1 ) {
        perror("mmap");
        return 1;
    }

    while(1){
        // snprintf( scnt, 3, "%d", cnt );
        // memcpy(addr, scnt, len);
        // addr[len] = '\0';
        int* p_cnt;
        p_cnt = (int*)addr;
        *p_cnt = cnt;

        printf("%d -> shared memory\n", cnt);
        printf("Shared memory filled\n");
        cnt++;
        sleep(10);
        if(cnt > 9){
            printf("Unlink\n");
            munmap(addr, SHARED_MEMORY_OBJECT_SIZE);
            close(shm);
            shm_unlink(SHARED_MEMORY_OBJECT_NAME);
            break;
        }
    }
   
    return 0;
}