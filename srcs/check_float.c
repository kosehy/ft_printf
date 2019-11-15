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

/*
** read float number
** @param fpf
** @param args
** @return
*/
long double	read_float(t_fpf *fpf, va_list args)
{
	long double	ld;

	if (fpf->flags & TYPE_CL)
		ld = va_arg(args, long double);
	else
		ld = (long double)va_arg(args, double);
	return (ld);
}

/*
** need to make one more function to reduce 25 lines
** @param fpf
** @param right
** @param prec
** @return
*/
char		*reduce_for_float(t_fpf *fpf, int64_t right, int prec)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = fpf->flags & FLOAT_PLUS ? prec + 1 : prec;
	if (right == 0 && prec && !(fpf->flags & FLOAT_PLUS))
	{
		if (!(tmp = ft_strnew(prec)))
			return (NULL);
		while (prec-- > 0)
			tmp[i++] = '0';
	}
	else
	{
		if (!(tmp = ft_strnew(j)))
			return (NULL);
		while (j-- > 0)
		{
			tmp[j] = right % 10 + '0';
			right /= 10;
		}
	}
	return (tmp);
}

/*
** minus_float
** @param fpf
** @param right
** @param left
** @param sign
** @return
*/
int			minus_float(t_fpf *fpf, char *right, char *left, int sign)
{
	int		count;
	int		i;

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
	i = (fpf->flags & FLOAT_PLUS) ? 1 : 0;
	count += put_digit(fpf, &right[i]);
	count += width_digit(fpf, fpf->width - count);
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
	int		i;

	count = 0;
	count += ((fpf->flags & FLAGS_SPACE) && !(fpf->flags & FLAGS_PLUS)) \
		? flag_space_digit(sign) : 0;
	count += (fpf->flags & FLAGS_PLUS) ? flag_plus_digit(sign) : 0;
	width_len = fpf->width - count - ft_strlen(left) - ft_strlen(right);
	width =  width_len + (fpf->flags & FLOAT_PLUS ? 1 : 0) - ((fpf->flags & \
		PRECISION && fpf->precision) ? 1 : 0) - (!(fpf->flags & PRECISION) \
		? 1 : 0) - (sign ? 1 : 0);
	count += width_digit(fpf, width);
	count += minus_digit(sign);
	count += put_digit(fpf, left);
	if ((fpf->flags & PRECISION && fpf->precision) || \
		!(fpf->flags & PRECISION) || fpf->flags & FLAGS_HASH)
	{
		count += 1;
		ft_putchar('.');
	}
	i = (fpf->flags & FLOAT_PLUS) ? 1 : 0;
	count += put_digit(fpf, &right[i]);
	return (count);
}

/*
** floating number rounding
** @param fpf
** @param right
** @return
*/
char		*rounding_off(t_fpf *fpf, long double right)
{
	int64_t round;
	int		prec;
	int		tmp;
	char	*temp;

	prec = (fpf->flags & PRECISION) ? fpf->precision : 6;
	tmp = prec + 1;
	while (tmp > 0)
	{
		--tmp;
		right = right * 10;
	}
	right += 5;
	round = (int64_t)right / 10;
	round = round > 0 ? round : -round;
	if (round != 0 && get_int64_len(round) == prec + 1)
		fpf->flags |= FLOAT_PLUS;
	if (!(temp = reduce_for_float(fpf, round, prec)))
		return (NULL);
	return (temp);
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
	fpf->flags |= right ? FLOAT_EXIST : 0;
	sign = right >= 0 ? 0 : 1;
	left = (int64_t)right;
	right = (right - left) > 0 ? right - left : left - right;
	left = left >= 0 ? left : -left;
	if (!(right_p = rounding_off(fpf, right)))
		return (0);
	left += (fpf->flags & FLOAT_PLUS) ? 1 : 0;
	if (!(left_p = ft_int64_itoa_base(left, 10)))
		return (0);
	if (fpf->flags & FLAGS_MINUS)
		left = (int64_t)minus_float(fpf, right_p, left_p, sign);
	else
		left = (int64_t)normal_float(fpf, right_p, left_p, sign);
	free(left_p);
	free(right_p);
	return ((int)left);
}
