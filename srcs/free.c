/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:39:13 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/15 06:51:01 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_redir	*redir;
	t_pipe	*pipe;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
		free (cmd);
	if (cmd->type == REDIR)
	{
		redir = (t_redir *)cmd;
		free_cmd((t_cmd *)redir->cmd);
		free (cmd);
	}
	if (cmd->type == PIPE)
	{
		pipe = (t_pipe *)cmd;
		free_cmd(pipe->left);
		free_cmd(pipe->right);
		free (cmd);
	}
}
