/* udp_server.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(atoi(argv[1]))
    };
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));

    char buf[BUF_SIZE];
    while (1) {
        ssize_t len = recvfrom(sock, buf, BUF_SIZE, 0, NULL, NULL);
        if (len <= 0) break;
        fwrite(buf, 1, len, stdout);
    }

    close(sock);
    return 0;
}
