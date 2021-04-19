/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_eat_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 21:50:01 by lessie            #+#    #+#             */
/*   Updated: 2021/04/06 21:50:29 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int     check_eat_space(const char *line, int *i)
{
    int     j;

    j = 0;
    if (line[j] != ' ' && line[j] != '\t')
        return (0);
    while (line[j] == ' ' || line[j] == '\t')
        j++;
    *i += j;
    return (1);
}

int     check_end_line(const char *line)
{
    int     j;

    j = 0;
    while (line[j] == ' ' || line[j] == '\t')
        j++;
    if (line[j] != '\0')
        return (0);
    return (1);
}