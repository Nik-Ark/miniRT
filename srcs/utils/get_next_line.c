/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:51:03 by lessie            #+#    #+#             */
/*   Updated: 2020/12/21 16:12:13 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		get_next_line(int fd, char **line)
{
	static t_lst	*head;
	t_lst			*tmp;

	if (fd < 0 || !line || (BUFFER_SIZE <= 0))
		return (-1);
	if (!head)
		if (!(head = ft_newlst_gnl(fd)))
			return (-1);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
		{
			if (!(tmp->next = ft_newlst_gnl(fd)))
				return (ft_freelst_gnl(&head, tmp) - 1);
			tmp->next->prev = tmp;
		}
		tmp = tmp->next;
	}
	if (!(*line = ft_new_zerostr(0)))
		return (ft_freelst_gnl(&head, tmp) - 1);
	if (tmp->delim[0] == '\0' && tmp->eof == 0)
		return (ft_readfd_gnl(&head, tmp, line));
	else
		return (ft_readdelim_gnl(&head, tmp, line));
}

int		ft_readfd_gnl(t_lst **head, t_lst *lst, char **line)
{
	char	buf[BUFFER_SIZE + 1];
	int		newln_index;
	char	*tmp;
	int		ret;

	tmp = NULL;
	while ((ret = read(lst->fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if ((newln_index = ft_strchr(buf, '\n')) >= 0)
			lst->delim = ft_strcpy(lst->delim, &buf[newln_index + 1]);
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buf)))
			return ((ft_freelst_gnl(head, lst)) - 1);
		free(tmp);
		if (newln_index >= 0)
			break ;
	}
	if (ret == -1)
		return ((ft_freelst_gnl(head, lst)) - 1);
	if (ret == 0)
		lst->eof = 1;
	if (ret == 0 && lst->delim[0] == '\0')
		return (ft_freelst_gnl(head, lst));
	return (1);
}

int		ft_readdelim_gnl(t_lst **head, t_lst *lst, char **line)
{
	int		newln_index;
	char	*tmp;

	tmp = NULL;
	if ((newln_index = ft_strchr(lst->delim, '\n')) >= 0)
	{
		tmp = *line;
		if (!(*line = ft_strjoin(*line, lst->delim)))
			return (ft_freelst_gnl(head, lst) - 1);
		free(tmp);
		lst->delim = ft_strcpy(lst->delim, &lst->delim[newln_index + 1]);
		if (lst->eof == 1 && lst->delim[0] == '\0')
			return (ft_freelst_gnl(head, lst));
		return (1);
	}
	tmp = *line;
	if (!(*line = ft_strjoin(*line, lst->delim)))
		return (ft_freelst_gnl(head, lst) - 1);
	free(tmp);
	if (lst->eof == 1)
		return (ft_freelst_gnl(head, lst));
	ft_fillzero(lst->delim, BUFFER_SIZE + 1);
	return (ft_readfd_gnl(head, lst, line));
}

t_lst	*ft_newlst_gnl(const int fd)
{
	t_lst	*new;

	if (!(new = malloc(sizeof(t_lst))))
		return (NULL);
	new->fd = fd;
	new->eof = 0;
	if (!(new->delim = ft_new_zerostr(BUFFER_SIZE + 1)))
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int		ft_freelst_gnl(t_lst **head, t_lst *lst)
{
	free(lst->delim);
	if (lst->prev == NULL)
		if (lst->next != NULL)
		{
			*head = lst->next;
			lst->next->prev = NULL;
		}
		else
			*head = NULL;
	else if (lst->next == NULL)
		lst->prev->next = NULL;
	else
	{
		lst->prev->next = lst->next;
		lst->next->prev = lst->prev;
	}
	free(lst);
	return (0);
}
