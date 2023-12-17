# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 15:48:31 by pnamnil           #+#    #+#              #
#    Updated: 2023/12/16 09:17:37 by pnamnil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB_PATH = libft
SRC_DIR = srcs
BUILD_DIR = bin
INCLUDES = -Ilibft/includes -I$(SRC_DIR)
LIBFT = -lft -L$(LIB_PATH) 

CC = cc
CFLAGS = -Wall -Werror -Wextra
# CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

SRCS = main.c \
		debug.c \
		gettoken.c \
		parser.c \
		null_terminate.c \
		free.c \
		runcmd.c \
		ft_execute.c \
		ft_get_env.c \
		debug_parser_2.c \
		# ft_free.c \
		# ft_get_env.c \
		# lexer/lexer.c \
		# lexer/is_token.c \
		# parser/ft_parser.c \
		# parser/ft_parse_var.c \
		# validate/ft_validate.c \
		# validate/ft_validate_helper.c \
		# build_in/ft_env.c

HEADERS = minishell.h

all: $(NAME)
# ./$(NAME)

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

l:
	leaks --atExit -- ./$(NAME)

v:
# valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)
	valgrind --leak-check=full ./$(NAME)

$(NAME): make_libft $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

make_libft:
	$(MAKE) -C $(LIB_PATH);

clean:
	rm -rf bin

fclean: clean
	rm -f $(NAME)

re: fclean all
