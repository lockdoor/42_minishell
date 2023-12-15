/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 08:08:40 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/15 08:49:19 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_pipe(char **ps, char *es);
t_cmd	*parse_redir(t_cmd *cmd, char **ps, char *es);
t_cmd	*parse_exec(char **ps, char *es);
t_cmd	*token_error(t_cmd *cmd, char *s);

t_cmd	*token_error(t_cmd *cmd, char *s)
{
	ft_putendl_fd (s, 2);
	free_cmd (cmd);
	return (NULL);
}

t_cmd	*parser(char *ps)
{
	t_cmd	*cmd;
	char	*es;

	es = ft_strchr(ps, 0);
	peek(&ps, es, "");
	if (*ps == 0)
		return (NULL);
	cmd = parse_pipe(&ps, es);
	// cmd = parse_exec(&ps, es);
	return (cmd);
}

t_cmd	*pipecmd(void)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) malloc (sizeof(t_pipe));
	if (!pipe)
	{
		perror ("pipecmd");
		return (NULL);
	}
	ft_memset (pipe, 0, sizeof(pipe));
	pipe->type = PIPE;
	return ((t_cmd *)pipe);
}

t_cmd	*parse_pipe(char **ps, char *es)
{
	t_cmd	*cmd;
	t_pipe	*pipe;

	cmd = parse_exec(ps, es);
	if (cmd == NULL)
		return (NULL);
	if (peek(ps, es, "|"))
	{
		gettoken (ps, es, NULL, NULL);
		pipe = (t_pipe *) pipecmd ();
		if (pipe == NULL)
		{
			free_cmd (cmd);
			return (NULL);
		}
		pipe->left = cmd;
		pipe->right = parse_pipe(ps, es);
		if (!pipe->right)
		{
			free_cmd ((t_cmd *)pipe);
			return (NULL);
		}
		cmd = (t_cmd *) pipe;
	}
	return (cmd);
}

t_cmd	*execmd(void)
{
	t_exec	*exec;

	exec = (t_exec *) malloc (sizeof(t_exec));
	if (!exec)
	{
		perror ("execmd");
		return (NULL);
	}
	ft_memset(exec, 0, sizeof(t_exec));
	exec->type = EXEC;
	return ((t_cmd *)exec);
}

t_cmd	*parse_exec(char **ps, char *es)
{
	t_exec	*exec;
	t_cmd	*ret;
	int		token;
	char	*q;
	char	*eq;
	int		argv;

	ret = execmd();
	if (!ret)
		return (NULL);
	peek(ps, es, "");
	if (**ps == 0)
		return (token_error(ret, COMMAND_NOT_FOUND));
	exec = (t_exec *) ret;
	ret = parse_redir(ret, ps, es);
	if (!ret)
		return (NULL);
	argv = 0;
	while (peek(ps, es, "|") == 0)
	{
		token = gettoken(ps, es, &q, &eq);
		if (token == 0)
			break ;
		if (token != 'a')
			return (token_error(ret, COMMAND_NOT_FOUND));
		exec->argv[argv] = q;
		exec->eargv[argv] = eq;
		argv++ ;
		ret = parse_redir(ret, ps, es);
		if (!ret)
			return (NULL);
	}
	exec->argv[argv] = 0;
	exec->eargv[argv] = 0;
	return (ret);
}

t_cmd	*redircmd(t_cmd *cmd, int fd, int mode)
{
	t_redir	*redir;

	redir = (t_redir *) malloc (sizeof (t_redir));
	if (!redir)
	{
		free_cmd (cmd);
		perror ("redircmd");
		return (NULL);
	}
	redir->cmd = cmd;
	redir->fd = fd;
	redir->mode = mode;
	redir->type = REDIR;
	return ((t_cmd *)redir);
}

t_cmd	*parse_redir(t_cmd *cmd, char **ps, char *es)
{
	t_redir	*redir;
	int		token;
	char	*q;
	char	*eq;

	
	while (peek (ps, es, "<>"))
	{
		token = gettoken(ps, es, NULL, NULL);
		if (token == '<')
			cmd = redircmd(cmd, 0, O_RDONLY);
		else if (token == '>')
			cmd = redircmd(cmd, 1, O_WRONLY|O_CREAT|O_TRUNC);
		else if (token == '+')
			cmd = redircmd(cmd, 1, O_WRONLY|O_CREAT);
		// else
		// handle heredoc here

		if (!cmd)
		{
			return (NULL);
		}
		redir = (t_redir *) cmd;
		token = gettoken(ps, es, &q, &eq);
		if (token != 'a')
		{
			write (2, FILE_NAME_NOT_FOUND, ft_strlen(FILE_NAME_NOT_FOUND));
			free_cmd (cmd);
			return (NULL);
		}
		redir->file = q;
		redir->efile = eq;
	}
	return (cmd);
}
