/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 00:03:30 by sko               #+#    #+#             */
/*   Updated: 2019/11/17 00:03:45 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_nor_oh_width(t_fpf *fpf, int len, int64_t digit)
{
	int		width;
	int		tmp;

	if (fpf->flags & IGNORE_PRECISION)
		tmp = 0;
	else
		tmp = fpf->precision;
	if (len > tmp)
		width = fpf->width - len;
	else
		width = fpf->width - fpf->precision;
	if (fpf->flags & FLAGS_HASH && digit != 0)
	{
		if (fpf->flags & EIGHT)
			width -= 1;
		else
			width -= 2;
	}
	return (width);
}

/*
** normal_octal ,normal_hexa
** @param fpf
** @param str
** @param digit
** @return
*/

int			normal_oct_hex(t_fpf *fpf, char *str, int64_t digit)
{
	int		len;
	int		count;
	int		width;
	int		prec;

	count = 0;
	width = 0;
	len = ft_strlen(str);
	width = check_nor_oh_width(fpf, len, digit);
	count += for_normal_oct_hex(fpf, digit, width);
	if (fpf->flags & IGNORE_PRECISION)
		prec = 0;
	else
		prec = fpf->precision - len;
	prec -= TO(fpf->flags & FLAGS_HASH && fpf->flags & EIGHT);
	if (prec > 0)
		count += prec;
	while (prec > 0)
	{
		--prec;
		ft_putchar('0');
	}
	count += put_digit(fpf, str);
	return (count);
}

/*
** check precision value of minus pointer
** @param prec
** @param count
** @return
*/

int			check_mi_p_prec(int prec, int count)
{
	if (prec > 0)
		count += prec;
	while (prec > 0)
	{
		--prec;
		ft_putchar('0');
	}
	return (count);
}

/*
** read float number
** @param fpf
** @param args
** @return
*/

long double	read_float(t_fpf *fpf, va_list args)
{
	long double	ld;

	if (fpf->flags & TYPE_CL)
		ld = va_arg(args, long double);
	else
		ld = (long double)va_arg(args, double);
	return (ld);
}

/*
** minus unsigned decimal int inteager
** @param fpf
** @param str
** @return
*/

int			minus_udi(t_fpf *fpf, char *str)
{
	int		prec;
	int		count;
	int		len;

	len = ft_strlen(str);
	count = 0;
	if (fpf->flags & IGNORE_PRECISION)
		prec = -len;
	else
		prec = fpf->precision - len;
	if (prec > 0)
		count += prec;
	while (prec > 0)
	{
		--prec;
		ft_putchar('0');
	}
	count += put_digit(fpf, str);
	if ((fpf->width - count) > 0)
		count += width_digit(fpf, fpf->width - count);
	return (count);
}
