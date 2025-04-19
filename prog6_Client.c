/* ----------- client.c ----------- */
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    char filename[256];
    char buffer[4096];

    /* 1) ensure the pipes exist */
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    /* 2) get filename from user */
    printf("Enter the full file path: ");
    fgets(filename, sizeof(filename), stdin);

    // Remove trailing newline character if present
    filename[strcspn(filename, "\n")] = '\0';

    /* 3) send filename to server */
    int w = open(FIFO1, O_WRONLY);
    write(w, filename, strlen(filename) + 1);  // include null terminator
    close(w);

    /* 4) read back file contents */
    int r = open(FIFO2, O_RDONLY);
    int n = read(r, buffer, sizeof(buffer));
    close(r);

    /* 5) display the file contents */
    write(STDOUT_FILENO, buffer, n);

    return 0;
}
