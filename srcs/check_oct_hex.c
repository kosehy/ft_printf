/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_oct_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 22:08:40 by sko               #+#    #+#             */
/*   Updated: 2019/11/13 22:08:41 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#import "ft_printf.h"

/*
** minus_octal & hexa
** @param fpf
** @param str
** @param digit
** @return
*/

int			minus_oct_hex(t_fpf *fpf, char *str, int64_t digit)
{
	int		count;
	int		prec;
	int		len;

	count = 0;
	len = ft_strlen(str);
	if (digit != 0)
		count += put_hash(fpf);
	if (fpf->flags & IGNORE_PRECISION)
		prec = -len;
	else
		prec = fpf->precision - len;
	prec -= TO(fpf->flags & FLAGS_HASH && fpf->flags & EIGHT && digit != 0);
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

int64_t		check_oh_digit(t_fpf *fpf, int64_t digit)
{
	digit = fpf->flags & TYPE_H ? (unsigned short)digit : digit;
	digit = fpf->flags & TYPE_HH ? (unsigned char)digit : digit;
	return (digit);
}

int			check_oh_count(t_fpf *fpf, int count, char *temp, int64_t digit)
{
	if (fpf->flags & FLAGS_MINUS)
		count = minus_oct_hex(fpf, temp, digit);
	else
		count = normal_oct_hex(fpf, temp, digit);
	return (count);
}

/*
** check_octal and hexa( -o, -x, -X)
** @param fpf
** @param args
** @return
*/

int			check_oct_hex(t_fpf *fpf, va_list args)
{
	int			count;
	int64_t		digit;
	int64_t		base;
	char		*temp;

	digit = signed_modifier(fpf, args);
	base = reduce_for_oct_hex(fpf);
	digit = check_oh_digit(fpf, digit);
	if (fpf->flags & TYPE_J && digit < 0)
	{
		if (!(temp = ft_uint64_itoa_base((uint64_t)digit, base)))
			return (0);
	}
	else if (!(temp = (digit < 0 ? ft_uint64_itoa_base((unsigned)digit, base) \
		: ft_int64_itoa_base(digit, base))))
		return (0);
	for_reduce_oct_hex(fpf, temp);
	if (fpf->flags & OX_ZERO && !fpf->width)
		return (for_zero_oct_hex(fpf, temp, base));
	if (fpf->flags & SIXUP)
		temp = upper_case(temp);
	count = 0;
	count = check_oh_count(fpf, count, temp, digit);
	free(temp);
	return (count);
}
