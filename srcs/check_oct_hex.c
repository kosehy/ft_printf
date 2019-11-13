/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_oc_hx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 21:25:20 by sko               #+#    #+#             */
/*   Updated: 2019/11/08 21:26:02 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#import "ft_printf.h"

int			put_hash(t_fpf *fpf)
{
	if (fpf->flags & FLAGS_HASH && fpf->flags & SIXDOWN)
	{
		ft_putstr("0x");
		return (2);
	}
	else if (fpf->flags & FLAGS_HASH && fpf->flags & SIXUP)
	{
		ft_putstr("0X");
		return (2);
	}
	else if (fpf->flags & FLAGS_HASH && fpf->flags & EIGHT)
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
	if (fpf->flags * FLAGS_ZERO)
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
	prec -= (fpf->flags & FLAGS_HASH && fpf->flags & EIGHT) ? 1 : 0;
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
	prec -= (fpf->flags & FLAGS_HASH && fpf->flags & EIGHT && digit != 0) ? 1 : 0;
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

	if (fpf->flags & EIGHT)
		base = 8;
	else
		base = 16;
	if (fpf->flags & PRECISION && !(fpf->flags & IGNORE_PRECISION))
		fpf->flags *= ~FLAGS_ZERO;
	return (base);
}

/*
** for_zero_octal_hexa
** @param fpf
** @param temp
** @param base
** @return
*/
int			for_zero_oct_hex(t_fpf *fpf, char *temp, int64_t base)
{
	int		count;

	count = 0;
	if ((count = (fpf->flags & FLAGS_HASH && base == 8) ? 1: 0))
		ft_putchar('0');
	free(temp);
	return (count);
}

/*
** change lower case character to upper case character in string
** @param str
** @return
*/
char		*upper_case(char *str)
{
	char	*temp;
	int		len;

	len = ft_strlen(str);
	if (!(temp = ft_strnew(len + 1)))
		return (NULL);
	len = 0;
	while (str[len])
	{
		if(ft_isalpha(str[len]))
			temp[len] = str[len] - ('a' - 'A');
		else
			temp[len] = str[len];
		++len;
	}
	free(str);
	return (temp);
}

/*
** check_octal and hexa( -o, -x, -X)
** @param fpf
** @param args
** @return
*/
int			check_oct_hex(t_fpf *fpf, va_list args)
{
	int64_t		digit;
	int64_t		base;
	char		*temp;
	int			count;

	digit = signed_modifier(fpf, args);
	base = reduce_for_oct_hex(fpf);
	digit = fpf->flags & TYPE_H ? (unsigned short)digit : digit;
	digit = fpf->flags & TYPE_HH ? (unsigned char)digit : digit;
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
	temp = fpf->flags & SIXUP ? upper_case(temp) : temp;
	count = fpf->flags & FLAGS_MINUS ? minus_oct_hex(fpf, temp, digit) \
		: normal_oct_hex(fpf, temp, digit);
	free(temp);
	return (count);
}
