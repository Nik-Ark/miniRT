/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:54:58 by lessie            #+#    #+#             */
/*   Updated: 2021/04/27 14:32:28 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_PARSE_H
# define LIGHT_PARSE_H

int		light_parse(t_scene *scene, const char *line);
int		check_append_light(t_scene *scene, float *vector, float inten, int rgb);

#endif
