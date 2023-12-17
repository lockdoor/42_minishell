/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:09:49 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/17 09:47:20 by pnamnil          ###   ########.fr       */
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

void	run_exec(t_cmd *cmd, t_shell *sh)
{
	t_exec	*exec;

	exec = (t_exec *)cmd;
	if (is_build_in(exec->argv[0]))
		printf("%s: Build_in is inconstruction\n", exec->argv[0]);
	else
		ft_execute (cmd, sh);
	exit (0);
}

void	run_redir(t_cmd *cmd, t_shell *sh)
{
	t_redir	*redir;
	int		fd;
	char	*file;

	redir = (t_redir *)cmd;

	// next step parse file
	file = redir->file;
	if (redir->mode == '<')
	{
		// close (0);
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			perror (file);
			free_shell(sh);
			exit (EXIT_FAILURE);
		}
		dup2 (fd, STDIN_FILENO);
		close (fd);
	}
	else if (redir->mode == '>')
	{
		fd = open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
		if (fd == -1)
		{
			perror (file);
			free_shell(sh);
			exit (EXIT_FAILURE);
		}
		dup2 (fd, STDOUT_FILENO);
		close (fd);
	}
	else if (redir->mode == '+')
	{
		fd = open (file, O_WRONLY|O_CREAT|O_APPEND, 0644);
		if (fd == -1)
		{
			perror (file);
			free_shell(sh);
			exit (EXIT_FAILURE);
		}
		dup2 (fd, STDOUT_FILENO);
		close (fd);
	}
	runcmd(redir->cmd, sh);
}

void	run_pipe(t_cmd *cmd, t_shell *sh)
{
	int		p[2];
	int		id[2];
	t_pipe	*exec_pipe;

	exec_pipe = (t_pipe *)cmd;
	if (pipe(p))
	{
		perror ("run_pipe");
		free_shell(sh);
		exit(EXIT_FAILURE);
	}
	id[0] = fork();
	if (id[0] == -1)
	{
		perror ("run_pipe");
		free_shell(sh);
		exit(EXIT_FAILURE);
	}
	if (id[0] == 0)
	{
		close (p[0]);
		dup2 (p[1], STDOUT_FILENO);
		close (p[1]);
		runcmd(exec_pipe->left, sh);
	}
	id[1] = fork();
	if (id[0] == -1)
	{
		perror ("run_pipe");
		free_shell(sh);
		exit(EXIT_FAILURE);
	}
	if (id[1] == 0)
	{
		close (p[1]);
		dup2(p[0], STDIN_FILENO);
		close (p[0]);
		runcmd(exec_pipe->right, sh);
	}
	close (p[0]);
	close (p[1]);
	waitpid(id[0], NULL, 0);
	waitpid(id[1], NULL, 0);
	exit (0);
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
	exit (0);
}
