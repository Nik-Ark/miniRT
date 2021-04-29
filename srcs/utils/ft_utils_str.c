/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 18:19:45 by lessie            #+#    #+#             */
/*   Updated: 2020/12/21 16:12:31 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*new_s;
	unsigned int	i;
	unsigned int	j;
	unsigned int	s1_len;
	unsigned int	s2_len;

	if (!s1 || !s2)
		return (NULL);
	new_s = NULL;
	s1_len = 0;
	s2_len = 0;
	while (s1[s1_len])
		s1_len++;
	while (s2[s2_len])
		s2_len++;
	i = -1;
	j = -1;
	if (!(new_s = malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	while (++i < s1_len)
		new_s[i] = s1[i];
	while (++j < s2_len)
		new_s[i + j] = s2[j];
	new_s[i + j] = '\0';
	return (new_s);
}

int		ft_strchr(char *str, int c)
{
	char	ch;
	int		i;

	ch = (char)c;
	i = 0;
	while (str[i] != ch && str[i] != '\0')
		i++;
	if (str[i] == ch)
	{
		str[i] = '\0';
		return (i);
	}
	else
		return (-1);
}

char	*ft_strcpy(char *dst, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_new_zerostr(int len)
{
	char	*str;

	str = NULL;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_fillzero(str, (len + 1));
	return (str);
}

void	ft_fillzero(char *str, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		str[i] = '\0';
		i++;
	}
}
