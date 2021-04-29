/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 22:28:56 by lessie            #+#    #+#             */
/*   Updated: 2021/04/27 14:26:21 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

void	error_exit(int err_code);
int		ft_strcmp(const char *s1, const char *s2);
void	explicit_err(char *line, int num_of_line);
void	ft_putstr(char *s, int fd);
void	check_scene(t_scene *scene);

#endif
