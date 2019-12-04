/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:30:49 by sko               #+#    #+#             */
/*   Updated: 2019/10/24 11:31:04 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** check width condition
** @param width
** @param c
** @param count
** @return
*/

int			check_width_condition(int width, char c, int count)
{
	while (width > 0)
	{
		--width;
		ft_putchar(c);
		++count;
	}
	return (count);
}

/*
** get width number
** @param fpf
** @param width
** @return count
*/

int			width_digit(t_fpf *fpf, int width)
{
	int		count;
	int		minus_flag;
	int		zero_flag;

	count = 0;
	minus_flag = fpf->flags & FLAGS_MINUS;
	zero_flag = fpf->flags & FLAGS_ZERO;
	if (!minus_flag && zero_flag)
		count = check_width_condition(width, '0', count);
	else
		count = check_width_condition(width, ' ', count);
	return (count);
}

/*
** initialize fpf values
** @param fpf
*/

void		init_fpf(t_fpf *fpf)
{
	fpf->flags = 0;
	fpf->width = 0;
	fpf->width_p = 0;
	fpf->precision = 0;
	fpf->prec_p = 0;
}

/*
** check string contains digit number from 0 to 9
** @param str
** @return 1 if contains digit number or 0 if not
*/

int			is_digit(const char *str)
{
	if (*str >= '0' && *str <= '9')
		return (1);
	return (0);
}

/*
** get length of int64_t
** @param nbr
** @return
*/

int			get_int64_len(int64_t nbr)
{
	int	len;

	len = 1;
	while (nbr != 0)
	{
		nbr /= 10;
		if (nbr == 0)
			break ;
		++len;
	}
	return (len);
}
