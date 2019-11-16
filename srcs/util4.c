/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 23:14:05 by sko               #+#    #+#             */
/*   Updated: 2019/11/15 23:14:07 by sko              ###   ########.fr       */
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

char			*check_round(t_fpf *fpf, char *temp, int64_t round, int prec)
{
	if (round != 0 && get_int64_len(round) == prec + 1)
		fpf->flags |= FLOAT_PLUS;
	if (!(temp = reduce_for_float(fpf, round, prec)))
		return (NULL);
	return (temp);
}

/*
** floating number rounding
** @param fpf
** @param right
** @return
*/

char			*rounding_off(t_fpf *fpf, long double right)
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
	if (round <= 0)
		round = -round;
	temp = NULL;
	temp = check_round(fpf, temp, round, prec);
	return (temp);
}
