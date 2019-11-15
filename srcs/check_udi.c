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

/*
** minus unsigned decimal int inteager
** @param fpf
** @param str
** @return
*/
int			minus_udi(t_fpf *fpf, char *str)
{
	int		prec;
	int		count;
	int		len;

	len = ft_strlen(str);
	count = 0;
	prec = (fpf->flags & IGNORE_PRECISION ? 0 : fpf->precision) - len;
	count += prec > 0 ? prec : 0;
	while (prec > 0)
	{
		--prec;
		ft_putchar('0');
	}
	count += put_digit(fpf, str);
	count += ((fpf->width - count) > 0) ? width_digit(fpf, fpf->width - count) : 0;
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
	int		prec;
	int		tmp;
	int		len;

	len = ft_strlen(str);
	count = 0;
	tmp = fpf->flags & IGNORE_PRECISION ? 0 : fpf->precision;
	width = fpf->width - (len > tmp ? len : fpf->precision);
	count += width_digit(fpf, width);
	prec = (fpf->flags & IGNORE_PRECISION ? 0 : fpf->precision) - len;
	count += prec > 0 ? prec : 0;
	while (prec > 0)
	{
		--prec;
		ft_putchar('0');
	}
	count += put_digit(fpf, str);
	return (count);
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

	digit = signed_modifier(fpf, args);
	digit = (!(fpf->flags & UNLONG) && !(fpf->flags & TYPE_L) && \
		fpf->flags & TYPE_H) ? (unsigned short)digit : digit;
	digit = (!(fpf->flags & UNLONG) && (fpf->flags & TYPE_L) && \
		fpf->flags & TYPE_HH) ? (unsigned char)digit : digit;
	if (fpf->flags & UNLONG || fpf->flags & TYPE_L || fpf->flags \
		& TYPE_LL || fpf->flags & TYPE_J)
	{
		if (!(tmp = ft_uint64_itoa_base((uint64_t)digit, 10)))
			return (0);
	}
	else if (!(tmp = digit < 0 ? ft_uint64_itoa_base((unsigned)digit, 10) : \
		ft_int64_itoa_base(digit, 10)))
		return (0);
	if (fpf->flags & PRECISION && !(fpf->flags & IGNORE_PRECISION))
		fpf->flags &= ~FLAGS_ZERO;
	count = fpf->flags & FLAGS_MINUS ? minus_udi(fpf, tmp) \
		: normal_udi(fpf, tmp);
	free(tmp);
	return (count);
}