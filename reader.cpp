#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of shared memory segment

int main() {
    key_t key = ftok("shmfile", 65);  // Generate the same key
    int shmid = shmget(key, SHM_SIZE, 0666);  // Get shared memory ID

    if (shmid == -1) {
        std::cerr << "Failed to get shared memory\n";
        return 1;
    }

    char *data = (char*) shmat(shmid, nullptr, 0);  // Attach to shared memory
    if (data == (char*) -1) {
        std::cerr << "Failed to attach shared memory\n";
        return 1;
    }

    std::cout << "Data read from shared memory: " << data << "\n";

    shmdt(data);  // Detach shared memory
    shmctl(shmid, IPC_RMID, nullptr);  // Remove shared memory

    return 0;
}
