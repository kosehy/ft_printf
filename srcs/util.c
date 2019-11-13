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


/*
** get widh numbers
** @param str
** @param fpf
** @return
*/

const char	*get_numbers(const char *str, t_fpf *fpf)
{
	int	nbr;

	nbr = 0;
	while (is_digit(str))
	{
		fpf->flags |= WIDTH;
		nbr = nbr * 10 + (*str - '0');
		++str;
	}
	if (nbr > fpf->width)
		fpf->width = nbr;
	return (str);
}

/*
** read the precision value from str
** managed minimum filed width (*)
** @param str
** @param fpf
** @return
*/

void		get_prec_numbers(t_fpf *fpf, int nbr)
{
	if (!(fpf->flags & PRECISION_ZERO))
	{
		if (fpf->precision != 0)
		{
			if (fpf->precision > nbr)
				fpf->precision = nbr;
			else
				fpf->precision = fpf->precision;
		}
		else
			fpf->precision = nbr;
	}
}