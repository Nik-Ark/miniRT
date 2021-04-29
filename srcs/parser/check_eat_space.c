/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_eat_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 21:50:01 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:59:45 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		check_eat_space(const char *line, int *i)
{
	int		j;

	j = 0;
	if (line[j] != ' ' && line[j] != '\t')
		return (0);
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	*i += j;
	return (1);
}

int		check_end_line(const char *line)
{
	int		j;

	j = 0;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if (line[j] != '\0')
		return (0);
	return (1);
}

int		num_coma(const char *line, int *i, int *nums)
{
	int		j;

	j = 0;
	eat_spaces(&line[j], &j);
	if (line[j++] != ',')
		return (0);
	eat_spaces(&line[j], &j);
	if (!((line[j] == '-' || line[j] == '+')
				|| (line[j] >= '0' && line[j] <= '9')))
		return (0);
	*i += j;
	*nums -= 1;
	return (1);
}

void	eat_spaces(const char *line, int *i)
{
	int		j;

	j = 0;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	*i += j;
}
