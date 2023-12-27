/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 08:08:40 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/27 11:24:01 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* use this parser in child process only */

t_cmd	*parse_pipe(char **ps, char *es);
t_cmd	*parse_redir(t_cmd *cmd, char **ps, char *es);
t_cmd	*parse_exec(char **ps, char *es);
int		is_no_cmd(t_cmd *cmd, char	*s);

t_cmd	*parser(char *ps)
{
	t_cmd	*cmd;
	char	*es;
	t_exec	*exec;

	es = ft_strchr(ps, 0);
	while (*ps && ft_strchr(WHITESPACE, *ps))
		ps++ ;
	if (*ps == 0)
		return (NULL);
	cmd = parse_pipe(&ps, es);
	if (!cmd)
		return (NULL);
	if (cmd->type == EXEC)
	{
		exec = (t_exec *)cmd;
		if (exec->argv[0] == NULL)
			return (token_error(cmd, NULL));
	}
	null_terminate (cmd);
	return (cmd);
}

t_cmd	*parse_pipe(char **ps, char *es)
{
	t_cmd	*cmd;
	t_pipe	*pipe;

	cmd = parse_exec(ps, es);
	if (is_no_cmd(cmd, TOKEN_ERROR))
		return (NULL);
	if (peek(ps, es, "|"))
	{
		gettoken (ps, es, NULL, NULL);
		peek(ps, es, "");
		if (**ps == 0)
			return (token_error(cmd, TOKEN_ERROR));
		pipe = (t_pipe *) pipecmd ();
		if (pipe == NULL)
			return (token_error(cmd, NULL));
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

t_cmd	*parse_exec_2(t_exec *exec, t_cmd *ret, char **ps, char *es)
{
	int		token;
	int		argv;
	char	*q;
	char	*eq;

	argv = 0;
	while (**ps && peek(ps, es, "|") == 0)
	{
		token = gettoken(ps, es, &q, &eq);
		if (token == 0)
			break ;
		if (token == -1)
			return (token_error(ret, NULL));
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

t_cmd	*parse_exec(char **ps, char *es)
{
	t_exec	*exec;
	t_cmd	*ret;

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
	return (parse_exec_2(exec, ret, ps, es));
}

t_cmd	*parse_redir(t_cmd *cmd, char **ps, char *es)
{
	int		token;
	int		file_token;
	char	*q[2];

	while (peek (ps, es, "<>"))
	{
		token = gettoken(ps, es, NULL, NULL);
		file_token = gettoken(ps, es, &q[0], &q[1]);
		if (file_token == -1)
			return (token_error (cmd, NULL));
		if (file_token != 'a')
			return (token_error (cmd, FILE_NAME_NOT_FOUND));
		if (token == '<')
			cmd = redircmd(cmd, 0, token, q);
		else if (token == '>')
			cmd = redircmd(cmd, 1, token, q);
		else if (token == '+')
			cmd = redircmd(cmd, 1, token, q);
		else if (token == 'h')
			cmd = redircmd(cmd, 0, token, q);
	}
	return (cmd);
}
