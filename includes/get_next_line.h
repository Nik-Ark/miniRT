/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 14:55:00 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:09:43 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1028
# endif

typedef struct		s_lst
{
	int				fd;
	int				eof;
	char			*delim;
	struct s_lst	*prev;
	struct s_lst	*next;
}					t_lst;

int					get_next_line(int fd, char **line);
int					ft_freelst_gnl(t_lst **head, t_lst *lst);
t_lst				*ft_newlst_gnl(const int fd);
int					ft_readfd_gnl(t_lst **head, t_lst *lst, char **line);
int					ft_readdelim_gnl(t_lst **head, t_lst *lst, char **line);

#endif
