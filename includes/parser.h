/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:50:22 by lessie            #+#    #+#             */
/*   Updated: 2021/04/27 14:38:23 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int		open_fd(const char *file);
t_scene	*parsing(int fd);
int		parse_line(t_scene *scene, const char *line);
int		parse_rgb(const char *line, int *rgb, int *i);
void	cycling_cams(t_scene *scene);
void	eat_spaces(const char *line, int *i);
int		num_coma(const char *line, int *i, int *nums);

#endif
