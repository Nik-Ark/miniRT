/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:22:59 by lessie            #+#    #+#             */
/*   Updated: 2021/02/13 07:51:00 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define BACKGROUND 0

int		create_rgb(int r, int g, int b);
int		get_r(int rgb);
int		get_g(int rgb);
int		get_b(int rgb);
void	add_color(t_colb *colb, t_light *light, float angle, float mult);

#endif
