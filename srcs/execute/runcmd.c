/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:09:49 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/18 14:23:18 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_build_in(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	return (!ft_strncmp(str, "echo", len)
		|| !ft_strncmp(str, "cd", len)
		|| !ft_strncmp(str, "pwd", len)
		|| !ft_strncmp(str, "export", len)
		|| !ft_strncmp(str, "unset", len)
		|| !ft_strncmp(str, "env", len)
		|| !ft_strncmp(str, "exit", len));
}

void	run_exec(t_cmd *cmd, t_shell *sh)
{
	t_exec	*exec;

	exec = (t_exec *)cmd;
	if (exec->argv[0] == NULL)
		return ;
	/* parse variable before use argv */
	if (is_build_in(exec->argv[0]))
		printf("%s: Build_in is inconstruction\n", exec->argv[0]);
	else
		ft_execute (cmd, sh);
}

void	runcmd(t_cmd *cmd, t_shell *sh)
{
	if (!cmd)
		exit (0);
	else if (cmd->type == EXEC)
		run_exec(cmd, sh);
	else if (cmd->type == REDIR)
		run_redir(cmd, sh);
	else if (cmd->type == PIPE)
		run_pipe(cmd, sh);
}
