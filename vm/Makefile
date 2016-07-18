# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderragu <aderragu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/21 17:34:59 by aderragu          #+#    #+#              #
#    Updated: 2015/12/28 11:37:38 by aderragu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

SRC_PATH = ./src/
SRC_NAME = 	cw_main.c\
			cw_param_handler.c\
			cw_champion_creation.c\
			cw_manage_list.c\

OBJ = $(SRC_NAME:.c=.o)

LIB_PATH = ../libft/
LIB_NAME =

INC_PATH_L = $(LIB_PATH)
INC_PATH_P = $(LIB_PATH)ft_printf/include/

NAME = corewar

CC = gcc
FLAGS =

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
LIB = $(addprefix $(LIB_PATH),$(LIB_NAME))

$(NAME): $(SRC)
	@make -C $(LIB_PATH)
	@$(CC) $(SRC) -o $(NAME) -I ./inc/ -I $(LIB_PATH) -I $(INC_PATH_P) $(LIB_PATH)libft.a $(LIB_PATH)ft_printf/libftprintf.a
	@echo "Compilation success"

all: $(NAME)

clean:
	@make clean -C $(LIB_PATH)
	@rm -rf $(OBJ)
	@echo "Delete .o"

fclean: clean
	@make fclean -C $(LIB_PATH)
	@rm -rf $(NAME)
	@echo "Delete Corewar"

re: fclean all
