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
		--i;
		ft_putchar(str[count++]);
	}
	return (count);
}

/*
** put digit (need to modify FLOAT_EXIST and function)
** @param fpf
** @param str
** @return
*/

int			put_digit(t_fpf *fpf, char *str)
{
	int		i;

	i = 0;
	if (fpf->flags & OX_ZERO)
	{
		ft_putchar(' ');
		return (1);
	}
	else if (!(fpf->flags & FLOAT_EXIST) && fpf->flags & PRECISION && \
			!fpf->precision && str[0] == '0' && str[1] == '\0')
	{
		if (!fpf->width)
			return (0);
		ft_putchar(' ');
		return (1);
	}
	else
	{
		while (str[i])
		{
			ft_putchar(str[i]);
			++i;
		}
	}
	return (i);
}

