/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:26:15 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/22 10:14:04 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to handle SIGINT
// void sigintHandler(int signum) {
//     printf("\nCaught SIGINT (Ctrl+C)\n");
//     // Additional cleanup or actions can be performed here
//     exit(EXIT_SUCCESS);
// }

// Function to handle SIGQUIT
// void sigquitHandler(int signum) {
//     printf("\nCaught SIGQUIT (Ctrl+\\)\n");
//     // Additional cleanup or actions can be performed here
//     exit(EXIT_SUCCESS);
// }

int	exec_command(t_cmd *cmd, t_shell *sh)
// int	exec_command(char *line, t_shell *sh)
{
	int	id;
	int	status;

	id = fork_1("exec_command", sh);
	if (id == 0)
	{
		runcmd(cmd, sh);
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

int main(void)
{
	char	*line;
	t_shell *sh;

	// Register signal handlers
    // if (signal(SIGINT, sigintHandler) == SIG_ERR) {
    //     perror("Unable to register SIGINT handler");
    //     exit(EXIT_FAILURE);
    // }

    // if (signal(SIGQUIT, sigquitHandler) == SIG_ERR) {
    //     perror("Unable to register SIGQUIT handler");
    //     exit(EXIT_FAILURE);
    // }

	sh = init_shell();
	while (1)
	{
		line = readline("$ ");
		if (!line)
			break;
		add_history(line);

		sh->cmd = parser(line);
		if (sh->cmd)
		{
			if (sh->cmd->type != PIPE && is_build_in_non_fork(sh->cmd))
			{
				sh->exit_code = runcmd_non_fork(sh->cmd, sh);
			}
			else
			{		
				sh->exit_code = exec_command(sh->cmd, sh);
			}
			free_cmd (sh->cmd);
		
			/* debug */
			// debug_parser(sh->cmd);
		}
		
		// printf("env: %s\n", getenv("SHLVL"));

		free (line);
	}
	ft_lstclear(&sh->env, &free_env);
	free (sh);
	free (line);
	return (0);
}
