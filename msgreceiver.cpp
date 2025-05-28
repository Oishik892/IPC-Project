#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <unistd.h>

#define MAX_TEXT 512  // Maximum message size

// Structure to store messages
struct message {
    long msg_type;       // Message type
    char msg_text[MAX_TEXT]; // Message text
};

int main() {
    key_t key = ftok("msgqueue", 65); // Generate the same unique key
    int msgid = msgget(key, 0666); // Get existing message queue

    if (msgid == -1) {
        std::cerr << "Failed to get message queue\n";
        return 1;
    }

    message msg;

    // Receive message from queue
    if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0) == -1) {
        std::cerr << "Failed to receive message\n";
        return 1;
    }

    std::cout << "Received message: " << msg.msg_text << "\n";

    // Remove the message queue after receiving (optional)
    msgctl(msgid, IPC_RMID, nullptr);
    return 0;
}
 