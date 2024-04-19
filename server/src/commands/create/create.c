/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** create
*/

#include "my.h"
#include <uuid/uuid.h>

int create(server_t *server, const int client_fd, my_teams_t *teams)
{
    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    if (teams->command_context->team_context == NOTHING)
        return create_team(server, client_fd, teams);
    if (teams->command_context->team_context == TEAM)
        return create_channel(server, client_fd, teams);
    if (teams->command_context->team_context == CHANNEL)
        return create_thread(server, client_fd, teams);
    if (teams->command_context->team_context == THREAD)
        return create_comment(server, client_fd, teams);
    return ERR_CMD;
}
