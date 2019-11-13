/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 21:32:28 by sko               #+#    #+#             */
/*   Updated: 2019/11/08 21:32:39 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#import "ft_printf.h"

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

char		*ft_int64_itoa_base(int64_t value, int64_t base)
{
	int64_t		n;
	int			i;
	char		*out;
	char		*hex_digit;

	n = ((base == 10 && value < 0) ? -value : value);
	i = base_len(value, base);
	out = malloc(sizeof(char) * (i + 1));
	hex_digit = "0123456789ABCDEF";
	out[i] = '\0';
	if (value < 0 && base == 10)
		out[0] = '-';
	if (value == 0)
		out[0] = '0';
	n = ((base == 10 && value < 0) ? -value : value);
	while ( n != 0)
	{
		--i;
		out[i] = hex_digit[n % base];
		n /= base;
	}
	return (out);
}

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
	hex_digit = "0123456789ABCDEF";
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
