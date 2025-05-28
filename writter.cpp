#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of shared memory segment

int main() {
    key_t key = ftok("shmfile", 65);  // Generate unique key
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);  // Create shared memory

    if (shmid == -1) {
        std::cerr << "Failed to create shared memory\n";
        return 1;
    }

    char *data = (char*) shmat(shmid, nullptr, 0);  // Attach to shared memory
    if (data == (char*) -1) {
        std::cerr << "Failed to attach shared memory\n";
        return 1;
    }

    std::string message;
    std::cout << "Enter message to store in shared memory: ";
    std::getline(std::cin, message);

    strncpy(data, message.c_str(), SHM_SIZE);  // Copy data to shared memory

    std::cout << "Data written to shared memory: " << data << "\n";

    shmdt(data);  // Detach shared memory
    return 0;
}
    