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
**  
** @param fpf
** @return
*/

int			put_hash(t_fpf *fpf)
{
	int		hash_flag;

	hash_flag = fpf->flags & FLAGS_HASH;
	if (hash_flag && fpf->flags & SIXDOWN)
	{
		ft_putchar('0');
		ft_putchar('x');
		return (2);
	}
	else if (hash_flag && fpf->flags & SIXUP)
	{
		ft_putchar('0');
		ft_putchar('X');
		return (2);
	}
	else if (hash_flag && fpf->flags & EIGHT)
	{
		ft_putchar('0');
		return (1);
	}
	return (0);
}

/*
** for_normal_octal_hexa
** @param fpf
** @param digit
** @param width
** @return
*/

int			for_normal_oct_hex(t_fpf *fpf, int64_t digit, int width)
{
	int		count;

	count = 0;
	if (fpf->flags & FLAGS_ZERO)
	{
		count += digit != 0 ? put_hash(fpf) : 0;
		count += width_digit(fpf, width);
	}
	else
	{
		count += width_digit(fpf, width);
		count += digit != 0 ? put_hash(fpf) : 0;
	}
	return (count);
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
	int		count;
	int		width;
	int		prec;
	int		temp;
	int		len;

	count = 0;
	len = ft_strlen(str);
	temp = fpf->flags & IGNORE_PRECISION ? 0 : fpf->precision;
	width = fpf->width - (len > temp ? len : fpf->precision);
	if (fpf->flags & FLAGS_HASH && digit != 0)
		width -= fpf->flags & EIGHT ? 1 : 2;
	count += for_normal_oct_hex(fpf, digit, width);
	prec = (fpf->flags & IGNORE_PRECISION ? 0 : fpf->precision) - len;
	prec -= TO(fpf->flags & FLAGS_HASH && fpf->flags & EIGHT);
	count += prec > 0 ? prec : 0;
	while (prec-- > 0)
		ft_putchar ('0');
	count += put_digit(fpf, str);
	return (count);
}

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
	prec = (fpf->flags & IGNORE_PRECISION ? 0 : fpf->precision) - len;
	prec -= TO(fpf->flags & FLAGS_HASH && fpf->flags & EIGHT && digit != 0);
	count += prec > 0 ? prec : 0;
	while (prec-- > 0)
		ft_putchar('0');
	count += put_digit(fpf, str);
	count += ((fpf->width - count) > 0) ? width_digit(fpf, fpf->width - count) : 0;
	return (count);
}

/*
** for_reduce_oct_hex
** @param fpf
** @param temp
*/

void		for_reduce_oct_hex(t_fpf *fpf, char *temp)
{
	if (temp[0] == '0' && temp[1] == '\0' && fpf->flags & PRECISION \
	&& fpf->precision == 0)
		fpf->flags |= OX_ZERO;
}

int64_t		reduce_for_oct_hex(t_fpf *fpf)
{
	int64_t	base;
	int		eight_flag;
	int		prec_flag;
	int		ig_prec_flag;
	int		zero_flag;

	eight_flag = fpf->flags & EIGHT;
	prec_flag = fpf->flags & PRECISION;
	ig_prec_flag = fpf->flags & IGNORE_PRECISION;
	zero_flag = fpf->flags & ~FLAGS_ZERO;
	if (eight_flag)
		base = 8;
	else
		base = 16;
	if (prec_flag && !ig_prec_flag)
		fpf->flags = zero_flag;
	return (base);
}

int64_t		digit_preprocess(t_fpf *fpf, int64_t digit)
{

	digit = fpf->flags & TYPE_H ? (unsigned short)digit : digit;
	digit = fpf->flags & TYPE_HH ? (unsigned char)digit : digit;
	return (digit);
}

int		count_post_process(t_fpf *fpf, int count, char *temp, int64_t digit)
{
	if (fpf->flags & FLAGS_MINUS)
		count =  minus_oct_hex(fpf, temp, digit);
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
	digit = digit_preprocess(fpf, digit);
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
	count = count_post_process(fpf, count, temp, digit);
	free(temp);
	return (count);
}

