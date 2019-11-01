/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 18:57:09 by sko               #+#    #+#             */
/*   Updated: 2019/10/17 22:32:50 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>

# define FLAGS_NONE			(1 << 0)
# define FLAGS_MINUS		(1 << 1)
# define FLAGS_SPACE		(1 << 2)
# define FLAGS_PLUS			(1 << 3)
# define FLAGS_HASH			(1 << 4)
# define FLAGS_ZERO			(1 << 5)
# define WIDTH				(1 << 5)
# define PRECISION			(1 << 6)
# define TYPE_H				(1 << 7)
# define TYPE_HH			(1 << 8)
# define TYPE_Z				(1 << 9)
# define TYPE_L				(1 << 10)
# define TYPE_LL			(1 << 11)
# define TYPE_LLL			(1 << 12)
# define TYPE_J				(1 << 13)
# define NUMBER_PRECISION	(1 << 14)
# define PRECISION_ZERO		(1 << 15)
# define IGNORE_PRECISION	(1 << 16)
# define OX_ZERO			(1 << 17)
# define F_EXIST			(1 << 18)

/*
** dispatch table structure
*/

typedef struct	s_dispatch_t
{
	char	specifier;
	int		(*ft)();
}				t_dpt;

typedef struct	s_fpf
{
	int		flags;
	int		length;
	int		width;
	int		width_p;
	int		precision;
	int		prec_p;
	char	specifier;
}				t_fpf;

const char		*read_content(const char *str, t_fpf *fpf);
int				check_character(t_fpf *fpf, va_list args);

/*
** check_info.c
*/

const char		*ft_check_info(const char *str, t_fpf *fpf);

/*
** ft_printf.c
*/

int				check_flags(const char *str);
int				check_modifier(const char *str);
const char		*get_numbers(const char *str, t_fpf *fpf);
void			get_prec_numbers_reduce_two(t_fpf *fpf, int nbr);
const char		*get_prec_number_reduce_one(const char *str, t_fpf *fpf);

/*
** specifier.c
*/

int				ft_select_specifier(const char *str, t_fpf *fpf, va_list args);

/*
** util.c
*/

void			init_fpf(t_fpf *fpf);
int				is_digit(const char *str);

/*
** check_letter.c
*/

int				check_string(t_fpf *fpf, va_list args);

#endif
