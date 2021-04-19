/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:19:50 by lessie            #+#    #+#             */
/*   Updated: 2021/02/17 09:53:16 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_closest	*new_closest()
{
	t_closest	*closest;

	closest = malloc(sizeof(t_closest));
	if (!closest)
		error_exit(-2);
	closest->type = 0;
	closest->dist = 0;
	closest->x = 0;
	closest->y = 0;
	closest->sphere = NULL;
	closest->plane = NULL;
	closest->triang = NULL;
	closest->cylinder = NULL;
	return (closest);
}
