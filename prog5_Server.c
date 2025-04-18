#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 17000
#define BUFFER_SIZE 1024

int main() {
    int sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    int expected_frame = 0, received_frame;
    socklen_t addr_size;

    // Create socket
    (sock = socket(AF_INET, SOCK_STREAM, 0));

    // Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Listen for connections
    listen(sock, 5);

    printf("Waiting for sender connection...\n");

    addr_size = sizeof(client_addr);
    client_sock = accept(sock, (struct sockaddr *)&client_addr, &addr_size);
    printf("Sender connected!\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        recv(client_sock, buffer, BUFFER_SIZE, 0);

        if (strcmp(buffer, "exit") == 0) {
            printf("Transmission complete. Closing connection.\n");
            break;
        }

        // Extract frame number
        sscanf(buffer, "Frame %d", &received_frame);

        if (received_frame == expected_frame) {
            printf("Received: %s\n", buffer);
            expected_frame++;
        } else {
            printf("Out-of-order frame received (Frame %d). Discarding...\n", received_frame);
        }

        // Send ACK for the last in-order received frame
        send(client_sock, &expected_frame, sizeof(expected_frame), 0);
    }

    close(client_sock);
    close(sock);
    return 0;
}