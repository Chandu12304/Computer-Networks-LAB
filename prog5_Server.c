#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 17000
#define WINDOW_SIZE 4
#define FRAME_COUNT 10

int main() {
    int sock;
    int simulate_loss = 1; 
    struct sockaddr_in server_addr;
    char buffer[1024];
    int base = 0, next_frame = 0, ack;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Connect to receiver
    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Connected to receiver.\n");
    
    while (base < FRAME_COUNT) {
        // Send frames within window size
        // Flag to simulate loss of frame 1
        while (next_frame < base + WINDOW_SIZE && next_frame < FRAME_COUNT) {
            if (next_frame == 1 && simulate_loss) {
                printf("Simulating loss of Frame 1\n");
                next_frame++; // Skip sending frame 1
                simulate_loss = 0;
                continue;
            }
            
            sprintf(buffer, "Frame %d", next_frame);
            send(sock, buffer, strlen(buffer), 0);
            printf("Sent: %s\n", buffer);
            next_frame++;
        }

        // Wait for ACK
        recv(sock, &ack, sizeof(ack), 0);
        printf("Received ACK for Frame %d\n", ack);

        // Update base only if we get ACK for newer frames
        if (ack > base) {
            base = ack;
        } else {
            // Go-Back-N: Retransmit from base
            printf("Timeout! Retransmitting from Frame %d\n", base);
            next_frame = base; // Reset to retransmit window
        }
    }

    // Send termination message
    strcpy(buffer, "exit");
    send(sock, buffer, strlen(buffer), 0);
    
    close(sock);
    return 0;
}
