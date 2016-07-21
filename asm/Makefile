# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/11 18:14:04 by tvisenti          #+#    #+#              #
#    Updated: 2016/07/21 19:00:00 by tvisenti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = asm

SRC_PATH = ./src
LIB_PATH = ./lib
INC_PATH = ./inc
OBJ_PATH = ./obj
OBJLIB_PATH = ./obj

SRC_NAME =	asm_main.c\
			asm_parsing.c\
			asm_binary_writer.c\
			asm_check_arg.c\
			asm_check_instruction.c\
			asm_check_label.c\
			asm_parse_instruct.c\
			asm_write_octal.c\
			asm_writer.c\

LIB_NAME =	asm_init.c\
			asm_error.c\
			asm_free.c\

INC_NAME =	asm.h\

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJLIB_NAME = $(LIB_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
OBJLIB = $(addprefix $(OBJLIB_PATH)/,$(OBJLIB_NAME))

all: $(NAME)

$(NAME): $(OBJ) $(OBJLIB)
	@make -C ../libft
	@echo '#####                         (33%)'
	@sleep 1
	@echo '#############                 (66%)'
	@sleep 1
	@echo '#######################       (100%)'
	@$(CC) $(FLAGS) -o $@ $^ ../libft/libft.a ../libft/ft_printf/libftprintf.a
	@echo "\033[1;34mASM\t\t\033[1;33mCompilation\t\033[0;32m-OK-\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(FLAGS) -o $@ -c $<

$(OBJLIB_PATH)/%.o: $(LIB_PATH)/%.c
	@mkdir $(OBJLIB_PATH) 2> /dev/null || true
	@$(CC) $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ) $(OBJLIB)
	@echo "\033[1;34mASM\t\t\033[1;33mCleaning obj\t\033[0;32m-OK-\033[0m"

fclean: clean
	@rm -rf ./obj $(NAME)
	@echo "\033[1;34mASM\t\t\033[1;33mCleaning lib\t\033[0;32m-OK-\033[0m"
	@cd ../libft && $(MAKE) fclean

re: fclean all
