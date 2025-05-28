#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <unistd.h>
using namespace std;

#define MAX_TEXT 512  // Maximum message size

// Structure to store messages
struct message {
    long msg_type;       // Message type (must be long)
    char msg_text[MAX_TEXT]; // Message text
};

int main() {
    key_t key = ftok("msgqueue", 65); // Generate a unique key
    int msgid = msgget(key, 0666 | IPC_CREAT); // Create or get message queue

    if (msgid == -1) {
        std::cerr << "Failed to create message queue\n";
        return 1;
    }

    message msg; 
    msg.msg_type = 1; // Message type (1 means normal message)

    std::cout << "Enter message to send: ";
    std::cin.getline(msg.msg_text, MAX_TEXT); // Read user input

    // Send the message
    if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
        std::cerr << "Failed to send message\n";
        return 1;
    }

    std::cout << "Message sent successfully!\n";
    return 0;
}
