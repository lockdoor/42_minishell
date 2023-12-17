/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:01:30 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/17 12:15:29 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	non_fork(t_cmd *cmd)
{
	t_redir	*redir;
	t_exec	*exec;
	if (cmd->type == PIPE)
		return (0);
	else if (cmd->type == REDIR)
	{
		redir = (t_cmd *)cmd;
		return (non_fork (redir->cmd));
	}
	else if (cmd->type == EXEC)
	{
		exec = (t_exec *)cmd;
		return (is_build_in(exec->argv[0]));
	}
	return (0);
}