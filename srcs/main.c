/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:26:15 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/17 10:18:32 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_cmd *cmd, t_shell *sh)
{
	int	id;

	id = fork();
	if (id == -1)
	{
		perror ("exec_command");
		return (EXIT_FAILURE);
	}
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
		// showtoken (line);
		// parsecmd (line);
		sh->cmd = parser (line);
		if (!sh->cmd)
		{
			free(line);
			continue;
		}
		// if (cmd)
		// {
		// 	debug_parser (cmd);
		// 	free_cmd (cmd);
		// }
		exec_command(sh->cmd, sh);
		// free (cmd);	
		free_cmd (sh->cmd);
		free (line);
	}
	ft_lstclear(&sh->env, &free_env);
	free (sh);
	// free_shell (sh);
	free (line);
	return (0);
}
