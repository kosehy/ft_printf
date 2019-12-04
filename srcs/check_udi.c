/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_udi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 22:13:10 by sko               #+#    #+#             */
/*   Updated: 2019/11/14 22:13:12 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_nor_udi_count(t_fpf *fpf, char *str, int width)
{
	int		ig_prec_flag;
	int		count;
	int		prec;

	count = 0;
	ig_prec_flag = fpf->flags & IGNORE_PRECISION;
	count += width_digit(fpf, width);
	if (ig_prec_flag)
		prec = -ft_strlen(str);
	else
		prec = fpf->precision - ft_strlen(str);
	if (prec > 0)
		count += prec;
	while (prec > 0)
	{
		--prec;
		ft_putchar('0');
	}
	count += put_digit(fpf, str);
	return (count);
}

/*
** normal unsigned decimal inteager
** @param fpf
** @param str
** @return
*/

int			normal_udi(t_fpf *fpf, char *str)
{
	int		count;
	int		width;
	int		tmp;
	int		ig_prec_flag;

	ig_prec_flag = fpf->flags & IGNORE_PRECISION;
	if (ig_prec_flag)
		tmp = 0;
	else
		tmp = fpf->precision;
	if ((int)ft_strlen(str) > tmp)
		width = fpf->width - ft_strlen(str);
	else
		width = fpf->width - fpf->precision;
	count = check_nor_udi_count(fpf, str, width);
	return (count);
}

char		*check_udi_temp(int64_t digit)
{
	char	*temp;

	if (digit < 0)
		temp = ft_uint64_itoa_base((unsigned)digit, 10);
	else
		temp = ft_int64_itoa_base(digit, 10);
	return (temp);
}

int64_t		check_udi_digit(t_fpf *fpf, va_list args)
{
	int64_t		digit;
	int			l_flag;
	int			ul_flag;

	l_flag = fpf->flags & TYPE_L;
	ul_flag = fpf->flags & UNLONG;
	digit = signed_modifier(fpf, args);
	if (!ul_flag && !l_flag && fpf->flags & TYPE_H)
		digit = (unsigned short)digit;
	if (!ul_flag && !l_flag && fpf->flags & TYPE_HH)
		digit = (unsigned char)digit;
	return (digit);
}

/*
** need to modify
** @param fpf
** @param args
** @return
*/

int			check_unsigned_dec_int(t_fpf *fpf, va_list args)
{
	int64_t		digit;
	int			count;
	char		*tmp;
	int			minus_flag;

	minus_flag = fpf->flags & FLAGS_MINUS;
	digit = check_udi_digit(fpf, args);
	if (fpf->flags & UNLONG || fpf->flags & TYPE_L || fpf->flags \
		& TYPE_LL || fpf->flags & TYPE_J)
	{
		if (!(tmp = ft_uint64_itoa_base((uint64_t)digit, 10)))
			return (0);
	}
	else if (!(tmp = check_udi_temp(digit)))
		return (0);
	if (fpf->flags & PRECISION && !(fpf->flags & IGNORE_PRECISION))
		fpf->flags &= ~FLAGS_ZERO;
	if (minus_flag)
		count = minus_udi(fpf, tmp);
	else
		count = normal_udi(fpf, tmp);
	free(tmp);
	return (count);
}
