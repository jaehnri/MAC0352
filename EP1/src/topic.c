#include "topic.h"
#include "limits.h"

#include <sys/mman.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define MAX_CLIENTS 1000


/**
 * Uses mmap to allocate memory space that is shared across all child processes of this broker.
 *
 * Below, the explanation for each flag passed to mmap:
 * 1) NULL: the kernel can place the mapping anywhere it sees fit.
 * 2) size: the number of bytes to be allocated
 * 3) PROT_READ | PROT_WRITE: processes have RW permission on the contents of this array
 * 4) MAP_SHARED: All processes related to this array can access it. MAP_ANONYMOUS: Any other processes
 * have no access to it and it won't be written to any file.
 * 5) File descriptor to be mapped. As we are using MAP_ANONYMOUS, the file descriptor is set to 0, i.e,
 * it won't be written to any specific file descriptor.
 * 6) Offset value. As there is no file descriptor, it will be 0 as well.
 *
 * Special thanks to https://linuxhint.com/using_mmap_function_linux/
 */
void* malloc_shared_memory(size_t size) {
    void* memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if (memory == MAP_FAILED) {
        fprintf(stderr, "Couldn't malloc shared memory.\n");
        exit(errno);
    }

    return memory;
}

void free_shared_memory(void* ptr, size_t size) {
    int err = munmap(ptr, size);
    if (err == -1) {
        fprintf(stderr, "Couldn't free shared memory.\n");
        exit(errno);
    }
}

topic topics;

void create_topic_structure() {
    topics.names              = malloc_shared_memory(TOPICS_SIZE * sizeof(unsigned char*));
    topics.subscribers        = malloc_shared_memory(TOPICS_SIZE * sizeof(int*));
    topics.subscribers_length = malloc_shared_memory(TOPICS_SIZE * sizeof(int));

    for (int i = 0; i < TOPICS_SIZE; i++) {
        topics.names[i] = malloc_shared_memory(SCHAR_MAX * sizeof(char));
        topics.subscribers[i] = malloc_shared_memory((MAX_CLIENTS + 1) * sizeof(int));

        topics.names[i] = 0;
        topics.subscribers_length[i] = 0;
    }
}

void clean_topic_structure() {
    for (int i = 0; i < TOPICS_SIZE; i++) {
        free_shared_memory(topics.names[i], SCHAR_MAX * sizeof(char));
        free_shared_memory(topics.subscribers[i], (MAX_CLIENTS + 1) * sizeof(int));
    }

    free_shared_memory(topics.names, TOPICS_SIZE * sizeof(unsigned char));
    free_shared_memory(topics.subscribers, TOPICS_SIZE * sizeof(int*));
    free_shared_memory(topics.subscribers_length, TOPICS_SIZE * sizeof(int));
}
