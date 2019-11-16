/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:11:13 by sko               #+#    #+#             */
/*   Updated: 2019/11/01 16:11:16 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define TO(X) ((X) ? 1 : 0)
#define ATO(X) ((X) ? 0 : 1)

/*
** find the length of variable based on int64_t type
** @param nbr
** @param base
** @return
*/

int			base_len(int64_t nbr, int64_t base)
{
	int			len;

	len = 0;
	while (nbr != 0)
	{
		nbr /= base;
		++len;
	}
	return (len);
}

/*
** itoa base function based on int64_t type
** @param value
** @param base
** @return
*/

char		*ft_int64_itoa_base(int64_t value, int64_t base)
{
	int64_t		n;
	int			i;
	char		*out;
	char		*hex_digit;

	n = ((base == 10 && value < 0) ? -value : value);
	i = base_len(value, base);
	out = malloc(sizeof(char) * (i + 1));
	hex_digit = "0123456789abcdef";
	out[i] = '\0';
	if (value < 0 && base == 10)
		out[0] = '-';
	if (value == 0)
		out[0] = '0';
	n = ((base == 10 && value < 0) ? -value : value);
	while ( n != 0)
	{
		--i;
		out[i] = hex_digit[n % base];
		n /= base;
	}
	return (out);
}

/*
** find the length of variable based on uint64_t type
** @param nbr
** @param base
** @return
*/

int			u_base_len(uint64_t nbr, uint64_t base)
{
	int			len;

	len = 0;
	while (nbr != 0)
	{
		nbr /= base;
		++len;
	}
	return (len);
}

/*
** itoa base function based on uint64_t type
** @param value
** @param base
** @return
*/

char		*ft_uint64_itoa_base(uint64_t value, uint64_t base)
{
	uint64_t	n;
	int			i;
	char		*out;
	char		*hex_digit;

	n = value;
	i = 0;
	if (value == 0)
		++i;
	i = u_base_len(value, base);
	out = malloc(sizeof(char) * (i + 1));
	hex_digit = "0123456789abcdef";
	out[i] = '\0';
	if (value == 0)
		out[0] = '0';
	n = value;
	while (n != 0)
	{
		--i;
		out[i] = hex_digit[n % base];
		n /= base;
	}
	return (out);
}

/*
** flag space digit
** @param sign
** @return
*/

int			flag_space_digit(int sign)
{
	if (!sign)
		ft_putchar(' ');
	return (ATO(sign));
}

/*
** flag plus digit
** @param sign
** @return
*/

int			flag_plus_digit(int sign)
{
	if (!sign)
		ft_putchar('+');
	return (ATO(sign));
}

/*
** put minuse character
** @param sign
** @return
*/

int			minus_digit(int sign)
{
	if (sign)
	{
		ft_putchar('-');
		return (1);
	}
	return (0);
}

/*
** need to change style
** @param fpf
** @param temp
** @param len
** @param sign
** @return
*/

int			flag_minus_digit(t_fpf *fpf, char *temp, int len, int sign)
{
	int		count;
	int		prec;
	int		plus_flag;
	int		space_flag;

	space_flag = fpf->flags & FLAGS_SPACE;
	plus_flag = fpf->flags & FLAGS_PLUS;
	count = minus_digit(sign);
	count += ((space_flag) && !plus_flag) ? flag_space_digit(sign) : 0;
	count += plus_flag ? flag_plus_digit(sign) : 0;
	prec = (fpf->flags & IGNORE_PRECISION ? 0 : fpf->precision) - len;
	count += prec > 0 ? prec : 0;
	while (prec > 0)
	{
		ft_putchar('0');
		--prec;
	}
	count += put_digit(fpf, temp);
	count += ((fpf->width - count) > 0) ? \
			width_digit(fpf, fpf->width - count) : 0;
	return (count);
}

/*
** need to change code style
** @param fpf
** @param width
** @param sign
** @return
*/

int			flagcase_digit(t_fpf *fpf, int width, int sign)
{
	int		count;
	int		space_flag;
	int		plus_flag;

	space_flag = fpf->flags & FLAGS_SPACE;
	plus_flag = fpf->flags & FLAGS_PLUS;
	count = 0;
	if (fpf->flags & FLAGS_ZERO)
	{
		count += minus_digit(sign);
		count += space_flag && !plus_flag ? flag_space_digit(sign) : 0;
		count += plus_flag ? flag_plus_digit(sign) : 0;
		count += width_digit(fpf, width);
	}
	else
	{
		count += space_flag && !plus_flag ? flag_space_digit(sign) : 0;
		count += width_digit(fpf, width);
		count += plus_flag ? flag_plus_digit(sign) : 0;
		count += minus_digit(sign);
	}
	return (count);
}

/*
**
** @param fpf
** @param temp
** @param len
** @param sign
** @return
*/

int			normal_digit(t_fpf *fpf, char *temp, int len, int si)
{
	int		count;
	int		width;
	int		prec;
	int		tm;

	count = 0;
	if (!(fpf->flags & IGNORE_PRECISION) && (fpf->flags& PRECISION) && \
		fpf->precision == 0 && temp[0] == '0' && temp[1] == '\0')
		len = 0;
	tm = fpf->flags & IGNORE_PRECISION ? 0 : fpf->precision;
	width = fpf->width - (len > tm ? len : fpf->precision);
	width -= TO(si);
	width -= TO(!si && fpf->flags & FLAGS_SPACE && !(fpf->flags & FLAGS_PLUS));
	width -= TO((fpf->flags & FLAGS_PLUS) && !si);
	count += flagcase_digit(fpf, width, si);
	prec = (fpf->flags & IGNORE_PRECISION ? 0 : fpf->precision) - len;
	count += prec > 0 ? prec : 0;
	while (prec > 0)
	{
		ft_putchar('0');
		--prec;
	}
	count += (len ? put_digit(fpf, temp) : 0);
	return (count);
}

/*
** int64_t
** @param fpf
** @param args
** @return
*/

int 		check_integer(t_fpf *fpf, va_list args)
{
	int64_t		digit;
	int			len;
	int			count;
	int			sign;
	char		*str;

	digit = signed_modifier(fpf, args);
	sign = TO(digit < 0);
	if ((fpf->flags & PRECISION) && !(fpf->flags & IGNORE_PRECISION))
		fpf->flags = fpf->flags & ~FLAGS_ZERO;
	if (!(str = (digit < 0 ? ft_uint64_itoa_base(-(uint64_t)digit, 10) : \
		ft_int64_itoa_base(digit, 10))))
		return (0);
	len = get_int64_len(digit);
	count = fpf->flags & FLAGS_MINUS ? flag_minus_digit(fpf, str, len, sign) \
			: normal_digit(fpf, str, len, sign);
	free(str);
	return (count);
}
