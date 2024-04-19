/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-yanis.harkouk
** File description:
** count_occurences
*/

int count_occurences(const char *str, const char c)
{
    int occurences = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == c)
            occurences++;
    return occurences;
}
