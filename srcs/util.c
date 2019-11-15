/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:30:49 by sko               #+#    #+#             */
/*   Updated: 2019/10/24 11:31:04 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


/*
** get width number
** @param fpf
** @param width
** @return count
*/

int			width_digit(t_fpf *fpf, int width)
{
	int		count;

	count = 0;
	if (!(fpf->flags & FLAGS_MINUS) && fpf->flags & FLAGS_ZERO)
	{
		while (width-- > 0)
		{
			ft_putchar('0');
			++count;
		}
	}
	else
	{
		while (width-- > 0)
		{
			ft_putchar(' ');
			++count;
		}
	}
	return (count);
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
** initialize fpf values
** @param fpf
*/

void		init_fpf(t_fpf *fpf)
{
	fpf->flags = 0;
	fpf->width = 0;
	fpf->width_p = 0;
	fpf->precision = 0;
	fpf->prec_p = 0;
}

/*
** check string contains digit number from 0 to 9
** @param str
** @return 1 if contains digit number or 0 if not
*/

int			is_digit(const char *str)
{
	if (*str >= '0' && *str <= '9')
		return (1);
	return (0);
}
/*
** get length of number
** @param nbr
** @return
*/

int			get_len(int nbr)
{
	int	len = 0;

	if (nbr <= 0)
		++len;
	while (nbr != 0)
	{
		++len;
		nbr /= 10;
	}
	return (len);
}

/*
** get length of int64_t
** @param nbr
** @return
*/

int			get_int64_len(int64_t nbr)
{
	int	len = 1;

	while (nbr != 0)
	{
		nbr /= 10;
		if (nbr == 0)
			break ;
		++len;
	}
	return (len);
}
