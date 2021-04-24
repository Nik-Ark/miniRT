/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:54:16 by lessie            #+#    #+#             */
/*   Updated: 2021/04/02 14:54:48 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RES_PARSE_H
# define RES_PARSE_H

int     res_parse(t_scene **scene, const char *line);
int     check_append_res(t_scene **scene, int x, int y);

#endif
