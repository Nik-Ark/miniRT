/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_str.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 22:27:21 by lessie            #+#    #+#             */
/*   Updated: 2021/01/09 22:28:44 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_STR_H
# define FT_UTILS_STR_H

char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strchr(char *str, int c);
char	*ft_new_zerostr(int len);
void	ft_fillzero(char *str, int len);
char	*ft_strcpy(char *dst, char *src);

#endif
