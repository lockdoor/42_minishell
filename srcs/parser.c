/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 08:08:40 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/15 09:55:16 by pnamnil          ###   ########.fr       */
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

t_cmd	*redircmd(t_cmd *cmd, int fd, int mode, char **q)
{
	t_redir	*redir;
	t_redir *new_redir;

	new_redir = (t_redir *) malloc (sizeof (t_redir));
	if (!new_redir)
	{
		free_cmd (cmd);
		perror ("redircmd");
		return (NULL);
	}
	new_redir->fd = fd;
	new_redir->mode = mode;
	new_redir->type = REDIR;
	new_redir->file = q[0];
	new_redir->efile = q[1];
	if (cmd->type == REDIR)
	{
		redir = (t_redir *)cmd;
		new_redir->cmd = redir->cmd;
		redir->cmd = (t_cmd *) new_redir;
		return ((t_cmd *)redir);
	}
	new_redir->cmd = cmd;
	return ((t_cmd *)new_redir);
}

t_cmd	*parse_redir(t_cmd *cmd, char **ps, char *es)
{
	int		token;
	char	*q[2];

	
	while (peek (ps, es, "<>"))
	{
		token = gettoken(ps, es, NULL, NULL);
		if (gettoken(ps, es, &q[0], &q[1]) != 'a')
			return token_error (cmd, FILE_NAME_NOT_FOUND);
		if (token == '<')
			cmd = redircmd(cmd, 0, O_RDONLY, q);
		else if (token == '>')
			cmd = redircmd(cmd, 1, O_WRONLY|O_CREAT|O_TRUNC, q);
		else if (token == '+')
			cmd = redircmd(cmd, 1, O_WRONLY|O_CREAT, q);
		// else
		// handle heredoc here

		if (!cmd)
			return (NULL);
	}
	return (cmd);
}
