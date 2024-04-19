/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** create_team
*/

#include "my.h"
#include <uuid/uuid.h>

static int error_create_team(server_t *server,
    const int client_fd, my_teams_t *teams)
{
    team_t *team_exist;

    if (server->cmd_arg.tab[1] == NULL || server->cmd_arg.tab[2] == NULL) {
        dprintf(client_fd, "%s%s", CODE_301, CODE_101);
        return ERR_CMD;
    }
    if (strlen(server->cmd_arg.tab[1]) >= MAX_NAME_LENGTH ||
        strlen(server->cmd_arg.tab[2]) >= MAX_DESCRIPTION_LENGTH)
        return ERR_CMD;
    TAILQ_FOREACH(team_exist, &teams->team_head, team_entries) {
        if (strcmp(team_exist->name, server->cmd_arg.tab[1]) == 0) {
            dprintf(client_fd, "%s%s", CODE_302, CODE_101);
            return ERR_CMD;
        }
    }
    return WIN_CMD;
}

int create_team(server_t *server, const int client_fd, my_teams_t *teams)
{
    team_t *team;
    uuid_t tmp_uuid;

    if (error_create_team(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    team = malloc(sizeof(team_t));
    TAILQ_INSERT_TAIL(&teams->team_head, team, team_entries);
    strcpy(team->name, server->cmd_arg.tab[1]);
    strcpy(team->description, server->cmd_arg.tab[2]);
    uuid_generate_random(tmp_uuid);
    uuid_unparse(tmp_uuid, team->uuid);
    TAILQ_INIT(&team->channel_head);
    dprintf(client_fd, "%s%s\n%s\n%s\n%s", CODE_211, team->uuid, team->name,
    team->description, CODE_101);
    server_event_team_created(team->uuid, team->name,
    server->clients[server->user_index]->my_uuid);
    return WIN_CMD;
}
