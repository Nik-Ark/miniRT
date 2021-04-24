/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 20:35:27 by lessie            #+#    #+#             */
/*   Updated: 2021/04/23 20:35:43 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int     free_three(t_vec *first, t_vec *second, t_vec *third)
{
    free(first);
    free(second);
    free(third);
    return (0);
}

int     free_four(t_vec *first, t_vec *second, t_vec *third, t_vec *fourth)
{
    free(first);
    free(second);
    free(third);
    free(fourth);
    return (0);
}