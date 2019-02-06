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
        while (dest[n] != 0) {
            rtn[n] = dest[n];
            ++n;
        }
        free(dest);
    }
    while (src[tmp] != 0 && tmp < lim) {
        rtn[tmp + n] = src[tmp];
        ++tmp;
    }
    rtn[tmp + n] = 0;
    return (rtn);
}

char *read_next(int fd, leftover_t *save, char *rtn)
{
    char buff[READ_SIZE + 1] = {'\0'};
    int check;

    save->nb = read(fd, buff, READ_SIZE);
    buff[save->nb] = 0;
    if (save->nb == 0 && rtn[0] == 0 || save->nb < 0) {
        free(rtn);
        return (NULL);
    }
    check = get_p(buff, '\n');
    rtn = copycat(rtn, buff, check);
    if (check == -1 && save->nb == READ_SIZE) {
        rtn = read_next(fd, save, rtn);
    } else if (check != -1) {
        free(save->str);
        save->str = copycat(NULL, buff + (check + 1), -1);
    } else
        save->str[0] = 0;
    return (rtn);
}

char *get_next_line(int fd)
{
    static leftover_t *save;
    char *rtn = NULL;
    char *cpy = NULL;

    if (save == NULL) {
        save = malloc(sizeof(*save));
        save->str = malloc(sizeof(char));
        save->str[0] = 0;
    }
    if (fd < 0 || READ_SIZE <= 0 || save == NULL)
        return (NULL);
    if (get_p(save->str, '\n') == -1) {
        rtn = save->str != NULL ? copycat(NULL, save->str, -1) : rtn;
        rtn = read_next(fd, save, rtn);
    } else {
        rtn = copycat(rtn, save->str, get_p(save->str, '\n'));
        cpy = copycat(NULL, save->str + (get_p(save->str, '\n') + 1), -1);
        free(save->str);
        save->str = cpy;
    }
    return (rtn);
}