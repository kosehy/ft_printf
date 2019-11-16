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
