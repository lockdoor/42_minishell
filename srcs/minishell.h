/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:33:24 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/15 08:21:50 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SYMBOLS "|<>"
# define WHITESPACE " \n\t\v\r"
# define EXEC  1
# define REDIR 2
# define PIPE  3
# define MAXARGS 10

// error
# define FILE_NAME_NOT_FOUND "file name not found"
# define COMMAND_NOT_FOUND "command not found"

typedef struct s_cmd
{
	int type;
}	t_cmd;

typedef struct s_exec
{
	int		type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
}	t_exec;

typedef struct s_redir
{
    int		type;
	t_cmd	*cmd;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
}	t_redir;

typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

// debug.c
int		showtoken(char	*line);
void	parsecmd(char *s);
void	debug_parser(t_cmd *cmd);

// gettoken.c
int	gettoken(char **ps, char *es, char **q, char **eq);
int	peek(char **ps, char *es, char *tok);

// parser.c
t_cmd	*parser(char *ps);

// free.c
void	free_cmd(t_cmd *cmd);

#endif