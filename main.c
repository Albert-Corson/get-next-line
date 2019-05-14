/*
** EPITECH PROJECT, 2019
** get_next_line
** File description:
** main
*/

#include "get_next_line.h"
#include "stdio.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
    int fd = 0;
    char *str = NULL;

    if (argc < 2) {
        dprintf(2, "%s file.txt\n", argv[0]);
        return (84);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        dprintf(2, "%s could not be opened\n", argv[1]);
        return (84);
    }
    while ((str = get_next_line(fd))) {
        printf("%s\n", str);
        free(str);
    }
    return (0);
}