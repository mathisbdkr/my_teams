/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** my_get_timestamp
*/

#include "my.h"

long int my_get_timestamp(char const *str)
{
    int i = 0;
    long int nb = 0;
    int nb_length = 0;

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            nb = nb * 10 + (str[i] - '0');
            nb_length += 1;
        }
        if (!(str[i] >= '0' && str[i] <= '9') && (nb_length > 0)) {
            break;
        }
        i++;
    }
    return (nb);
}
