/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_non_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:22:02 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/27 09:33:45 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_in_list(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strncmp(cmd, "exit", -1)
		|| !ft_strncmp(cmd, "cd", -1)
		|| !ft_strncmp(cmd, "export", -1)
		|| !ft_strncmp(cmd, "unset", -1));
}

int	is_build_in_non_fork(t_cmd *cmd, t_shell *sh)
{
	t_redir	*redir;
	t_exec	*exec;

	if (!cmd)
		return (0);
	if (cmd->type == PIPE)
		return (0);
	if (cmd->type == REDIR)
	{
		redir = (t_redir *)cmd;
		return (is_build_in_non_fork(redir->cmd, sh));
	}
	else if (cmd->type == EXEC)
	{
		exec = (t_exec *)cmd;
		return (build_in_list(exec->argv[0]));
	}
	return (0);
}
