/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-mathis.brehm
** File description:
** user_command.c
*/

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "my.h"
#include "teams.h"

static int error_handling_user(server_t *server,
    const int client_fd, my_teams_t *teams)
{
    user_t *np_user;

    if (server->cmd_arg.tab[1] == NULL) {
        dprintf(client_fd, "%s\n%s", CODE_101, "CODE_101");
        return ERR_CMD;
    }
    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    TAILQ_FOREACH(np_user, &teams->user_head, user_entries) {
        if (strcmp(np_user->uuid, server->cmd_arg.tab[1]) == 0) {
            return WIN_CMD;
        }
    }
    dprintf(client_fd, "%s%s\n%s", CODE_401, server->cmd_arg.tab[1], CODE_101);
    return ERR_CMD;
}

int user_cmd(server_t *server, const int client_fd, my_teams_t *teams)
{
    user_t *np_user;

    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    dprintf(client_fd, "%s", CODE_203);
    TAILQ_FOREACH(np_user, &teams->user_head, user_entries) {
        dprintf(client_fd, "%s\n%s\n%d\n",
        np_user->uuid, np_user->name, np_user->is_logged);
    }
    dprintf(client_fd, "%s", CODE_101);
    return WIN_CMD;
}

int user_spe_uuid(server_t *server, const int client_fd, my_teams_t *teams)
{
    user_t *np_user;

    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    if (error_handling_user(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    TAILQ_FOREACH(np_user, &teams->user_head, user_entries) {
        if (strcmp(np_user->uuid, server->cmd_arg.tab[1]) == 0) {
            dprintf(client_fd, "%s%s\n%s\n%d\n%s", CODE_204, np_user->uuid,
            np_user->name, np_user->is_logged, CODE_101);
            return WIN_CMD;
        }
    }
    dprintf(client_fd, "%s%s\n%s", CODE_401, server->cmd_arg.tab[1], CODE_101);
    return ERR_CMD;
}
