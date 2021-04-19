/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:42:24 by lessie            #+#    #+#             */
/*   Updated: 2021/02/17 09:52:10 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSEST_H
# define CLOSEST_H

# include "sphere.h"

typedef struct		s_closest
{
	int				type;
	float			dist;
	float			x;
	float			y;
	struct s_sphere	*sphere;
	struct s_plane  *plane;
	struct s_triang *triang;
	struct s_cyl    *cylinder;
}					t_closest;

t_closest			*new_closest();

#endif
