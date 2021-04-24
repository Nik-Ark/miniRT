/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 07:11:19 by lessie            #+#    #+#             */
/*   Updated: 2021/02/17 10:52:53 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_exit(int err_code)
{
	if (err_code == -1)
		write(STDERR_FILENO, "Error\n Wrong number of arguments\n", 35);
	if (err_code == -2)
		write(STDERR_FILENO, "Error\n Can't allocate memory for new element\n", 47);
    if (err_code == -3)
        write(STDERR_FILENO, "Error\n Can't initialize mlx instance\n", 39);
    if (err_code == -4)
        write(STDERR_FILENO, "Error\n Can't initialize mlx window\n", 37);
    if (err_code == -5)
        write(STDERR_FILENO, "Error\n Can't open file\n", 25);
    if (err_code == -6)
        write(STDERR_FILENO, "Error\n Second argument should be --save if exists\n", 51);
    if (err_code == -7)
        write(STDERR_FILENO, "Error\n Scene description should have some name\n", 49);
    if (err_code == -8)
        write(STDERR_FILENO, "Error\n Scene description should have .rt extension\n", 53);
    if (err_code == -9)
        write(STDERR_FILENO, "Error\n Scene description syntax error\n", 40);
    if (err_code == -10)
        write(STDERR_FILENO, "Error\n Can't Create or Write into .BMP file\n", 46);
	exit(err_code);
}

int		ft_strcmp(const char *s1, const char *s2)
{
    int     i;

    i = 0;
    while (s1[i] == s2[i] && s1[i] && s2[i])
        i++;
    if (s1[i] == s2[i])
        return (1);
    return (0);
}