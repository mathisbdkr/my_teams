##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

CC = gcc

SERVER_SRC =                						\
	./server/src/initialize_server.c                \
    ./server/src/insert_client_in_struct.c          \
    ./server/src/close_client_socket.c              \
    ./server/src/run_server.c                       \
    ./server/src/server.c                           \
    ./server/src/commands/login_command.c           \
    ./server/src/commands/call_cmd_function.c       \
    ./server/src/commands/help/help_cmd.c           \
    ./server/src/commands/logout.c      	        \
    ./server/src/commands/user_list_command.c       \
    ./server/src/commands/private_msg.c             \
    ./server/src/commands/disp_priv_msg.c           \
    ./server/src/commands/sub_teams.c               \
    ./server/src/commands/unsub.c                   \
    ./server/src/commands/use.c                     \
    ./server/src/commands/reset_command_context.c   \
    ./server/src/commands/create/create.c           \
    ./server/src/commands/create/create_team.c      \
    ./server/src/commands/create/create_channel.c   \
    ./server/src/commands/create/create_thread.c    \
    ./server/src/commands/create/create_comment.c   \
    ./server/src/commands/list/list.c               \
    ./server/src/commands/list/list_team.c          \
    ./server/src/commands/list/list_channel.c       \
    ./server/src/commands/list/list_thread.c        \
    ./server/src/commands/list/list_comment.c       \
    ./server/src/commands/info/info.c               \
    ./server/src/commands/info/info_user.c          \
    ./server/src/commands/info/info_team.c          \
    ./server/src/commands/info/info_channel.c       \
    ./server/src/commands/info/info_thread.c        \
    ./server/src/database/parse_database.c          \
    ./server/src/database/save_database.c           \
    ./server/src/database/parse_teams.c             \
    ./server/src/database/parse_users.c             \
    ./server/src/database/parse_mp.c                \
	./server/main.c

CLIENT_SRC =                				\
	./client/src/client.c					\
	./client/src/redirect_print.c           \
    ./client/src/display_multiple_print.c   \
    ./client/main.c

LIB =                                       \
    lib/is_number.c                         \
    lib/concat_strings.c                    \
    lib/array_functions.c	                \
	lib/word_array.c                        \
    lib/my_swap_str.c                       \
    lib/fd_putstr.c                         \
    lib/my_getnbr.c                         \
    lib/my_get_timestamp.c                  \
    lib/count_occurences.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)			\
	$(LIB:.c=.o)

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)			\
	$(LIB:.c=.o)

CFLAGS = -W -Wall -Wextra -I server/include -I client/include -I libs/myteams

LDFLAGS = -Llibs/myteams -lmyteams -luuid

FLAGS_DEBUG = -g3

SERVER_BIN_NAME = myteams_server

CLIENT_BIN_NAME = myteams_cli

all: compil_server compil_client

compil_server: $(SERVER_OBJ)
	$(CC) -o  $(SERVER_BIN_NAME) $(SERVER_OBJ) $(LDFLAGS)

compil_client: $(CLIENT_OBJ)
	$(CC) -o $(CLIENT_BIN_NAME) $(CLIENT_OBJ) $(LDFLAGS)

debug: CFLAGS += $(FLAGS_DEBUG)
debug: all

clean:
	rm -f $(SERVER_OBJ)
	rm -f $(CLIENT_OBJ)

fclean: clean
	rm -f $(SERVER_BIN_NAME)
	rm -f $(CLIENT_BIN_NAME)

re: fclean all

.PHONY: debug fclean clean re all
