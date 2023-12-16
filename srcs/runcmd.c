/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:09:49 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/15 14:28:28 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_build_in(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	return (!ft_strncmp(str, "echo", len)
		|| !ft_strncmp(str, "cd", len)
		|| !ft_strncmp(str, "pwd", len)
		|| !ft_strncmp(str, "export", len)
		|| !ft_strncmp(str, "unset", len)
		|| !ft_strncmp(str, "env", len)
		|| !ft_strncmp(str, "exit", len));
}

void	run_exec(t_cmd *cmd, t_list *env)
{
	t_exec	*exec;

	exec = (t_exec *)cmd;
	if (is_build_in(exec->argv[0]))
		printf("%s: Build_in is inconstruction\n", exec->argv[0]);
	else
		// printf("call exevep\n");
	exit (0);
}

// void	run_redir(t_cmd *cmd, int *p)
// {
// 	t_redir	*redir;
// 	int		fd;

// 	redir = (t_redir *)cmd;
// 	if (redir->mode == '<')
// 	{
// 		// close (0);
// 		fd = open(redir->file)
// 	}
// }

int	runcmd(t_cmd *cmd, t_list *env)
{
	int	p[2];
	
	if (pipe(p))
	{
		perror ("runcmd");
		exit (0);
	}
	if (!cmd)
		return (0);
	if (cmd->type == EXEC)
		run_exec(cmd);
	// if (cmd->type == REDIR)
	// 	run_redir(cmd, p);
	exit (0);
}
