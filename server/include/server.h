/*
** EPITECH PROJECT, 2024
** bs_myFTP_select
** File description:
** my
*/

    #include <stdbool.h>
    #include <netinet/ip.h>
    #include <sys/select.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include "teams.h"


#ifndef SERVER_H_
    #define SERVER_H_

    #define MAX_USER 1024
    #define BUFFER_MAX_SIZE 1024
    #define NB_CMD 15

    #define FAIL_MSG_LOGIN "530 Not logged in.\n"
    #define ALRD_LOGIN "531 Already logged in.\n"
    #define CODE_200 "200 Command okay.\n"

    #define ERR_BAD_ARG "504 Bad arguments\n"
    #define CODE_NOT_IMPLEMENTED "NOT YET IMPLEMENTED\n"

    #define CODE_101 "101 End of transmmission"

    #define CODE_201 "201 Client logged in.\n"
    #define CODE_202 "202 Client logged out.\n"
    #define CODE_203 "203 Print users.\n"
    #define CODE_204 "204 Print user.\n"
    #define CODE_205 "205 Private message received.\n"
    #define CODE_206 "206 Print private message.\n"
    #define CODE_207 "207 Print subscribed.\n"
    #define CODE_208 "208 Print teams.\n"
    #define CODE_209 "209 Print unsubscribed.\n"
    #define CODE_210 "210 Thread reply received.\n"
    #define CODE_211 "211 Event team created.\n"
    #define CODE_212 "212 Event channel created.\n"
    #define CODE_213 "213 Event thread created.\n"
    #define CODE_214 "214 Print team created.\n"
    #define CODE_215 "215 Print channel created.\n"
    #define CODE_216 "216 Print thread created.\n"
    #define CODE_217 "217 Print reply created.\n"
    #define CODE_218 "218 Team print channels.\n"
    #define CODE_219 "219 Channel print threads.\n"
    #define CODE_220 "220 Thread print replies.\n"
    #define CODE_221 "221 Print team.\n"
    #define CODE_222 "222 Print channel.\n"
    #define CODE_223 "223 Print thread.\n"
    #define CODE_224 "224 Help message.\n"

    #define CODE_301 "301 Error unauthorized.\n"
    #define CODE_302 "302 Error already exist.\n"

    #define CODE_401 "401 Error unknown user.\n"
    #define CODE_402 "402 Error unknown team.\n"
    #define CODE_403 "403 Error unknown channel.\n"
    #define CODE_404 "404 Error unknown thread.\n"

static char *const cmd_lst[NB_CMD] = {
    "/login",
    "/users",
    "/user",
    "/logout",
    "/send",
    "/messages",
    "/subscribe",
    "/create",
    "/help",
    "/subscribed",
    "/use",
    "/unsubscribe",
    "/list",
    "/info",
    "/quit"
};

enum cmd_status {
    NO_CMD,
    WIN_CMD,
    ERR_CMD
};

typedef struct clients_s {
    struct sockaddr_in sock_addr;
    int client_fd;
    bool is_connected;
    bool has_been_closed;
    char *username;
    char *my_uuid;
    user_t *new_user;
} clients_t;

typedef struct cmd_s {
    char **tab;
    size_t len;
} cmd_t;

typedef struct server_s {
    struct sockaddr_in sock_addr;
    int port;
    int server_fd;
    int *fd_array;
    size_t size;
    int max_fd_set;
    int user_index;
    fd_set readfds;
    clients_t **clients;
    cmd_t cmd_arg;
} server_t;

#endif /* !SERVER_H_ */
