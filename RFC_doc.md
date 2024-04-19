###
# Client side
###

### • /login [“user_name”] : set the user_name used by client
- client_event_logged_in -- 201

###

### • /logout : disconnect the client from the server
- client_event_logged_out -- 202

###

### • /users : get the list of all users that exist on the domain
- client_print_users -- 203

###

### • /user [“user_uuid”] : get details about the requested user
- client_error_unknown_user -- 401
- client_print_user -- 204

###

### • /send [“user_uuid”] [“message_body”] : send a message to specific user
- client_event_private_message_received -- 205
- client_error_unknown_user -- 401

###

### • /messages [“user_uuid”] : list all messages exchanged with the specified user
- client_private_message_print_messages -- 206
- client_error_unknown_user -- 401

###

### • /subscribe [“team_uuid”] : subscribe to the events of a team and its sub directories (enable reception
of all events from a team)
- client_error_unknown_team -- 402
- client_print_subscribed -- 207

###

### • /subscribed ?[“team_uuid”] : list all subscribed teams or list all users subscribed to a team
- client_print_users -- 203
- client_error_unknown_team -- 402
- client_print_teams -- 208

###

### • /unsubscribe [“team_uuid”] : unsubscribe from a team
- client_error_unknown_team -- 402
- client_print_unsubscribed -- 209

###

### • /use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] : Sets the command context to a team/channel/thread
- client_error_unknown_team -- 402
- client_error_unknown_channel -- 403
- client_error_unknown_thread -- 404

###

### • /create : based on the context, create the sub resource (see below)
- client_event_thread_reply_received -- 210
- client_event_team_created -- 211
- client_event_channel_created -- 212
- client_event_thread_created -- 213
- client_error_unauthorized -- 301
- client_error_already_exist -- 302
- client_print_team_created -- 214
- client_print_channel_created -- 215
- client_print_thread_created -- 216
- client_print_reply_created -- 217

###

### • /list : based on the context, list all the sub resources (see below)
- client_print_teams -- 208
- client_team_print_channels -- 218
- client_channel_print_threads -- 219
- client_thread_print_replies -- 220
- client_error_unknown_team -- 402
- client_error_unknown_channel -- 403
- client_error_unknown_thread -- 404

###

### • /info : based on the context, display details of the current resource (see below)
- client_error_unknown_team -- 402
- client_error_unknown_channel -- 403
- client_error_unknown_thread -- 404
- client_print_user -- 204
- client_print_team -- 221
- client_print_channel -- 222
- client_print_thread -- 223

###
# Server side
###

### At server start :
- server_event_user_loaded

#####

### • /login
- server_event_user_created
- server_event_user_logged_in

###

### • /logout
- server_event_user_logged_out

###

### • /send
- server_event_private_message_sended

###

### • /subscribe
- server_event_user_subscribed

###

### • /unsubscribe
- server_event_user_unsubscribed

###

### • /create
- server_event_team_created
- server_event_channel_created
- server_event_thread_created
- server_event_reply_created


````c
int server_event_team_created(char const *team_uuid, char const *team_name, char const *user_uuid);

int server_event_channel_created(char const *team_uuid, char const *channel_uuid, char const *channel_name);

int server_event_thread_created(char const *channel_uuid, char const *thread_uuid, char const *user_uuid, char const *thread_title, char const *thread_body);

int server_event_reply_created(char const *thread_uuid, char const *user_uuid, char const *reply_body);

int server_event_user_subscribed(char const *team_uuid, char const *user_uuid);

int server_event_user_unsubscribed(char const *team_uuid, char const *user_uuid);

int server_event_user_created(char const *user_uuid, char const *user_name);

int server_event_user_loaded(char const *user_uuid, char const *user_name);

int server_event_user_logged_in(char const *user_uuid);

int server_event_user_logged_out(char const *user_uuid);

int server_event_private_message_sended(char const *sender_uuid, char const *receiver_uuid, char const *message_body);
```