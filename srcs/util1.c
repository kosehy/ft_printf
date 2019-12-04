/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:04:11 by sko               #+#    #+#             */
/*   Updated: 2019/11/15 14:04:12 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** find the length of variable based on int64_t type
** @param nbr
** @param base
** @return
*/

int			base_len(int64_t nbr, int64_t base)
{
	int			len;

	len = 0;
	while (nbr != 0)
	{
		nbr /= base;
		++len;
	}
	return (len);
}

/*
** find the length of variable based on uint64_t type
** @param nbr
** @param base
** @return
*/

int			u_base_len(uint64_t nbr, uint64_t base)
{
	int			len;

	len = 0;
	while (nbr != 0)
	{
		nbr /= base;
		++len;
	}
	return (len);
}

/*
** put digit (need to modify FLOAT_EXIST and function)
** @param fpf
** @param str
** @return
*/

int			put_digit(t_fpf *fpf, char *str)
{
	int		i;

	i = 0;
	if (fpf->flags & OX_ZERO)
	{
		ft_putchar(' ');
		return (1);
	}
	else if (!(fpf->flags & FLOAT_EXIST) && fpf->flags & PRECISION && \
			!fpf->precision && str[0] == '0' && str[1] == '\0')
	{
		if (!fpf->width)
			return (0);
		ft_putchar(' ');
		return (1);
	}
	else
	{
		while (str[i])
		{
			ft_putchar(str[i]);
			++i;
		}
	}
	return (i);
}

/*
** itoa base function based on uint64_t type
** @param value
** @param base
** @return
*/

char		*ft_uint64_itoa_base(uint64_t value, uint64_t base)
{
	uint64_t	n;
	int			i;
	char		*out;
	char		*hex_digit;

	n = value;
	i = 0;
	if (value == 0)
		++i;
	i = u_base_len(value, base);
	out = malloc(sizeof(char) * (i + 1));
	hex_digit = "0123456789abcdef";
	out[i] = '\0';
	if (value == 0)
		out[0] = '0';
	n = value;
	while (n != 0)
	{
		--i;
		out[i] = hex_digit[n % base];
		n /= base;
	}
	return (out);
}

/*
** itoa base function based on int64_t type
** @param value
** @param base
** @return
*/

char		*ft_int64_itoa_base(int64_t value, int64_t base)
{
	int64_t		n;
	int			i;
	char		*out;
	char		*hex_digit;

	n = ((base == 10 && value < 0) ? -value : value);
	i = base_len(value, base);
	out = malloc(sizeof(char) * (i + 1));
	hex_digit = "0123456789abcdef";
	out[i] = '\0';
	if (value < 0 && base == 10)
		out[0] = '-';
	if (value == 0)
		out[0] = '0';
	n = ((base == 10 && value < 0) ? -value : value);
	while (n != 0)
	{
		--i;
		out[i] = hex_digit[n % base];
		n /= base;
	}
	return (out);
}
