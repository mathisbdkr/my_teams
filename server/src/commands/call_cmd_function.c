/*
** EPITECH PROJECT, 2024
** all_teams
** File description:
** call_cmd_function
*/

#include "my.h"

int (*cmd_func[NB_CMD])(server_t *server,
    const int client_fd, my_teams_t *team) = {
    &user_login,
    &user_cmd,
    &user_spe_uuid,
    &quit_cmd,
    &send_msg,
    &display_priv_msg,
    &sub_team,
    &create,
    &help_cmd,
    &disp_subscribed,
    &use_cmd,
    &unsub_team,
    &list,
    &info,
    &handle_ctrl_c
};

int error_not_login(server_t *server, const int client_fd)
{
    if (server->clients[server->user_index]->is_connected == false) {
        my_fd_putstr(CODE_301, client_fd);
        my_fd_putstr(CODE_101, client_fd);
        return 1;
    }
    return 0;
}

static void check_additional_space(server_t *server,
    const size_t x, const size_t y)
{
    if (server->cmd_arg.tab[x][y + 1] == '\0'
        && server->cmd_arg.tab[x][y] == ' ')
        server->cmd_arg.tab[x][y] = '\0';
}

static void swap_empty_strings(server_t *server, bool *has_swapped)
{
    for (size_t x = 0; server->cmd_arg.tab[x + 1] != NULL; x++) {
        if (strcmp(server->cmd_arg.tab[x], "\0") == 0) {
            my_swap_str(&server->cmd_arg.tab[x], &server->cmd_arg.tab[x + 1]);
            *has_swapped = true;
        }
        if (strcmp(server->cmd_arg.tab[server->cmd_arg.len - 1], "\0") == 0) {
            server->cmd_arg.tab[server->cmd_arg.len - 1] = NULL;
            server->cmd_arg.len -= 1;
        }
    }
}

static void realloc_arg(server_t *server)
{
    bool has_swapped = true;

    for (size_t x = 0; server->cmd_arg.tab[x] != NULL; x++) {
        for (size_t y = 0; server->cmd_arg.tab[x][y] != '\0'; y += 1) {
            check_additional_space(server, x, y);
        }
    }
    while (has_swapped) {
        has_swapped = false;
        swap_empty_strings(server, &has_swapped);
    }
}

static bool valid_number_of_quotes(const char *str, const int client_fd)
{
    if (count_occurences(str, '\"') % 2 != 0) {
        my_fd_putstr(CODE_301, client_fd);
        my_fd_putstr(CODE_101, client_fd);
        return false;
    }
    return true;
}

void get_user_input(server_t *server, const int client_fd, my_teams_t *teams)
{
    char buffer[BUFFER_MAX_SIZE] = {0};
    int status = 0;

    if (read(client_fd, buffer, BUFFER_MAX_SIZE) == 0)
        return;
    if (!valid_number_of_quotes(buffer, client_fd))
        return;
    server->cmd_arg.tab = word_array(buffer, "\"\n\r");
    server->cmd_arg.len = array_size(server->cmd_arg.tab);
    realloc_arg(server);
    for (size_t i = 0; i < NB_CMD; i++) {
        if (server->cmd_arg.len >= 1 &&
        strcmp(server->cmd_arg.tab[0], cmd_lst[i]) == 0)
            status = cmd_func[i](server, client_fd, teams);
    }
    if (status == 0) {
        my_fd_putstr(CODE_301, client_fd);
        my_fd_putstr(CODE_101, client_fd);
    }
    free(server->cmd_arg.tab);
}
