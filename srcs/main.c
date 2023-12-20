/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:26:15 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/20 15:18:30 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	exec_command(t_cmd *cmd, t_shell *sh)
int	exec_command(char *line, t_shell *sh)
{
	int	id;
	int	status;

	id = fork_1("exec_command", sh);
	if (id == 0)
	{
		sh->cmd = parser(line);
		if (!sh->cmd)
		{
			free (line);
			exit (0);
		}
		runcmd(sh->cmd, sh);
		free_cmd (sh->cmd);
		free (line);
	}
	waitpid(id, &status, 0);
	return (WEXITSTATUS(status));
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
	ft_memset(sh, 0, sizeof(t_shell));
	sh->env = ft_get_env();
	if (!sh->env)
	{
		free (sh);
		perror ("init_shell cannot get env");
		exit (EXIT_FAILURE);
	}
	return (sh);
}

int	is_build_in_non_fork(char *cmd)
{
	size_t	len;

	if (!cmd)
		return (0);
	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "exit", len)
		|| !ft_strncmp(cmd, "cd", len)
		|| !ft_strncmp(cmd, "export", len)
		|| !ft_strncmp(cmd, "unset", len))
		return (1);
	return (0);
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
		return (is_build_in_non_fork(exec->argv[0]));
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
		add_history(line);
		// sh->cmd = parser (line);
		// if (!sh->cmd)
		// {
		// 	free(line);
		// 	continue;
		// }
		/* execute */
		// if (is_non_fork(sh->cmd))
		// 	runcmd(sh->cmd, sh);
		// else
		sh->exit_code = exec_command(line, sh);
		// sh->exit_code = exec_command(sh->cmd, sh);
		/**/

		/* debug */
		// debug_parser(sh->cmd);
		
		free_cmd (sh->cmd);
		free (line);
	}
	ft_lstclear(&sh->env, &free_env);
	free (sh);
	free (line);
	return (0);
}
