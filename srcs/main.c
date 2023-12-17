/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:26:15 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/17 14:18:35 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_cmd *cmd, t_shell *sh)
{
	int	id;

	id = fork_1("exec_command", sh);
	if (id == 0)
		runcmd(cmd, sh);
	waitpid(id, NULL, 0);
	return (0);
}

t_shell	*init_shell(void)
{
	t_shell	*sh;

	sh = (t_shell *) malloc (sizeof(t_shell));
	if (!sh)
	{
		perror ("init_shell");
		exit (EXIT_FAILURE);
	}
	sh->env = ft_get_env();
	if (!sh->env)
	{
		free (sh);
		perror ("init_shell");
		exit (EXIT_FAILURE);
	}
	return (sh);
}

int	is_non_fork(t_cmd *cmd)
{
	t_redir	*redir;
	t_exec	*exec;
	if (cmd->type == PIPE)
		return (0);
	else if (cmd->type == REDIR)
	{
		redir = (t_redir *)cmd;
		return (is_non_fork (redir->cmd));
	}
	else if (cmd->type == EXEC)
	{
		exec = (t_exec *)cmd;
		return (is_build_in(exec->argv[0]));
	}
	return (0);
}

int main(void)
{
	char	*line;
	t_shell *sh;

	sh = init_shell();
	while (1)
	{
		line = readline("$ ");
		if (!line)
			break;
		sh->cmd = parser (line);
		if (!sh->cmd)
		{
			free(line);
			continue;
		}
		if (is_non_fork(sh->cmd))
			runcmd(sh->cmd, sh);
		else
			exec_command(sh->cmd, sh);
		free_cmd (sh->cmd);
		free (line);
	}
	ft_lstclear(&sh->env, &free_env);
	free (sh);
	free (line);
	return (0);
}
