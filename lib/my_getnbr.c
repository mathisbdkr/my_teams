/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-yanis.harkouk
** File description:
** my_getnbr
*/

int my_getnbr(char const *str)
{
    int i = 0;
    int nb = 0;
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
