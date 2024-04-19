/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-mathis.brehm
** File description:
** help_cmd
*/

#include "my.h"
#include <sys/stat.h>
#include <fcntl.h>

static void open_help_msg(const int client_fd)
{
    char *buf;
    char **tab;
    struct stat sb;
    int fd = open("server/src/commands/help/help_msg.txt", O_RDONLY);

    stat("server/src/commands/help/help_msg.txt", &sb);
    buf = malloc(sizeof(char) * (sb.st_size + 1));
    read(fd, buf, sb.st_size - 1);
    buf[sb.st_size - 1] = '\0';
    close(fd);
    tab = word_array(buf, "\n");
    dprintf(client_fd, "%s", CODE_224);
    for (int i = 0; tab[i] != NULL; i++) {
        dprintf(client_fd, "%s\n", tab[i]);
    }
    dprintf(client_fd, "%s", CODE_101);
    free(tab);
    free(buf);
}

int help_cmd(server_t *server, const int client_fd, my_teams_t *)
{
    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    open_help_msg(client_fd);
    return WIN_CMD;
}
