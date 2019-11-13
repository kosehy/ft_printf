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

int			flag_space_digit(int sign)
{
	if (!sign)
		ft_putchar(' ');
	return (sign ? 0 : 1);
}

int			flag_plus_digit(int sign)
{
	if (!sign)
		ft_putchar('+');
	return (sign ? 0 : 1);
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

	count = minus_digit(sign);
	count += ((fpf->flags & FLAGS_SPACE) && !(fpf->flags & FLAGS_PLUS)) \
		? flag_space_digit(sign) : 0;
	count += (fpf->flags & FLAGS_PLUS) ? flag_plus_digit(sign) : 0;
	prec = (fpf->flags & IGNORE_PRECISION ? 0 : fpf->precision) - len;
	count += prec > 0 ? prec : 0;
	while (prec > 0)
	{
		ft_putchar('0');
		--prec;
	}
	count += put_digit(fpf, temp);
	count += ((fpf->width - count) > 0) ? width_digit(fpf, fpf->width - count) : 0;
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

	count = 0;
	if (fpf->flags & FLAGS_ZERO)
	{
		count += minus_digit(sign);
		count += ((fpf->flags & FLAGS_SPACE) && !(fpf->flags & FLAGS_PLUS)) \
			? flag_space_digit(sign) : 0;
		count += (fpf->flags & FLAGS_PLUS) ? flag_plus_digit(sign) : 0;
		count += width_digit(fpf, width);
	}
	else
	{
		count += ((fpf->flags & FLAGS_SPACE) && !(fpf->flags & FLAGS_PLUS)) \
			? flag_space_digit(sign) : 0;
		count += width_digit(fpf, width);
		count += (fpf->flags & FLAGS_PLUS) ? flag_plus_digit(sign) : 0;
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
int			normal_digit(t_fpf *fpf, char *temp, int len, int sign)
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
	width -= sign ? 1: 0;
	width -= (!sign && fpf->flags & FLAGS_SPACE && \
			!(fpf->flags & FLAGS_PLUS)) ? 1 : 0;
	width -= ((fpf->flags & FLAGS_PLUS) && !sign) ? 1 : 0;
	count += flagcase_digit(fpf, width, sign);
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
	sign = digit < 0 ? 1 : 0;
	if ((fpf->flags & PRECISION) && !(fpf->flags & IGNORE_PRECISION))
		fpf->flags = fpf->flags & ~FLAGS_ZERO;
	if (!(str = (digit < 0 ? ft_uint64_itoa_base(-(uint64_t)digit, 10) : \
		ft_int64_itoa_base(digit, 10))))
		return (0);
	len = get_int64_len(digit);
	if (fpf->flags & FLAGS_MINUS)
		count = flag_minus_digit(fpf, str, len, sign);
	else
		count = normal_digit(fpf, str, len, sign);
	free(str);
	return (count);
}
