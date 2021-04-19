/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:32:06 by lessie            #+#    #+#             */
/*   Updated: 2021/04/02 13:32:29 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_atoi(const char *str, int *num, int *i)
{
    unsigned int	j;
    int				sign;
    long int		nbr;

    j = 0;
    if (!str[j])
        return (0);
    sign = 1;
    nbr = 0;
    if (str[j] == '-' || str[j] == '+')
        if (str[j++] == '-')
            sign *= -1;
    while (str[j] >= '0' && str[j] <= '9')
    {
        nbr *= 10;
        nbr += (str[j] - '0');
        j++;
    }
    if (j == 0 || (j == 1 && (str[0] == '-' || str[0] == '+')))
        return (0);
    *num = (int)(nbr * sign);
    *i += (int)j;
    return (1);
}

int		ft_atoif(const char *str, int *num, int *i)
{
    unsigned int	j;
    long int		nbr;

    j = 0;
    if (!str[j])
        return (0);
    nbr = 0;
    if (str[j] == '-' || str[j] == '+')
        j++;
    while (str[j] >= '0' && str[j] <= '9')
    {
        nbr *= 10;
        nbr += (str[j] - '0');
        j++;
    }
    if (j == 0 || (j == 1 && (str[0] == '-' || str[0] == '+')))
        return (0);
    *num = (int)nbr;
    *i += (int)j;
    return (1);
}

int     ft_atof(const char *str, float *nbr, int *i)
{
    int     j;
    int     num;
    float   decimal;

    j = 0;
    decimal = str[0] == '-' ? -1.0 : 1.0;
    if (!(ft_atoif(str, &num, &j)))
        return (0);
    *nbr = num * decimal;
    if (str[j] == '.')
        j++;
    while (str[j] && str[j] >= '0' && str[j] <= '9')
    {
        decimal *= 0.1;
        *nbr += decimal * (str[j] - '0');
        j++;
    }
    *i += j;
    return (1);
}