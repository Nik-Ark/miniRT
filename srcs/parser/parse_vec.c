/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 21:02:06 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 18:08:46 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_vec(const char *line, float *vecs, int num_vecs, int *i)
{
	int		j;
	int		k;
	int		nums;

	nums = num_vecs * 2;
	j = 0;
	k = 0;
	while (num_vecs-- > 0)
	{
		if (!(ft_atof(&line[j], &vecs[k++], &j)))
			return (0);
		if (!(num_coma(&line[j], &j, &nums)))
			return (0);
		if (!(ft_atof(&line[j], &vecs[k++], &j)))
			return (0);
		if (!(num_coma(&line[j], &j, &nums)))
			return (0);
		if (!(ft_atof(&line[j], &vecs[k++], &j)))
			return (0);
		if (num_vecs > 0)
			if (!(check_eat_space(&line[j], &j)))
				return (0);
	}
	*i += j;
	return (nums == 0 ? 1 : 0);
}
