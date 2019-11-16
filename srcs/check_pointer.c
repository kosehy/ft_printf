/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:04:57 by sko               #+#    #+#             */
/*   Updated: 2019/11/14 17:05:00 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_prec(int prec, int count)
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
** control minus pointer
** @param fpf
** @param str
** @param len
** @return
*/

int			minus_pointer(t_fpf *fpf, char *str, int len)
{
	int		count;
	int		prec;

	count = 0;
	count += put_flag(1);
	if (fpf->flags & IGNORE_PRECISION)
		prec = -len;
	else
		prec = fpf->precision - len;
	count = check_prec(prec, count);
	count += put_digit(fpf, str);
	if ((fpf->width - count) > 0)
		count += width_digit(fpf, fpf->width - count);
	return (count);
}

/*
** control normal pointer
** @param fpf
** @param str
** @param len
** @return
*/

int			normal_pointer(t_fpf *fpf, char *str, int len)
{
	int		count;
	int		width;
	int		prec;
	int		temp;
	int		ig_prec_flag;

	ig_prec_flag = fpf->flags & IGNORE_PRECISION;
	count = 0;
	if (ig_prec_flag)
		temp = 0;
	else
		temp = fpf->precision;
	if (len > temp)
		width = fpf->width - len;
	else
		width = fpf->width - fpf->precision;
	width -= 2;
	count += width_digit(fpf, width);
	count += put_flag(1);
	prec = (ig_prec_flag ? 0 : fpf->precision) - len;
	count = check_prec(prec, count);
	count += put_digit(fpf, str);
	return (count);
}

int			check_cp(t_fpf *fpf, char *tmp, int len, int count)
{
	if (fpf->flags & FLAGS_MINUS)
		count = minus_pointer(fpf, tmp, len);
	else
		count = normal_pointer(fpf, tmp, len);
	return (count);
}

/*
** check pointer specifier
** @param fpf
** @param args
** @return
*/

int			check_pointer(t_fpf *fpf, va_list args)
{
	int64_t	digit;
	int		count;
	int		len;
	char	*tmp;

	count = 0;
	digit = (int64_t)va_arg(args, void*);
	if (!(tmp = ft_int64_itoa_base(digit, 16)))
		return (0);
	len = ft_strlen(tmp);
	count = check_cp(fpf, tmp, len, count);
	free(tmp);
	return (count);
}
