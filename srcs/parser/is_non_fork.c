/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_non_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:22:02 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/25 09:56:05 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_in_list(char *cmd)
{
	size_t	len;

	if (!cmd)
		return (0);
	// len = ft_strlen(cmd);
	len = -1;
	
	// if (len == 0)
	// 	return (0);
	return (!ft_strncmp(cmd, "exit", len)
		|| !ft_strncmp(cmd, "cd", len)
		|| !ft_strncmp(cmd, "export", len)
		|| !ft_strncmp(cmd, "unset", len));
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

		/* this point can handle last command */
		
		exec = (t_exec *)cmd;
		return (build_in_list(exec->argv[0]));
	}
	return (0);
}
