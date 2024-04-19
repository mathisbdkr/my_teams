/*
** EPITECH PROJECT, 2024
** bs_myFTP
** File description:
** client
*/

#include <signal.h>
#include "client.h"
#include <errno.h>

int ctrl_c;

static void exit_program(int signal)
{
    if (signal == SIGINT)
        ctrl_c = 0;
}

static int check_socket_creation(const int port, const int sock_fd)
{
    if (port == 0) {
        fprintf(stdout, "argument isn't a port");
        return 84;
    }
    if (sock_fd == -1) {
        fprintf(stdout, "socket creation failed");
        return 84;
    }
    return 0;
}

static int connect_to_server(const char **av, struct sockaddr_in *sock_addr,
    struct in_addr *in_addr, int port)
{
    if (inet_aton(av[1], in_addr) == 0) {
        fprintf(stdout, "invalid ip adress");
        return 84;
    }
    sock_addr->sin_family = AF_INET;
    sock_addr->sin_addr.s_addr = inet_addr(av[1]);
    sock_addr->sin_port = htons(port);
    return 0;
}

static char *rm_first_ligne(char *str)
{
    char *dest;
    int size = 0;

    while (str[size] != '\n') {
        size++;
    }
    dest = malloc(sizeof(char) * (strlen(str) - size) + 1);
    dest[strlen(str) - size] = '\0';
    for (int i = 0; str[i + size] != '\0'; i++) {
        dest[i] = str[i + size];
    }
    return dest;
}

static client_buf_t init_buffer_struct(void)
{
    client_buf_t buf_struct;

    buf_struct.loop_read = 0;
    buf_struct.pass = 0;
    buf_struct.code = NULL;
    return buf_struct;
}

static int read_response(const int sock_fd)
{
    char reponse[1024] = {0};
    char **tab;
    client_buf_t buf_struct = init_buffer_struct();

    while (buf_struct.loop_read == 0) {
        if (read(sock_fd, reponse, 1023) <= 0)
            return 1;
        buf_struct.all_reponse = strdup(reponse);
        if (buf_struct.code == NULL) {
            tab = word_array(reponse, "\n");
            buf_struct.code = strdup(word_array(tab[0], " ")[0]);
            buf_struct.all_reponse = strdup(rm_first_ligne(reponse));
        }
        if (strcmp(buf_struct.code, "301") == 0)
            buf_struct.pass++;
        buf_struct.loop_read = select_display_methode(buf_struct);
    }
    return 0;
}

static int read_server(const int sock_fd, fd_set readfds)
{
    size_t len = 0;
    char *line = NULL;

    if (select(sock_fd + 1, &readfds, NULL, NULL, NULL) == -1) {
        return 1;
    }
    if (FD_ISSET(0, &readfds)) {
        if (getline(&line, &len, stdin) > 0) {
            line[strlen(line) - 1] = '\0';
            write(sock_fd, line, strlen(line));
        }
    }
    if (FD_ISSET(sock_fd, &readfds)) {
        if (read_response(sock_fd) != 0)
            return 2;
        write(1, "Enter the command : ", strlen("Enter the command : "));
    }
    return 0;
}

static void send_initial_command(const int sock_fd, const char *cmd)
{
    char buffer[1024];

    write(sock_fd, cmd, strlen(cmd));
    read(sock_fd, buffer, 1024 - 1);
}

static void client_loop(int sock_fd)
{
    fd_set readfds;

    write(1, "Enter the command : ", strlen("Enter the command : "));
    ctrl_c = 1;
    signal(SIGINT, exit_program);
    while (ctrl_c) {
        FD_ZERO(&readfds);
        FD_SET(sock_fd, &readfds);
        FD_SET(0, &readfds);
        if (read_server(sock_fd, readfds) == 2)
            return;
    }
    send_initial_command(sock_fd, "/quit");
}

int client(const char **av)
{
    int port = atoi(av[2]);
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sock_addr;
    struct in_addr in_addr;

    if (check_socket_creation(port, sock_fd) == 84)
        return 84;
    if (connect_to_server(av, &sock_addr, &in_addr, port) == 84)
        return 84;
    if (connect(sock_fd, (struct sockaddr*)&sock_addr,
        sizeof(sock_addr)) == -1) {
        perror("connect");
        return 84;
    }
    send_initial_command(sock_fd, "");
    client_loop(sock_fd);
    close(sock_fd);
    return 0;
}
