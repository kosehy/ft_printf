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

int			check_fl_mi_di_prec(t_fpf *fpf, int len, int count)
{
	int		prec;

	if (fpf->flags & IGNORE_PRECISION)
		prec = -len;
	else
		prec = fpf->precision - len;
	if (prec > 0)
		count += prec;
	while (prec > 0)
	{
		ft_putchar('0');
		--prec;
	}
	return (count);
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
	int		plus_flag;
	int		space_flag;

	space_flag = fpf->flags & FLAGS_SPACE;
	plus_flag = fpf->flags & FLAGS_PLUS;
	count = minus_digit(sign);
	if ((space_flag) && !plus_flag)
		count += flag_space_digit(sign);
	if (plus_flag)
		count += flag_plus_digit(sign);
	count = check_fl_mi_di_prec(fpf, len, count);
	count += put_digit(fpf, temp);
	if ((fpf->width - count) > 0)
		count += width_digit(fpf, fpf->width - count);
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

int			check_int_count(t_fpf *fpf, int64_t digit, char *str, int sign)
{
	int		len;
	int		count;

	len = get_int64_len(digit);
	if (fpf->flags & FLAGS_MINUS)
		count = flag_minus_digit(fpf, str, len, sign);
	else
		count = normal_digit(fpf, str, len, sign);
	free(str);
	return (count);
}

/*
** int64_t
** @param fpf
** @param args
** @return
*/

int			check_integer(t_fpf *fpf, va_list args)
{
	int64_t		digit;
	int			count;
	int			sign;
	char		*str;

	digit = signed_modifier(fpf, args);
	sign = TO(digit < 0);
	if ((fpf->flags & PRECISION) && !(fpf->flags & IGNORE_PRECISION))
		fpf->flags = fpf->flags & ~FLAGS_ZERO;
	if (digit < 0)
		str = ft_uint64_itoa_base(-(uint64_t)digit, 10);
	else
		str = ft_int64_itoa_base(digit, 10);
	if (!str)
		return (0);
	count = check_int_count(fpf, digit, str, sign);
	return (count);
}
