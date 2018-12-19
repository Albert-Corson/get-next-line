/*
** EPITECH PROJECT, 2018
** get_next_line_2018
** File description:
** get_next_line
*/

#include "get_next_line.h"

static leftover_t *lftovr;

int get_pos(char const *str, char goal)
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

char *my_strncpy(char *dest, char const *src, int n)
{
    int a = 0;
    int i = get_pos(src, '\0');

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
    int i = get_pos(dest, 0);
    char *rtn = malloc(sizeof(char) * (i + get_pos(src, 0) + 1));
    int n = 0;

    my_strncpy(rtn, dest, -1);
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
        tmp = get_pos(buff, '\n');
        rtn = my_allocatn(rtn, buff, tmp);
    }
    cpy = malloc(sizeof(char) * get_pos(buff + tmp, 0));
    my_strncpy(cpy, buff + tmp + 1, -1);
    free(buff);
    lftovr->str = cpy;
    lftovr->nb_rd = i == READ_SIZE ? i : 0;
    return (rtn);
}

char *get_next_line(int fd)
{
    char *rtn = malloc(sizeof(char));
    int tmp = 1;

    rtn[0] = 0;
    tmp = (lftovr == NULL) ? tmp : lftovr->nb_rd;
    lftovr = (lftovr == NULL) ? malloc(sizeof(*lftovr)) : lftovr;
    lftovr->nb_rd = tmp;
    if ((lftovr->nb_rd == 0 && get_pos(lftovr->str, 0) == 0) || fd < 0) {
        free(rtn);
        return (NULL);
    } else if (lftovr->nb_rd == 0 && get_pos(lftovr->str, 0) != 0) {
        rtn = my_allocatn(rtn, lftovr->str, get_pos(lftovr->str, '\n'));
        lftovr->str = lftovr->str + get_pos(lftovr->str, '\n');
    }
    tmp = lftovr->str != NULL ? get_pos(lftovr->str, '\n') : -1;
    rtn = lftovr->str != NULL ? my_allocatn(rtn, lftovr->str, tmp) : rtn;
    if (tmp == -1 && lftovr->nb_rd != 0) {
        rtn = read_next(rtn, fd);
    } else if (lftovr)
        lftovr->str = lftovr->str + tmp + 1;
    return (rtn);
}