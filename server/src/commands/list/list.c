/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** list
*/

#include "my.h"

int list(server_t *server, const int client_fd, my_teams_t *teams)
{
    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    if (teams->command_context->team_context == NOTHING)
        return list_team(client_fd, teams);
    if (teams->command_context->team_context == TEAM)
        return list_channel(client_fd, teams);
    if (teams->command_context->team_context == CHANNEL)
        return list_thread(client_fd, teams);
    if (teams->command_context->team_context == THREAD)
        return list_comment(client_fd, teams);
    return WIN_CMD;
}
