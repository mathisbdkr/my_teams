/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** parse_users
*/


#include "teams.h"
#include "my.h"

static void fill_team_belong(user_t *user, char **array)
{
    team_belong_t *team_belong;

    for (size_t i = 1; array[i] != NULL; i += 1) {
        if (strlen(array[i]) < MAX_UUID_LENGTH) {
            team_belong = malloc(sizeof(team_belong_t));
            TAILQ_INSERT_TAIL(&user->team_belong_head, team_belong,
                belong_entries);
            strcpy(team_belong->uuid, array[i]);
        }
    }
}

static void fill_user(char *line, user_t *user, char **array)
{
    if (strncmp(line, "\tuuid=", strlen("\tuuid=")) == 0 &&
        strlen(array[1]) < MAX_UUID_LENGTH)
        strcpy(user->uuid, array[1]);
    if (strncmp(line, "\tname=", strlen("\tname=")) == 0 &&
        strlen(array[1]) < MAX_NAME_LENGTH)
        strcpy(user->name, array[1]);
    if (strncmp(line, "\tis_logged=", strlen("\tis_logged=")) == 0) {
        user->is_logged = my_getnbr(array[1]);
        server_event_user_loaded(user->uuid, user->name);
    }
    if (strncmp(line, "\tteams_uuid=", strlen("\tteams_uuid=")) == 0)
        fill_team_belong(user, array);
}

void parse_users(my_teams_t *teams, char *line, int *is_user)
{
    static user_t *user;
    char **array = word_array(line, "\t\n=,:");

    if (strcmp(line, "user:\n") == 0) {
        user = malloc(sizeof(user_t));
        TAILQ_INSERT_TAIL(&teams->user_head, user, user_entries);
        TAILQ_INIT(&user->team_belong_head);
        *is_user = 0;
    }
    if (array_size(array) < 2 || *is_user != 0) {
        free(array);
        return;
    }
    fill_user(line, user, array);
    free(array);
}
