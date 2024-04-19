/*
** EPITECH PROJECT, 2024
** test
** File description:
** fd_putstr
*/

#include <unistd.h>
#include <string.h>

void my_fd_putstr(char *str, const int client_fd)
{
    write(client_fd, str, strlen(str));
}
