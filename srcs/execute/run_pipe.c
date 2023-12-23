/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:44:47 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/23 11:17:46 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		fork_1(char	*s, t_shell *sh)
{
	int	id;

	id = fork();
	if (id == -1)
	{
		perror (s);
		free_shell(sh);
		exit(EXIT_FAILURE);
	}
	return(id);
}

static void	fork_left(t_cmd *cmd, int *p, t_shell *sh)
{
	close (p[0]);
	dup2 (p[1], STDOUT_FILENO);
	close (p[1]);
	runcmd(cmd, sh);
}

static void	fork_rigth(t_cmd *cmd, int *p, t_shell *sh)
{
	close (p[1]);
	dup2(p[0], STDIN_FILENO);
	close (p[0]);
	runcmd(cmd, sh);
}

void	run_pipe(t_cmd *cmd, t_shell *sh)
{
	int		p[2];
	int		id[2];
	t_pipe	*exec_pipe;
	int		status;

	exec_pipe = (t_pipe *)cmd;
	if (pipe(p))
	{
		perror ("run_pipe");
		free_shell(sh);
		exit(EXIT_FAILURE);
	}
	id[0] = fork_1("run_pipe", sh);
	if (id[0] == 0)
	{
		/* global variable= */
		// ++g_process ;
		
		fork_left(exec_pipe->left, p, sh);
	}
	id[1] = fork_1("run_pipe", sh);
	if (id[1] == 0)
	{
		/* global variable= */
		// ++g_process ;
		
		fork_rigth(exec_pipe->right, p, sh);
	}
	close (p[0]);
	close (p[1]);
	waitpid(id[0], NULL, 0);
	waitpid(id[1], &status, 0);
	// debug
	// printf ("runpipe: status: %d\n", WEXITSTATUS(status));
	// exit (status);
	exit (WEXITSTATUS(status));
}