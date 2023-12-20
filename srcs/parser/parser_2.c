/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:52:55 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/20 16:42:55 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* use this parser in child process only */
t_cmd	*pipecmd(void)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) malloc (sizeof(t_pipe));
	if (!pipe)
	{
		perror ("pipecmd");
		return (NULL);
	}
	ft_memset (pipe, 0, sizeof(pipe));
	pipe->type = PIPE;
	return ((t_cmd *)pipe);
}

t_cmd	*execmd(void)
{
	t_exec	*exec;

	exec = (t_exec *) malloc (sizeof(t_exec));
	if (!exec)
	{
		perror ("execmd");
		return (NULL);
	}
	ft_memset(exec, 0, sizeof(t_exec));
	exec->type = EXEC;
	return ((t_cmd *)exec);
}

t_cmd	*redircmd(t_cmd *cmd, int fd, int mode, char **q)
{
	t_redir	*redir;
	t_redir	*new_redir;

	new_redir = (t_redir *) malloc (sizeof (t_redir));
	if (!new_redir || fd < 0)
	{
		free_cmd (cmd);
		perror ("redircmd");
		return (NULL);
	}
	new_redir->fd = fd;
	new_redir->mode = mode;
	new_redir->type = REDIR;
	new_redir->file = q[0];
	new_redir->efile = q[1];
	if (cmd->type == REDIR)
	{
		redir = (t_redir *)cmd;
		new_redir->cmd = redir->cmd;
		redir->cmd = (t_cmd *) new_redir;
		return (cmd);
	}
	new_redir->cmd = cmd;
	return ((t_cmd *)new_redir);
}
