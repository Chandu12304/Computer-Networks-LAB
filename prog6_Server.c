/* ----------- server.c ----------- */
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    char filename[256], buffer[4096];

    /* 1) ensure the pipes exist */
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    /* 2) read filename from client */
    int r = open(FIFO1, O_RDONLY);
    read(r, filename, sizeof(filename));
    close(r);

    /* 3) open the file and read its contents */
    int f = open(filename, O_RDONLY);
    int n = read(f, buffer, sizeof(buffer));
    close(f);

    /* 4) send contents back to client */
    int w = open(FIFO2, O_WRONLY);
    write(w, buffer, n);
    close(w);

    return 0;
}
