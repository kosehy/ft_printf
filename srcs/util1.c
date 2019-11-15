/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:04:11 by sko               #+#    #+#             */
/*   Updated: 2019/11/15 14:04:12 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** check string precision
** @param fpf
** @param str
** @return count
*/

int				precision_string(t_fpf *fpf, char *str)
{
	int		count;
	int		i;

	count = 0;
	i = fpf->precision;
	while (i != 0)
	{
		ft_putchar(str[count++]);
		--i;
	}
	return (count);
}

