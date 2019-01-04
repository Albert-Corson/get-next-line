/*
** EPITECH PROJECT, 2018
** get_next_line_2018
** File description:
** get_next_line
*/

#include "get_next_line.h"

int get_p(char const *str, char goal)
{
    int n = 0;

    if (str == NULL)
        return (-1);
    while (str[n] != goal && str[n] != '\0')
        ++n;
    if (str[n] != goal)
        return (-1);
    return (n);
}

char *copy_n(char *dest, char const *src, int n)
{
    int a = 0;
    int i = get_p(src, '\0');
    char *rtn = NULL;

    if (i < n || n < 0)
        n = i;
    if (dest == NULL)
        rtn = malloc(sizeof(char) * (i + 1));
    else
        rtn = dest;
    while (a < n) {
        rtn[a] = src[a];
        ++a;
    }
    rtn[a] = '\0';
    return (rtn);
}

char *my_allocatn(char *dest, const char *src, int lim)
{
    int i;
    char *rtn;
    int n = 0;

    if (src == NULL)
        return (dest);
    else if (dest == NULL)
        return (copy_n(NULL, src, lim));
    i = get_p(dest, 0);
    rtn = malloc(sizeof(char) * (i + get_p(src, 0) + 1));
    copy_n(rtn, dest, -1);
    while (src[n] != '\0' && (n < lim || lim == -1)) {
        rtn[i + n] = src[n];
        ++n;
    }
    rtn[i + n] = '\0';
    free(dest);
    return (rtn);
}

char *read_next(int fd, leftover_t *save, char *rtn)
{
    char buff[READ_SIZE + 1] = {'\0'};
    int check;

    save->nb = read(fd, buff, READ_SIZE);
    buff[save->nb] = 0;
    if (save->nb == 0 && rtn[0] == 0 || save->nb < 0) {
        free(save->str);
        free(save);
        free(rtn);
        return (NULL);
    }
    check = get_p(buff, '\n');
    rtn = my_allocatn(rtn, buff, check);
    if (check == -1 && save->nb == READ_SIZE) {
        rtn = read_next(fd, save, rtn);
    } else {
        free(save->str);
        save->str = copy_n(NULL, buff + (check + 1), -1);
    }
    return (rtn);
}

char *get_next_line(int fd)
{
    static leftover_t *save;
    char *rtn = NULL;
    char *cpy = NULL;

    if (fd < 0 || READ_SIZE <= 0) {
        return (NULL);
    } else if (save == NULL) {
        save = malloc(sizeof(*save));
        save->nb = READ_SIZE;
    }
    if (get_p(save->str, '\n') == -1) {
        rtn = copy_n(NULL, save->str, -1);
        rtn = read_next(fd, save, rtn);
    } else {
        rtn = my_allocatn(rtn, save->str, get_p(save->str, '\n'));
        cpy = copy_n(NULL, save->str + (get_p(save->str, '\n') + 1), -1);
        free(save->str);
        save->str = cpy;
    }
    return (rtn);
}