/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_z_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 23:19:35 by sko               #+#    #+#             */
/*   Updated: 2019/11/14 23:19:36 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				check_minus_flag(t_fpf *fpf, int width)
{
	int		count;

	count = 0;
	if (fpf->flags & FLAGS_MINUS)
	{
		ft_putchar('%');
		count += width_digit(fpf, width) + 1;
	}
	else
	{
		count += width_digit(fpf, width) + 1;
		ft_putchar('%');
	}
	return (count);
}

int				check_percent(t_fpf *fpf, va_list args)
{
	int		count;
	int		width;

	width = fpf->width - 1;
	if (!args)
		return (0);
	count = check_minus_flag(fpf, width);
	return (count);
}

int				check_z(t_fpf *fpf, va_list args)
{
	int		count;

	count = 0;
	if (fpf && args)
	{
		ft_putchar('Z');
		++count;
	}
	return (count);
}

int				check_z_percent(t_fpf *fpf, va_list args)
{
	int		count;

	if (fpf->specifier == 'Z')
		count = check_z(fpf, args);
	else
		count = check_percent(fpf, args);
	return (count);
}
