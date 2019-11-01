# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sko <marvin@42.fr>                         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 15:17:33 by sko               #+#    #+#              #
#    Updated: 2019/10/30 15:17:37 by sko              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC_PATH = srcs/
SRCS = *.c

SRC = $(addprefix $(SRC_PATH), $(SRCS))

FT = libft/
LIBFT = libft.a
HEAD = ./includes
OBJ = *.o
FLAG = -Wextra -Werror -Wall
DEL = rm -rf

all: $(NAME)

$(NAME):
	@make -C $(FT)
	@gcc $(FLAG) -o $(NAME) $(SRC) -I $(HEAD) -I $(FT) -L. $(FT)$(LIBFT)
	@echo "[======================]"
	@echo "|     success !        |"
	@echo "|     libftprintf.a    |"
	@echo "|     was summoned     |"
	@echo "[======================]"

clean:
	@$(DEL) $(OBJ)
	@make -C $(FT) clean
	@echo "[=================]"
	@echo "|     succes !    |"
	@echo "|     XXXXX.o     |"
	@echo "|  was destroyed  |"
	@echo "[=================]"

fclean:	clean
	@$(DEL) $(NAME)
	@make -C $(FT) fclean
	@echo "[======================]"
	@echo "|     succes !         |"
	@echo "|     libftprintf.a    |"
	@echo "|    was destroyed     |"
	@echo "[======================]"

re: fclean all

debug:
	gcc -g -o $(NAME) $(SRC) -I $(HEAD)
