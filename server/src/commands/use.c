/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** use
*/

#include "my.h"

static bool is_in_user_team_belong(server_t *server, my_teams_t *teams)
{
    team_belong_t *team_belong;

    for ((team_belong) =
        ((&server->clients[server->user_index]->
        new_user->team_belong_head)->tqh_first);
        (team_belong); (team_belong) =
        ((team_belong)->belong_entries.tqe_next)) {
        if (strcmp(server->cmd_arg.tab[1], team_belong->uuid) == 0) {
            teams->command_context->team_context = TEAM;
            teams->command_context->team_uuid = strdup(team_belong->uuid);
            return true;
        }
    }
    return false;
}

static bool channel_is_found(server_t *server, my_teams_t *teams, team_t *team)
{
    channel_t *channel;

    for ((channel) = ((&team->channel_head)->tqh_first); (channel);
    (channel) = ((channel)->channel_entries.tqe_next)) {
        if (strcmp(server->cmd_arg.tab[2], channel->uuid) == 0) {
            teams->command_context->team_context = CHANNEL;
            teams->command_context->channel_uuid = strdup(channel->uuid);
            return true;
        }
    }
    return false;
}

static bool is_in_team(server_t *server, my_teams_t *teams)
{
    team_t *team;

    for ((team) = ((&teams->team_head)->tqh_first); (team);
        (team) = ((team)->team_entries.tqe_next)) {
        if (strcmp(server->cmd_arg.tab[1], team->uuid) == 0) {
            teams->command_context->team_uuid = strdup(team->uuid);
            return channel_is_found(server, teams, team);
        }
    }
    return false;
}

static bool thread_is_found(server_t *server, my_teams_t *teams,
    channel_t *channel)
{
    thread_t *thread;

    for ((thread) = ((&channel->thread_head)->tqh_first);
        (thread); (thread) = ((thread)->thread_entries.tqe_next)) {
        if (strcmp(server->cmd_arg.tab[3], thread->uuid) == 0) {
            teams->command_context->team_context = THREAD;
            teams->command_context->thread_uuid = strdup(thread->uuid);
            return true;
        }
    }
    return false;
}

static bool channel_thread_is_found(server_t *server, my_teams_t *teams,
    team_t *team)
{
    channel_t *channel;

    for ((channel) = ((&team->channel_head)->tqh_first); (channel);
        (channel) = ((channel)->channel_entries.tqe_next)) {
        if (strcmp(server->cmd_arg.tab[2], channel->uuid) == 0) {
            teams->command_context->channel_uuid = strdup(channel->uuid);
            return thread_is_found(server, teams, channel);
        }
    }
    return false;
}

static bool is_in_channel(server_t *server, my_teams_t *teams)
{
    team_t *team;

    for ((team) = ((&teams->team_head)->tqh_first); (team);
        (team) = ((team)->team_entries.tqe_next)) {
        if (strcmp(server->cmd_arg.tab[1], team->uuid) == 0) {
            teams->command_context->team_uuid = strdup(team->uuid);
            return channel_thread_is_found(server, teams, team);
        }
    }
    return false;
}

static void set_team_context(server_t *server, const int client_fd,
    my_teams_t *teams)
{
    if (server->cmd_arg.len == 2) {
        if (is_in_user_team_belong(server, teams)) {
            dprintf(client_fd, "%s",
                    "use.c/set_team_context: Context set at TEAM\n");
        } else {
            reset_command_context(teams);
            dprintf(client_fd, "%s",
                    "use.c/set_team_context: Context set at NOTHING\n");
        }
    }
}

static void set_channel_context(server_t *server, const int client_fd,
    my_teams_t *teams)
{
    if (server->cmd_arg.len == 3) {
        if (is_in_user_team_belong(server, teams) &&
            is_in_team(server, teams)) {
            dprintf(client_fd, "%s",
                    "use.c/set_channel_context: Context set at CHANNEL\n");
        } else {
            reset_command_context(teams);
            dprintf(client_fd, "%s",
                    "use.c/set_channel_context: Context set at NOTHING\n");
        }
    }
}

static void set_thread_context(server_t *server, const int client_fd,
    my_teams_t *teams)
{
    if (server->cmd_arg.len == 4) {
        if (is_in_user_team_belong(server, teams) &&
            is_in_channel(server, teams)) {
            dprintf(client_fd, "%s",
                    "use.c/set_thread_context: Context set at THREAD\n");
        } else {
            reset_command_context(teams);
            dprintf(client_fd, "%s",
                    "use.c/set_thead_context: Context set at NOTHING\n");
        }
    }
}

int use_cmd(server_t *server, const int client_fd, my_teams_t *teams)
{
    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    if (server->cmd_arg.len < 2 || server->cmd_arg.len > 4) {
        dprintf(client_fd, "%s",
            "use.c/use_cmd: Invalid number of parameters\n");
        return ERR_CMD;
    }
    set_team_context(server, client_fd, teams);
    set_channel_context(server, client_fd, teams);
    set_thread_context(server, client_fd, teams);
    return WIN_CMD;
}
