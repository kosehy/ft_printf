/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 10:30:14 by sko               #+#    #+#             */
/*   Updated: 2019/11/16 10:30:16 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				check_mf_count(t_fpf *fpf, int sign, char *left)
{
	int		count;

	count = minus_digit(sign);
	count += ((fpf->flags & FLAGS_SPACE) && !(fpf->flags & FLAGS_PLUS)) \
			? flag_space_digit(sign) : 0;
	count += (fpf->flags & FLAGS_PLUS) ? flag_plus_digit(sign) : 0;
	count += put_digit(fpf, left);
	if (fpf->precision)
	{
		count += 1;
		ft_putchar('.');
	}
	return (count);
}

/*
** minus_float
** @param fpf
** @param right
** @param left
** @param sign
** @return
*/

int				minus_float(t_fpf *fpf, char *right, char *left, int sign)
{
	int		count;
	int		index;

	count = check_mf_count(fpf, sign, left);
	index = TO(fpf->flags & FLOAT_PLUS);
	count += put_digit(fpf, &right[index]);
	count += width_digit(fpf, fpf->width - count);
	return (count);
}

int				check_nor_di_width(t_fpf *fpf, int tm, int len, int si)
{
	int		width;
	int		ig_prec_flag;

	ig_prec_flag = fpf->flags & IGNORE_PRECISION;
	if (ig_prec_flag)
		tm = 0;
	else
		tm = fpf->precision;
	if (len > tm)
		width = fpf->width - len;
	else
		width = fpf->width - fpf->precision;
	width -= TO(si);
	width -= TO(!si && fpf->flags & FLAGS_SPACE && !(fpf->flags & FLAGS_PLUS));
	width -= TO((fpf->flags & FLAGS_PLUS) && !si);
	return (width);
}

int				check_nor_di_prec(t_fpf *fpf, int len)
{
	int		prec;
	int		ig_prec_flag;

	ig_prec_flag = fpf->flags & IGNORE_PRECISION;
	if (ig_prec_flag)
		prec = -len;
	else
		prec = fpf->precision - len;
	return (prec);
}

/*
** check normal digit
** @param fpf
** @param temp
** @param len
** @param sign
** @return
*/

int				normal_digit(t_fpf *fpf, char *temp, int len, int si)
{
	int		count;
	int		width;
	int		prec;
	int		tm;
	int		ig_prec_flag;

	ig_prec_flag = fpf->flags & IGNORE_PRECISION;
	count = 0;
	if (!ig_prec_flag && (fpf->flags & PRECISION) && fpf->precision == 0 \
		&& temp[0] == '0' && temp[1] == '\0')
		len = 0;
	tm = 0;
	width = check_nor_di_width(fpf, tm, len, si);
	count += flagcase_digit(fpf, width, si);
	prec = check_nor_di_prec(fpf, len);
	if (prec > 0)
		count += prec;
	while (prec > 0)
	{
		ft_putchar('0');
		--prec;
	}
	if (len)
		count += put_digit(fpf, temp);
	return (count);
}
