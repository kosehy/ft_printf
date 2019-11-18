/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 22:19:51 by sko               #+#    #+#             */
/*   Updated: 2019/11/15 22:19:53 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** for_reduce_oct_hex
** @param fpf
** @param temp
*/

void			for_reduce_oct_hex(t_fpf *fpf, char *temp)
{
	int		pre_flag;

	pre_flag = fpf->flags & PRECISION;
	if (temp[0] == '0' && temp[1] == '\0' && pre_flag && fpf->precision == 0)
		fpf->flags |= OX_ZERO;
}

int64_t			reduce_for_oct_hex(t_fpf *fpf)
{
	int64_t	base;
	int		eight_flag;
	int		prec_flag;
	int		ig_prec_flag;
	int		zero_flag;

	eight_flag = fpf->flags & EIGHT;
	prec_flag = fpf->flags & PRECISION;
	ig_prec_flag = fpf->flags & IGNORE_PRECISION;
	zero_flag = fpf->flags & ~FLAGS_ZERO;
	if (eight_flag)
		base = 8;
	else
		base = 16;
	if (prec_flag && !ig_prec_flag)
		fpf->flags = zero_flag;
	return (base);
}

/*
** put hash 0x or 0 or 0X
** @param fpf
** @return
*/

int				put_hash(t_fpf *fpf)
{
	int		hash_flag;

	hash_flag = fpf->flags & FLAGS_HASH;
	if (hash_flag && fpf->flags & SIXDOWN)
	{
		ft_putchar('0');
		ft_putchar('x');
		return (2);
	}
	else if (hash_flag && fpf->flags & EIGHT)
	{
		ft_putchar('0');
		return (1);
	}
	else if (hash_flag && fpf->flags & SIXUP)
	{
		ft_putchar('0');
		ft_putchar('X');
		return (2);
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

int				for_normal_oct_hex(t_fpf *fpf, int64_t digit, int width)
{
	int		count;

	count = 0;
	if (fpf->flags & FLAGS_ZERO)
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
** put '0x' flag
** @param i
** @return
*/

int				put_flag(int i)
{
	if (i > 0)
	{
		ft_putchar('0');
		ft_putchar('x');
	}
	return (2);
}
