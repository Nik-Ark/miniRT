/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:21:02 by lessie            #+#    #+#             */
/*   Updated: 2021/04/29 15:22:28 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_numlen_pars(long int nbr)
{
	int		len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

void	ft_numchar_pars(char *str, int len, long int nbr, int is_neg)
{
	int		i;

	i = 0;
	if (is_neg)
		str[i++] = '-';
	str[len] = '\0';
	while (--len >= i)
	{
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	if (!s || fd < 0)
		return ;
	i = 0;
	while (s[i] != '\0')
		i++;
	write(fd, s, i);
}

void	putnbr(int n, int fd)
{
	char		str[12];
	int			is_neg;
	int			len;
	long int	nbr;

	if (fd < 0)
		return ;
	is_neg = 0;
	if (n < 0)
	{
		nbr = (long int)n * (-1);
		is_neg = 1;
	}
	else
		nbr = n;
	len = ft_numlen_pars(nbr) + is_neg;
	ft_numchar_pars(str, len, nbr, is_neg);
	ft_putstr_fd(str, fd);
}
