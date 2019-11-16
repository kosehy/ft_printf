/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:14:56 by sko               #+#    #+#             */
/*   Updated: 2019/11/14 18:14:57 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_nf_count(t_fpf *fpf, int width, char *r, char *l, int sign)
{
	int		pre_flag;
	int		count;
	int		index;

	count = 0;
	pre_flag = fpf->flags & PRECISION;
	count += width_digit(fpf, width);
	count += minus_digit(sign);
	count += put_digit(fpf, l);
	if ((pre_flag && fpf->precision) || !pre_flag || fpf->flags & FLAGS_HASH)
	{
		count += 1;
		ft_putchar('.');
	}

	index = TO(fpf->flags & FLOAT_PLUS);
	count += put_digit(fpf, &r[index]);
	return (count);
}

/*
** normal float need to reduce line?
** @param fpf
** @param right
** @param left
** @param sign
** @return
*/

int			normal_float(t_fpf *fpf, char *right, char *left, int sign)
{
	int		count;
	int		width;
	int		width_len;
	int		pre_flag;

	pre_flag = fpf->flags & PRECISION;
	count = 0;
	count += ((fpf->flags & FLAGS_SPACE) && !(fpf->flags & FLAGS_PLUS)) \
		? flag_space_digit(sign) : 0;
	count += (fpf->flags & FLAGS_PLUS) ? flag_plus_digit(sign) : 0;
	width_len = fpf->width - count - ft_strlen(left) - ft_strlen(right);
	width =  width_len + TO(fpf->flags & FLOAT_PLUS) - \
			TO(pre_flag && fpf->precision) - TO(!pre_flag) - TO(sign);
	count += check_nf_count(fpf, width, right, left, sign);
	return (count);
}

long double	check_right(long double right, int64_t left)
{
	if ((right - left) > 0)
		right = right - left;
	else
		right = left - right;
	return (right);
}

int64_t		check_left(t_fpf *fpf, int64_t left, char *rp, char *lp, int sign)
{
	if (fpf->flags & FLAGS_MINUS)
		left = (int64_t)minus_float(fpf, rp, lp, sign);
	else
		left = (int64_t)normal_float(fpf, rp, lp, sign);
	return (left);
}

/*
** check_float
** @param fpf
** @param args
** @return
*/
int			check_float(t_fpf *fpf, va_list args)
{
	int64_t		left;
	int			sign;
	long double	right;
	char		*left_p;
	char		*right_p;

	right = read_float(fpf, args);
	if (right)
		fpf->flags |= FLOAT_EXIST;
	sign = ATO(right >= 0);
	left = (int64_t)right;
	right = check_right(right, left);
	if (left < 0)
		left = -left;
	if (!(right_p = rounding_off(fpf, right)))
		return (0);
	left += TO(fpf->flags & FLOAT_PLUS);
	if (!(left_p = ft_int64_itoa_base(left, 10)))
		return (0);
	left = check_left(fpf, left, right_p, left_p, sign);
	free(left_p);
	free(right_p);
	return ((int)left);
}
