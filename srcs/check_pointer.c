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

/*
** put '0x' flag
** @param i
** @return
*/

int			put_flag(int i)
{
	if (i > 0)
	{
		ft_putchar('0');
		ft_putchar('x');
	}
	return (2);
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
	prec = (fpf->flags & IGNORE_PRECISION ? 0 : fpf->precision) - len;
	count += prec > 0 ? prec : 0;
	while (prec-- > 0)
		ft_putchar('0');
	count += put_digit(fpf, str);
	count += ((fpf->width - count) > 0) ? \
			width_digit(fpf, fpf->width - count) : 0;
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

	count = 0;
	temp = fpf->flags & IGNORE_PRECISION ? 0 : fpf->precision;
	width = fpf->width - (len > temp ? len : fpf->precision);
	width -= 2;
	count += width_digit(fpf, width);
	count += put_flag(1);
	prec = (fpf->flags & IGNORE_PRECISION ? 0 : fpf->precision) - len;
	count += prec > 0 ? prec : 0;
	while (prec-- > 0)
		ft_putchar('0');
	count += put_digit(fpf, str);
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
	if (fpf->flags & FLAGS_MINUS)
		count = minus_pointer(fpf, tmp, len);
	else
		count = normal_pointer(fpf, tmp, len);
	free(tmp);
	return (count);
}
