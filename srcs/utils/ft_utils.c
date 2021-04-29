/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 07:11:19 by lessie            #+#    #+#             */
/*   Updated: 2021/04/29 15:23:01 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_exit(int err_code)
{
	if (err_code == -1)
		write(STDERR_FILENO, "Error\nWrong number of arguments\n", 32);
	if (err_code == -2)
		write(STDERR_FILENO, "Error\nCan't allocate memory for element\n", 40);
	if (err_code == -3)
		write(STDERR_FILENO, "Error\nCan't initialize mlx instance\n", 36);
	if (err_code == -4)
		write(STDERR_FILENO, "Error\nCan't initialize mlx window\n", 34);
	if (err_code == -5)
		write(STDERR_FILENO, "Error\nCan't open file\n", 22);
	if (err_code == -6)
		write(STDERR_FILENO, "Error\nSecond argument should be --save\n", 39);
	if (err_code == -7)
		write(STDERR_FILENO, "Error\nScene description hase no name\n", 37);
	if (err_code == -8)
		write(STDERR_FILENO,
				"Error\nScene description must be .rt extension\n", 46);
	if (err_code == -9)
		write(STDERR_FILENO, "Error\nScene Resolution doesn't correct\n", 39);
	if (err_code == -10)
		write(STDERR_FILENO,
				"Error\nCan't Create or Write into .BMP file\n", 43);
	if (err_code == -11)
		write(STDERR_FILENO, "Error\nScene doesn't have Camera\n", 32);
	exit(err_code);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (s1[i] == s2[i])
		return (1);
	return (0);
}

void	explicit_err(char *line, int num_of_line)
{
	int		i;

	i = 0;
	while (line[i])
		i++;
	write(STDERR_FILENO, "Error\nCheck line number: ", 25);
	putnbr(num_of_line, 1);
	write(STDERR_FILENO, "\nline content:\n", 15);
	write(STDERR_FILENO, line, i);
	write(STDERR_FILENO, "\n", 1);
	exit(-12);
}

void	ft_putstr(char *s, int fd)
{
	int		i;
	int		j;

	if (!s || fd < 0)
		return ;
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '/')
			j = i + 1;
		i++;
	}
	write(fd, &s[j], (i - j));
}

void	check_scene(t_scene *scene)
{
	if (scene->resolution_x == 0 || scene->resolution_y == 0)
		error_exit(-9);
	if (scene->cam_lst == NULL)
		error_exit(-11);
	if (scene->amb == NULL)
	{
		write(1, "Ambient Light hasn't been set up\n", 33);
		write(1, "Setting up default value of Ambient Light of 0.1\n", 49);
		scene->amb = new_amb(16777215, 0.1);
		scene->colb = new_colb(scene->amb);
	}
}
