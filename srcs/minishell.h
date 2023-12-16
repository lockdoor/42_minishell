/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:33:24 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/15 14:28:42 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
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

extern char	**environ;
typedef struct s_env
{
    char    *name;
    char    *value;
}   t_env;
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

// ft_get_env.c
t_list	*ft_get_env(void);
void	ft_free_env(void *data);

// debug.c
int		showtoken(char	*line);
void	parsecmd(char *s);
void	debug_parser(t_cmd *cmd);

// gettoken.c
int	gettoken(char **ps, char *es, char **q, char **eq);
int	peek(char **ps, char *es, char *tok);

// parser.c
t_cmd	*parser(char *ps);
void	null_terminate(t_cmd *cmd);

int	runcmd(t_cmd *cmd, t_list *env);

// free.c
void	free_cmd(t_cmd *cmd);

#endif