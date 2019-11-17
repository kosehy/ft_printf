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

int64_t		check_red_f_right(int64_t right, int j, char *tmp)
{
	while (j > 0)
	{
		--j;
		tmp[j] = right % 10 + '0';
		right /= 10;
	}
	return (right);
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
	if (fpf->flags & FLOAT_PLUS)
		j = prec + 1;
	else
		j = prec;
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
		right = check_red_f_right(right, j, tmp);
	}
	return (tmp);
}

char		*check_round(t_fpf *fpf, char *temp, long double right, int prec)
{
	int64_t round;

	round = (int64_t)right / 10;
	if (round <= 0)
		round = -round;
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

char		*rounding_off(t_fpf *fpf, long double right)
{
	int		prec;
	int		tmp;
	char	*temp;

	if (fpf->flags & PRECISION)
		prec = fpf->precision;
	else
		prec = 6;
	tmp = prec + 1;
	while (tmp > 0)
	{
		--tmp;
		right = right * 10;
	}
	right += 5;
	temp = NULL;
	temp = check_round(fpf, temp, right, prec);
	return (temp);
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
