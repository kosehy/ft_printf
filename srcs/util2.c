/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:04:16 by sko               #+#    #+#             */
/*   Updated: 2019/11/15 14:04:18 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** flag space digit
** @param sign
** @return
*/

int				flag_space_digit(int sign)
{
	if (!sign)
		ft_putchar(' ');
	return (ATO(sign));
}

/*
** flag plus digit
** @param sign
** @return
*/

int				flag_plus_digit(int sign)
{
	if (!sign)
		ft_putchar('+');
	return (ATO(sign));
}

/*
** check string precision
** @param fpf
** @param str
** @return count
*/

int				precision_string(t_fpf *fpf, char *str)
{
	int		count;
	int		i;

	count = 0;
	i = fpf->precision;
	while (i != 0)
	{
		--i;
		ft_putchar(str[count++]);
	}
	return (count);
}

/*
** change lower case character to upper case character in string
** @param str
** @return
*/

char			*upper_case(char *str)
{
	char	*temp;
	int		len;

	len = ft_strlen(str);
	if (!(temp = ft_strnew(len + 1)))
		return (NULL);
	len = 0;
	while (str[len])
	{
		if (ft_isalpha(str[len]))
			temp[len] = str[len] - ('a' - 'A');
		else
			temp[len] = str[len];
		++len;
	}
	free(str);
	return (temp);
}

/*
** for_zero_octal_hexa
** @param fpf
** @param temp
** @param base
** @return
*/

int				for_zero_oct_hex(t_fpf *fpf, char *temp, int64_t base)
{
	int		count;

	count = 0;
	if ((count = TO(fpf->flags & FLAGS_HASH && base == 8)))
		ft_putchar('0');
	free(temp);
	return (count);
}
