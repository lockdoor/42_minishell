/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 06:14:42 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/15 10:49:58 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_parser(t_cmd *cmd)
{
	t_exec	*exec;
	t_redir	*redir;
	t_pipe	*pipe;
	int		i;

	if (cmd->type == EXEC)
	{
		i = 0;
		exec = (t_exec *)cmd;
		printf ("Command: ");
		while (exec->argv[i])
			printf ("%s ", exec->argv[i++]);
		printf ("\n");
	}
	if (cmd->type == REDIR)
	{
		redir = (t_redir *)cmd;
		printf ("Redirect: %s, FD: %d\n", redir->file, redir->fd);
		debug_parser (redir->cmd);
	}
	if (cmd->type == PIPE)
	{
		pipe = (t_pipe *)cmd;
		printf ("Found PIPE\n");
		debug_parser (pipe->left);
		debug_parser (pipe->right);
	}
}