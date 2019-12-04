# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sko <marvin@42.fr>                         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 15:17:33 by sko               #+#    #+#              #
#    Updated: 2019/11/01 11:52:24 by sko              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

DIRHDER = ./includes/
DIRLIB = ./libft/
DIRSRC = ./srcs/

INCLUDE = -I $(DIRHDER)
COMPILE = -c $(DIRLIB)*.c $(DIRSRC)*.c
FLAG = -Wall -Wextra -Werror


all: $(NAME)

$(NAME):
	gcc $(COMPILE) $(INCLUDE) $(FLAG)
	ar rcs $(NAME) *.o

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
