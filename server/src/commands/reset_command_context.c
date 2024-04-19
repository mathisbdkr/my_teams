/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-yanis.harkouk
** File description:
** reset_command_context
*/

#include "teams.h"

void reset_command_context(my_teams_t *teams)
{
    if (teams->command_context->team_uuid != NULL)
        free(teams->command_context->team_uuid);
    if (teams->command_context->channel_uuid != NULL)
        free(teams->command_context->channel_uuid);
    if (teams->command_context->thread_uuid != NULL)
        free(teams->command_context->thread_uuid);
    teams->command_context->team_uuid = NULL;
    teams->command_context->channel_uuid = NULL;
    teams->command_context->thread_uuid = NULL;
    teams->command_context->team_context = NOTHING;
}
