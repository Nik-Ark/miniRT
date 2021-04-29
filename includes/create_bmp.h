/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:03:40 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:05:45 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_BMP_H
# define CREATE_BMP_H

void	create_bmp(const char *filename_rt);
char	*get_filename(const char *filename_rt);
void	write_first_header(int num_of_bytes, int fd);
void	write_second_header(int res_x, int res_y, int fd);
void	write_pixels(t_scene *scene, int padding, int fd);
void	put_pixel(int color, int fd);
void	add_padding(int padding, int fd);

#endif
