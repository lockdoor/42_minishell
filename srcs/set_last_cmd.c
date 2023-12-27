/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_last_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 08:34:13 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/27 06:37:12 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_last_command(char *argv, t_shell *sh)
{
	char	*last;

	last = ft_strjoin("_=", argv);
	if (!last)
	{
		perror ("set_last_cmd");
		return ;
	}
	set_export(last, sh);
	free (last);
}

void	set_last_cmd(t_cmd *cmd, t_shell *sh)
{
	t_redir	*redir;
	t_exec	*exec;

	if (!cmd)
		return ;
	if (cmd->type == PIPE)
	{
		set_last_command ("", sh);
		return ;
	}
	if (cmd->type == REDIR)
	{
		redir = (t_redir *)cmd;
		set_last_cmd(redir->cmd, sh);
	}
	else if (cmd->type == EXEC)
	{
		exec = (t_exec *)cmd;
		set_last_command (exec->argv[0], sh);
	}
}
