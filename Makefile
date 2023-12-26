# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 15:48:31 by pnamnil           #+#    #+#              #
#    Updated: 2023/12/26 08:40:19 by pnamnil          ###   ########.fr        #
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
		debug/debug.c \
		free.c \
		ft_get_env.c \
		set_last_cmd.c \
		debug/debug_parser_2.c \
		parser/gettoken.c \
		parser/parser_1.c \
		parser/parser_2.c \
		parser/parser_3.c \
		parser/null_terminate.c \
		parser/is_non_fork.c \
		execute/runcmd.c \
		execute/run_pipe.c \
		execute/run_redir.c \
		execute/ft_execute.c \
		execute/ft_parse_cmd.c \
		execute/ft_parser.c \
		execute/ft_parse_var.c \
		execute/is_non_fork.c \
		execute/utils.c \
		build_in/echo.c \
		build_in/exit.c \
		build_in/env.c \
		build_in/unset.c \
		build_in/pwd.c \
		build_in/export.c \
		build_in/set_export.c 
		
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
# valgrind --leak-check=full --track-origins=yes ./$(NAME)
	valgrind --leak-check=full ./$(NAME)

$(NAME): make_libft $(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS)  -o $(NAME)

make_libft:
	$(MAKE) -C $(LIB_PATH);

clean:
	rm -rf bin

fclean: clean
	rm -f $(NAME)

re: fclean all
