/*
** EPITECH PROJECT, 2018
** get_next_line_2018
** File description:
** get_next_line
*/

#include "get_next_line.h"

static leftover_t *save;

int get_p(char const *str, char goal)
{
    int n = 0;

    if (str == NULL)
        return (-1);
    while (str[n] != goal && str[n] != '\0' && str != NULL)
        ++n;
    if (str[n] != goal)
        return (-1);
    return (n);
}

char *copy_n(char *dest, char const *src, int n)
{
    int a = 0;
    int i = get_p(src, '\0');

    if (i < n || n < 0)
        n = i;
    while (a < n) {
        dest[a] = src[a];
        ++a;
    }
    dest[a] = '\0';
    return (dest);
}

char *my_allocatn(char *dest, const char *src, int lim)
{
    int i = get_p(dest, 0);
    char *rtn = malloc(sizeof(char) * (i + get_p(src, 0) + 1));
    int n = 0;

    copy_n(rtn, dest, -1);
    while (src[n] != '\0' && (n < lim || lim == -1)) {
        rtn[i + n] = src[n];
        ++n;
    }
    rtn[i + n] = '\0';
    free(dest);
    return (rtn);
}

char *read_next(char *rtn, int fd)
{
    char *buff = malloc(sizeof(char) * (READ_SIZE + 1));
    char *cpy;
    int i = READ_SIZE;
    int tmp = -1;
    buff[0] = '\0';

    while (i == READ_SIZE && tmp == -1) {
        i = read(fd, buff, READ_SIZE);
        buff[i] = '\0';
        tmp = get_p(buff, '\n');
        rtn = my_allocatn(rtn, buff, tmp);
    }
    cpy = malloc(sizeof(char) * get_p(buff + tmp, 0));
    copy_n(cpy, buff + tmp + 1, -1);
    free(buff);
    save->str = cpy;
    save->nb = i == READ_SIZE ? i : 0;
    if (i <= 0)
        return (NULL);
    return (rtn);
}

char *get_next_line(int fd)
{
    char *rtn = malloc(sizeof(char));
    int tmp = 1;

    rtn[0] = 0;
    tmp = (save == NULL) ? READ_SIZE : save->nb;
    save = (save == NULL) ? malloc(sizeof(*save)) : save;
    save->nb = tmp;
    if ((save->nb != READ_SIZE && !save->str[0]) || READ_SIZE <= 0) {
        free(rtn);
        return (NULL);
    } else if (save->nb == 0 && get_p(save->str, 0) != 0) {
        rtn = my_allocatn(rtn, save->str, get_p(save->str, '\n'));
        save->str = copy_n(save->str, save->str + get_p(save->str, '\n'), -1);
    }
    tmp = save->str != NULL ? get_p(save->str, '\n') : -1;
    rtn = save->str != NULL ? my_allocatn(rtn, save->str, tmp) : rtn;
    if (tmp == -1 && save->nb != 0) {
        rtn = read_next(rtn, fd);
    } else if (save)
        save->str = copy_n(save->str, save->str + tmp + 1, -1);
    return (rtn);
}