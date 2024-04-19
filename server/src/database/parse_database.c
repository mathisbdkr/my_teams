/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** parse_database
*/


#include "teams.h"
#include "my.h"

void parse_database(my_teams_t *teams)
{
    FILE *stream = fopen(".database", "r");
    char *line = NULL;
    size_t len = 0;
    int is_user = 0;

    if (!stream)
        return;
    while (getline(&line, &len, stream) != -1) {
        parse_users(teams, line, &is_user);
        parse_teams(teams, line, &is_user);
        parse_mp(teams, line, &is_user);
    }
    fclose(stream);
    if (line != NULL)
        free(line);
}
