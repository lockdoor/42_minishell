/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_terminate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:25:48 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/15 10:48:13 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void null_exec(t_cmd *cmd)
{
	t_exec	*exec;
	int		i;

	exec = (t_exec *)cmd;
	i = 0;
	while (exec->argv[i])
	{
		*exec->eargv[i] = 0;
		i++ ;
	}
}

static void null_redir(t_cmd *cmd)
{
	t_redir *redir;

	redir = (t_redir *)cmd;
	*redir->efile = 0;
	null_terminate(redir->cmd);
}

static void	null_pipe(t_cmd *cmd)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)cmd;
	null_terminate(pipe->left);
	null_terminate(pipe->right);
}

void	null_terminate(t_cmd *cmd)
{
	if (!cmd)
		return;
	if (cmd->type == EXEC)
		null_exec(cmd);
	if (cmd->type == REDIR)
		null_redir(cmd);
	if (cmd->type == PIPE)
		null_pipe(cmd);  
}
