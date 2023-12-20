/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:33:24 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/20 16:20:20 by pnamnil          ###   ########.fr       */
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
	int		mode; // '<', '>', '+', 'h'
	int		fd; //for heredoc
}	t_redir;

typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

typedef struct s_shell
{
	t_cmd		*cmd;
	t_list		*env;
	u_int8_t	exit_code;
}	t_shell;

// ft_get_env.c
t_list	*ft_get_env(void);


// debug.c
int		showtoken(char	*line);
void	parsecmd(char *s);
void	debug_parser(t_cmd *cmd);

// gettoken.c
int	gettoken(char **ps, char *es, char **q, char **eq);
int	peek(char **ps, char *es, char *tok);

// parser.c
t_cmd	*parser(char *ps);
t_cmd	*token_error(t_cmd *cmd, char *s);
void	null_terminate(t_cmd *cmd);

t_cmd	*pipecmd(void);
t_cmd	*execmd(void);
t_cmd	*redircmd(t_cmd *cmd, int fd, int mode, char **q);

// t_cmd	*redircmd_heredoc(t_cmd *cmd, int mode, char **q);
int		fd_heredoc(char **q);

// runcmd.c
void	runcmd(t_cmd *cmd, t_shell *sh);
void	run_pipe(t_cmd *cmd, t_shell *sh);
int		fork_1(char	*s, t_shell *sh);
void	run_redir(t_cmd *cmd, t_shell *sh);
int		is_build_in(char *str);
char	**ft_parser(char **argv, t_shell *sh);
char	*parse_qoute(char **str, t_shell *sh);
char	*parse_var(char **str, t_shell *sh);
char	*parse_db_qoute(char **str, t_shell *sh);
char	*get_word(char **str, t_shell *sh);
char	*parse_token(char *s, t_shell *sh);
char	*join_free(char *s1, char *s2);
char	*get_env(char *name, t_shell *sh);

// exec_command.c
void	ft_execute(char **argvs, t_shell *sh);
char	*ft_parse_cmd(char	*cmd, t_list *env);

// build_in
int	echo(char **argv);

// free.c
void	free_cmd(t_cmd *cmd);
void	free_env(void *data);
void	free_shell(t_shell *sh);
void	free_split(char **sp);

#endif