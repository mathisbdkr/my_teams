/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** my_swap_str
*/

void my_swap_str(char **a, char **b)
{
    char *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}
