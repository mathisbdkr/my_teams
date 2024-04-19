/*
** EPITECH PROJECT, 2024
** bs_myFTP_select
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include "server.h"
    #include "teams.h"
    #include "logging_server.h"
    #include <uuid/uuid.h>
    #include <stddef.h>

// lib
int array_size(char **array);
void print_array(char **array);
void free_array(char **array);
char *concat_strings(char *str1, char *str2, char *delim);
bool array_is_number(char **array);
char **word_array(char const *str, char *delim);
void my_swap_str(char **a, char **b);
void my_fd_putstr(char *str, const int client_fd);
int my_getnbr(char const *str);
long int my_get_timestamp(char const *str);
int count_occurences(const char *str, const char c);

// server
int server(const char *port_number);
server_t *init_server_struct(const char *port_number);
int initialize_server(server_t *server);
int run_server(server_t *server);
int insert_client_in_struct(server_t *server, const int client_fd);
void close_client_socket(server_t *server);

void get_user_input(server_t *server, const int client_fd, my_teams_t *team);
int error_not_login(server_t *server, const int client_fd);

int user_login(server_t *server, const int client_fd, my_teams_t *team);
int quit_cmd(server_t *server, const int client_fd, my_teams_t *team);
int list_cmd(server_t *server, const int client_fd, my_teams_t *team);
int display_priv_msg(server_t *server, const int client_fd, my_teams_t *team);
int user_cmd(server_t *server, const int client_fd, my_teams_t *team);
int user_spe_uuid(server_t *server, const int client_fd, my_teams_t *team);
int cdup_cmd(server_t *server, const int client_fd, my_teams_t *team);
int send_msg(server_t *server, const int client_fd, my_teams_t *team);
int help_cmd(server_t *server, const int client_fd, my_teams_t *team);
int sub_team(server_t *server, const int client_fd, my_teams_t *team);
int retr_cmd(server_t *server, const int client_fd, my_teams_t *team);
int stor_cmd(server_t *server, const int client_fd, my_teams_t *team);
int disp_subscribed(server_t *server, const int client_fd, my_teams_t *teams);
int use_cmd(server_t *server, const int client_fd, my_teams_t *teams);
int unsub_team(server_t *server, const int client_fd, my_teams_t *teams);
int handle_ctrl_c(server_t *server, const int client_fd, my_teams_t *teams);
void reset_command_context(my_teams_t *teams);

//create
int create(server_t *server, const int client_fd, my_teams_t *teams);
int create_team(server_t *server, const int client_fd, my_teams_t *teams);
int create_channel(server_t *server, const int client_fd, my_teams_t *teams);
int create_thread(server_t *server, const int client_fd, my_teams_t *teams);
int create_comment(server_t *server, const int client_fd, my_teams_t *teams);

//list
int list(server_t *server, const int client_fd, my_teams_t *teams);
int list_team(const int client_fd, my_teams_t *teams);
int list_channel(const int client_fd, my_teams_t *teams);
int list_thread(const int client_fd, my_teams_t *teams);
int list_comment(const int client_fd, my_teams_t *teams);

//info
int info(server_t *server, const int client_fd, my_teams_t *teams);
int info_user(server_t *server, const int client_fd);
int info_team(const int client_fd, my_teams_t *teams);
int info_channel(const int client_fd, my_teams_t *teams);
int info_thread(const int client_fd, my_teams_t *teams);

// database
void parse_database(my_teams_t *teams);
void parse_teams(my_teams_t *teams, char *line, int *is_user);
void parse_users(my_teams_t *teams, char *line, int *is_user);
void parse_mp(my_teams_t *teams, char *line, int *is_user);
void save_database(const my_teams_t teams);

#endif /* !MY_H_ */
