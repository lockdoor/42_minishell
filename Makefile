# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 15:48:31 by pnamnil           #+#    #+#              #
#    Updated: 2024/01/03 07:12:58 by pnamnil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB_PATH = libft
SRC_DIR = srcs
BUILD_DIR = bin

# for machine school
LREAD_DIR = /usr/local/opt/readline
INCLUDES =	-I$(SRC_DIR) \
			-I$(LIB_PATH)/includes \
			-I$(LREAD_DIR)/include
LIBS =	-lreadline -L$(LREAD_DIR)/lib  \
		-lft -L$(LIB_PATH)

# for mac m1
# INCLUDES = -Ilibft/includes -I$(SRC_DIR)
# LIBS = -lft -L$(LIB_PATH) -lreadline

CC = cc
CFLAGS = -Wall -Werror -Wextra
# CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

SRCS = main.c \
		init_shell.c \
		free.c \
		ft_get_env.c \
		set_last_cmd.c \
		debug/debug.c \
		debug/debug_parser.c \
		parser/gettoken.c \
		parser/parser_1.c \
		parser/parser_2.c \
		parser/parser_3.c \
		parser/null_terminate.c \
		parser/is_non_fork.c \
		parser/parse_here.c \
		parser/parse_here_helper.c \
		execute/runcmd.c \
		execute/run_pipe.c \
		execute/run_redir.c \
		execute/ft_execute.c \
		execute/ft_parse_cmd.c \
		execute/ft_parser.c \
		execute/ft_parse_var.c \
		execute/is_non_fork.c \
		execute/utils.c \
		execute/make_env.c \
		build_in/echo.c \
		build_in/exit.c \
		build_in/env.c \
		build_in/unset.c \
		build_in/pwd.c \
		build_in/export.c \
		build_in/set_export.c \
		build_in/cd.c 
		
HEADERS = srcs/minishell.h

all: $(NAME)
# ./$(NAME)

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

l:
	leaks --atExit -- ./$(NAME)

v:
# valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)
# valgrind --leak-check=full --track-origins=yes ./$(NAME)
	valgrind --leak-check=full ./$(NAME)

$(NAME): $(OBJS) $(HEADERS)
	$(MAKE) -C $(LIB_PATH);
	$(CC) $(CFLAGS) $(OBJS) $(LIBS)  -o $(NAME)

clean:
	rm -rf bin

fclean: clean
	rm -f $(NAME)

norminette:
	@norminette -R CheckForbiddenSourceHeader $(LIB_PATH)/*.c
	@norminette -R CheckDefine $(LIB_PATH)/includes/libft.h
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*
	@norminette -R CheckDefine $(SRC_DIR)/minishell.h

re: fclean all
