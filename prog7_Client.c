/* udp_client.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <server_ip> <port> <filename>\n", argv[0]);
        return 1;
    }

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in srv = {
        .sin_family = AF_INET,
        .sin_port = htons(atoi(argv[2]))
    };
    inet_pton(AF_INET, argv[1], &srv.sin_addr);

    FILE *fp = fopen(argv[3], "rb");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char buf[BUF_SIZE];
    while (!feof(fp)) {
        size_t n = fread(buf, 1, BUF_SIZE, fp);
        if (n > 0)
            sendto(sock, buf, n, 0, (struct sockaddr*)&srv, sizeof(srv));
    }

    fclose(fp);
    close(sock);
    return 0;
}
