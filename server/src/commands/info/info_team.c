/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** info_team
*/

#include "my.h"

int info_team(const int client_fd, my_teams_t *teams)
{
    team_t *team;

    TAILQ_FOREACH(team, &teams->team_head, team_entries) {
        if (strcmp(team->uuid, teams->command_context->team_uuid) == 0) {
            dprintf(client_fd, "%s%s\n%s\n%s\n%s", CODE_208, team->uuid,
            team->name, team->description, CODE_101);
            return WIN_CMD;
        }
    }
    dprintf(client_fd, "%s%s\n%s", CODE_402, teams->command_context->team_uuid,
    CODE_101);
    return ERR_CMD;
}
