/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** info
*/

#include "my.h"

int info(server_t *server, const int client_fd, my_teams_t *teams)
{
    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    if (teams->command_context->team_context == NOTHING)
        return info_user(server, client_fd);
    if (teams->command_context->team_context == TEAM)
        return info_team(client_fd, teams);
    if (teams->command_context->team_context == CHANNEL)
        return info_channel(client_fd, teams);
    if (teams->command_context->team_context == THREAD)
        return info_thread(client_fd, teams);
    return WIN_CMD;
}
