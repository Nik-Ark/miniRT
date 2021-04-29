/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:20:26 by lessie            #+#    #+#             */
/*   Updated: 2021/04/29 15:24:51 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUTNBR_H
# define PUTNBR_H

# include "minirt.h"

int		ft_numlen_pars(long int nbr);
void	ft_numchar_pars(char *str, int len, long int nbr, int is_neg);
void	ft_putstr_fd(char *s, int fd);
void	putnbr(int n, int fd);

#endif
