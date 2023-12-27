/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 06:14:42 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/27 06:50:01 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	debug_parser_pipe(t_cmd *cmd)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)cmd;
	printf ("Found PIPE\n");
	debug_parser (pipe->left);
	debug_parser (pipe->right);
}

/* use this for debug command tree node */
void	debug_parser(t_cmd *cmd)
{
	t_exec	*exec;
	t_redir	*redir;
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
		debug_parser_pipe(cmd);
}
