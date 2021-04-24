/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:08:09 by lessie            #+#    #+#             */
/*   Updated: 2021/02/04 22:39:05 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int		get_r(int rgb)
{
	int		result;

	result = (rgb & (255 << 16));
	return (result >> 16);
}

int		get_g(int rgb)
{
	int		result;

	result = (rgb & (255 << 8));
	return (result >> 8);
}

int		get_b(int rgb)
{
	return (rgb & 255);
}
