/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:52:29 by lessie            #+#    #+#             */
/*   Updated: 2021/04/27 13:57:15 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMB_PARSE_H
# define AMB_PARSE_H

int		amb_parse(t_scene *scene, const char *line);
int		check_append_amb(t_scene *scene, float inten, int rgb);

#endif
