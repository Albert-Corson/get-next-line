/*
** EPITECH PROJECT, 2018
** get_next_line_2018
** File description:
** get_next_line
*/

#include "get_next_line.h"

int get_p(char *str, char c)
{
    int n = 0;

    if (str == NULL)
        return (-1);
    while (str[n] != c && str[n] > 0)
        ++n;
    if (str[n] != c)
        return (-1);
    return (n);
}

char *copycat(char *dest, char *src, int lim)
{
    char *rtn;
    int n = 0;
    int tmp = 0;

    lim = lim == -1 ? get_p(src, 0) : lim;
    if (dest == NULL)
        rtn = malloc(sizeof(char) * (lim + 1));
    else {
        rtn = malloc(sizeof(char) * (get_p(dest, 0) + lim + 1));
        while (dest[n] > 0) {
            rtn[n] = dest[n];
            ++n;
        }
        free(dest);
    }
    while (src[tmp] > 0 && tmp < lim) {
        rtn[tmp + n] = src[tmp];
        ++tmp;
    }
    rtn[tmp + n] = 0;
    return (rtn);
}

leftover_t *init_struct(leftover_t *save)
{
    if (save == NULL) {
        save = malloc(sizeof(*save));
        save->str = malloc(sizeof(char));
        save->str[0] = 0;
        save->nb = READ_SIZE;
    }
    return (save);
}

char *read_line(int fd, char *rtn, leftover_t *save)
{
    char *buff = malloc(sizeof(char) * (READ_SIZE + 1));

    while (get_p(buff, '\n') == -1 && save->nb == READ_SIZE) {
        save->nb = read(fd, buff, READ_SIZE);
        buff[save->nb] = 0;
        rtn = copycat(rtn, buff, get_p(buff, '\n'));
    }
    save->str = copycat(NULL, buff + get_p(buff, '\n') + 1, -1);
    free(buff);
    if (save->nb < 0)
        return (NULL);
    return (rtn);
}

char *get_next_line(int fd)
{
    static leftover_t *save;
    char *rtn = NULL;

    if (READ_SIZE <= 0 || fd < 0)
        return (NULL);
    save = init_struct(save);
    if (save->nb != READ_SIZE && get_p(save->str, '\n') == -1) {
        rtn = save->str;
        save->str = NULL;
    } else if (get_p(save->str, '\n') == -1) {
        rtn = copycat(NULL, save->str, -1);
        rtn = read_line(fd, rtn, save);
    } else {
        rtn = copycat(NULL, save->str, get_p(save->str, '\n'));
        save->str = copycat(NULL, save->str + get_p(save->str, '\n') + 1, -1);
    }
    return (rtn);
}