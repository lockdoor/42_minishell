/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_non_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:22:02 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/21 10:13:12 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_in_list(char *cmd)
{
	size_t	len;

	if (!cmd)
		return (0);
	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "exit", len)
		|| !ft_strncmp(cmd, "cd", len)
		|| !ft_strncmp(cmd, "export", len)
		|| !ft_strncmp(cmd, "unset", len))
		return (1);
	return (0);
}

int	is_build_in_non_fork(t_cmd *cmd)
{
	t_redir	*redir;
	t_exec	*exec;

	if (!cmd)
		return (0);
	if (cmd->type == REDIR)
	{
		redir = (t_redir *)cmd;
		return (is_build_in_non_fork(redir->cmd));
	}
	else if (cmd->type == EXEC)
	{
		exec = (t_exec *)cmd;
		return (build_in_list(exec->argv[0]));
	}
	return (0);
}

t_cmd	*pre_parse_pipe(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parse_exec(ps, es);
	if (cmd == NULL)
		return (NULL);
	if (peek(ps, es, "|"))
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

t_cmd	*is_non_fork(char *line)
{
	char	*es;
	t_cmd	*cmd;

	es = ft_strchr(line, 0);
	cmd = pre_parse_pipe(&line, es);
	null_terminate(cmd);
	if (is_build_in_non_fork(cmd))
		return (cmd);
	free_cmd(cmd);
	return (NULL);
}