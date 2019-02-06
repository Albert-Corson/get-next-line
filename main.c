#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char const *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    char *s = get_next_line(fd);

    while (s) {
        printf("%s\n", s);
        free(s);
        s = get_next_line(fd);
    }
    return (0);
}
