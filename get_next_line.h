/*
** EPITECH PROJECT, 2018
** get_next_line_2018
** File description:
** get_next_line
*/

#ifndef GET_NEXT_LINE_H_
    #define GET_NEXT_LINE_H_

#ifndef READ_SIZE
#define READ_SIZE (1024)
#endif /* !READ_SIZE */

#include <stdlib.h>
#include <unistd.h>

typedef struct leftover {
    char *str;
    int nb;
} leftover_t;

char *get_next_line(int fd);

#endif /* !GET_NEXT_LINE_H_ */