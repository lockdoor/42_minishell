/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:26:15 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/15 14:29:17 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_cmd *cmd, t_list *env)
{
	int	id;

	id = fork();
	if (id == -1)
	{
		perror ("exec_command");
		return (EXIT_FAILURE);
	}
	if (id == 0)
		runcmd(cmd, env);
	waitpid(id, NULL, 0);
	return (0);
}

int main(void)
{
	char	*line;
	t_cmd	*cmd;
	t_list	*env;

	env = ft_get_env();
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		// showtoken (line);
		// parsecmd (line);
		cmd = parser (line);
		if (!cmd)
		{
			free(line);
			continue;
		}
		// if (cmd)
		// {
		// 	debug_parser (cmd);
		// 	free_cmd (cmd);
		// }
		exec_command(cmd, env);
		free (cmd);		
		free (line);
	}
	
	free (line);
	return (0);
}
