/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 06:14:42 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/15 07:08:34 by pnamnil          ###   ########.fr       */
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
		ft_putstr_fd ("Command: ", 1);
		while (exec->argv[i])
		{
			write (1, exec->argv[i], exec->eargv[i] - exec->argv[i]);
			write (1, " ", 1);
			i++ ;
		}
		write (1, "\n", 1);
	}
	if (cmd->type == REDIR)
	{
		redir = (t_redir *)cmd;
		ft_putstr_fd ("Redirect: ", 1);
		write (1, redir->file, redir->efile - redir->file);
		printf (", FD: %d\n", redir->fd);
		debug_parser (redir->cmd);
	}
	if (cmd->type == PIPE)
	{
		pipe = (t_pipe *)cmd;
		ft_putendl_fd ("Found PIPE", 1);
		debug_parser (pipe->left);
		debug_parser (pipe->right);
	}
}