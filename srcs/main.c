/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:26:15 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/23 15:31:01 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	g_process;

int	exec_command(t_cmd *cmd, t_shell *sh)
// int	exec_command(char *line, t_shell *sh)
{
	int	id;
	int	status;

	id = fork_1("exec_command", sh);

	if (id == 0)
	{
		/* global variable= */
		// ++g_process ;
		
		runcmd(cmd, sh);
		// exit(0);
	}
	// waitpid(id, &status, 0);
	wait(&status);
	return (WEXITSTATUS(status));
}

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		// if (g_process > 1)
		// {
			// ft_putendl_fd("i am child", 1);
			// rl_redisplay();
		// 	exit (130);
		// }
		// else if (g_process == 0)
		// else
		// {	
			if (!g_signal)
			{
				ft_putchar_fd('\n', STDOUT_FILENO);
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();	
				return ;		
			}
			g_signal = signum;
			// if (g_signal > 1)
			// {
			// 	exit (130);
			// }
		// }
	}
}

void	init_sig(void)
{
	struct sigaction	sa;
	/* set handler funtion */
	sa.sa_handler = sigint_handler;

	/* init struct empty */
	sigemptyset (&sa.sa_mask);

	sa.sa_flags = SA_RESTART;

	/* register hangler */
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror ("sigaction");
		exit (EXIT_FAILURE);
	}
	// if (sigaction(SIGQUIT, sa, NULL) == -1)
	// {
	// 	perror ("sigaction");
	// 	exit (EXIT_FAILURE);
	// }
}

t_shell	*init_shell(void)
{
	t_shell	*sh;

	init_sig();
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


	sh = init_shell();
	while (1)
	{
		/* global variable= */
		// g_process = 0;
		g_signal = 0;
		
		line = readline("$ ");
		
		// g_process++ ;
		g_signal++ ;
		
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
		
			if (g_signal == SIGINT)
				sh->exit_code = 130;
			
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
